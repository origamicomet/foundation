// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/debug_info.h>
#include <foundation/memory.h>
#include <foundation/string.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #include <DbgHelp.h>
#elif defined(FOUNDATION_PLATFORM_MACOSX)
#elif defined(FOUNDATION_PLATFORM_LINUX)
#else
#endif 

namespace foundation {
  bool load_debug_information(
    const char** search_dirs,
    size_t num_search_dirs )
  {
#if defined(FOUNDATION_PLATFORM_WINDOWS)
    wchar_t* search_path = nullptr;
    if (num_search_dirs > 0) {
      String search_path_;
      for (size_t search_dir = 0; search_dir < num_search_dirs; ++search_dir) {
        search_path_ += search_dirs[search_dir];
        if (search_dir != (num_search_dirs - 1))
          search_path_ += ':';
      }

      const size_t len = MultiByteToWideChar(
        CP_UTF8, 0, search_path_.to_ptr(), search_path_.size(), nullptr, 0
      );

      search_path = (wchar_t*)alloca(len * sizeof(wchar_t));
      MultiByteToWideChar(
        CP_UTF8, 0, search_path_.to_ptr(), search_path_.size(), search_path, len
      );
    }

    SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_OMAP_FIND_NEAREST);
    SymCleanup(GetCurrentProcess());

    return (SymInitializeW(
      GetCurrentProcess(),
      search_path,
      TRUE /* Deferring symbol loading might create multi-threading issues... */
    ) == TRUE);
#elif defined(FOUNDATION_PLATFORM_MACOSX) || defined(FOUNDATION_PLATFORM_LINUX)
    return false;
#else
    return false;
#endif
  }

  bool address_to_name(
    void* address,
    char* name,
    size_t name_len )
  {
    if (!address)
      return false;

    if (name_len <= 0)
      return false;

#if defined(FOUNDATION_PLATFORM_WINDOWS)
    SYMBOL_INFOW* sym_info =
      (SYMBOL_INFOW*)alloca(sizeof(SYMBOL_INFOW) + 254 * sizeof(wchar_t));
    zero((void*)sym_info, sizeof(SYMBOL_INFOW) + 254 * sizeof(wchar_t));
    sym_info->SizeOfStruct = sizeof(SYMBOL_INFOW);
    sym_info->MaxNameLen = 255;

    const bool success =
      (SymFromAddrW(
        GetCurrentProcess(),
        (DWORD64)address,
        0, /* Don't need displacement */
        sym_info
      ) == TRUE);

    if (!success)
      return false;

    WideCharToMultiByte(
      CP_UTF8, 0, sym_info->Name, sym_info->NameLen + 1, (char*)name, name_len, 0, 0
    );
  
    return true;
#elif defined(FOUNDATION_PLATFORM_MACOSX) || defined(FOUNDATION_PLATFORM_LINUX)
    return false;
#else
    return false;
#endif
  }

  bool address_to_file_path(
    void* address,
    char* file_path,
    size_t file_path_len )
  {
    if (!address)
      return false;

    if (file_path_len <= 0)
      return false;

#if defined(FOUNDATION_PLATFORM_WINDOWS)
    IMAGEHLP_LINEW64 ihl;

    zero((void*)&ihl, sizeof(IMAGEHLP_LINEW64));
    ihl.SizeOfStruct = sizeof(IMAGEHLP_LINEW64);

    DWORD displacement;
    const bool success =
      (SymGetLineFromAddrW64(
        GetCurrentProcess(),
        (DWORD64)address,
        &displacement, /* Don't need displacement */
        &ihl
      ) == TRUE);

    if (!success)
      return false;

    WideCharToMultiByte(
      CP_UTF8, 0, ihl.FileName, wcslen(ihl.FileName) + 1, (char*)file_path, file_path_len, 0, 0
    );

    return true;
#elif defined(FOUNDATION_PLATFORM_MACOSX) || defined(FOUNDATION_PLATFORM_LINUX)
    return false;
#else
    return false;
#endif
  }

  bool address_to_line_number(
    void* address,
    uint32_t& line_number )
  {
#if defined(FOUNDATION_PLATFORM_WINDOWS)
    IMAGEHLP_LINEW64 ihl;

    zero((void*)&ihl, sizeof(IMAGEHLP_LINEW64));
    ihl.SizeOfStruct = sizeof(IMAGEHLP_LINEW64);

    DWORD displacement;
    const bool success =
      (SymGetLineFromAddrW64(
        GetCurrentProcess(),
        (DWORD64)address,
        &displacement, /* Don't need displacement */
        &ihl
      ) == TRUE);

    if (!success)
      return false;

    line_number = ihl.LineNumber;

    return true;
#elif defined(FOUNDATION_PLATFORM_MACOSX) || defined(FOUNDATION_PLATFORM_LINUX)
    return false;
#else
    return false;
#endif
  }
} // foundation

#if defined(FOUNDATION_ARCH_X86_64)
  extern "C" void foundation_execution_state_x86_64();
#elif defined(FOUNDATION_ARCH_X86)
  extern "C" void foundation_execution_state_x86();
#endif

namespace foundation {
  void FOUNDATION_STDCALL get_execution_state(
    ExecutionState& exec_state )
  {
    (void)exec_state;
  #if defined(FOUNDATION_ARCH_X86_64)
    foundation_execution_state_x86_64();
  #elif defined(FOUNDATION_ARCH_X86)
    foundation_execution_state_x86();
  #endif
  }

  bool callstack(
    Callstack& callstack )
  {
#if defined(FOUNDATION_PLATFORM_WINDOWS)
    CONTEXT context;
    STACKFRAME64 stack_frame;
    ExecutionState exec_state;

    zero((void*)&context, sizeof(CONTEXT));
    zero((void*)&stack_frame, sizeof(STACKFRAME64));
    get_execution_state(exec_state);

#if defined(FOUNDATION_ARCH_X86_64)
    static const DWORD machine_type = IMAGE_FILE_MACHINE_AMD64;

    context.ContextFlags = CONTEXT_CONTROL;
    context.Rbp          = exec_state.RBP;
    context.Rsp          = exec_state.RSP;
    context.Rip          = exec_state.RIP;

    stack_frame.AddrFrame.Offset = cexec_state.RBP;
    stack_frame.AddrFrame.Mode   = AddrModeFlat;
    stack_frame.AddrStack.Offset = exec_state.RSP;
    stack_frame.AddrStack.Mode   = AddrModeFlat;
    stack_frame.AddrPC.Offset    = exec_state.RIP;
    stack_frame.AddrPC.Mode      = AddrModeFlat;
#elif defined(FOUNDATION_ARCH_X86)
    static const DWORD machine_type = IMAGE_FILE_MACHINE_I386;

    context.ContextFlags = CONTEXT_CONTROL;
    context.Ebp          = exec_state.EBP;
    context.Esp          = exec_state.ESP;
    context.Eip          = exec_state.EIP;

    stack_frame.AddrFrame.Offset = context.Ebp;
    stack_frame.AddrFrame.Mode   = AddrModeFlat;
    stack_frame.AddrStack.Offset = context.Esp;
    stack_frame.AddrStack.Mode   = AddrModeFlat;
    stack_frame.AddrPC.Offset    = context.Eip;
    stack_frame.AddrPC.Mode      = AddrModeFlat;
#endif
    
    while (StackWalk64(
      machine_type,
      GetCurrentProcess(), GetCurrentThread(),
      &stack_frame, &context, NULL,
      &SymFunctionTableAccess64, &SymGetModuleBase64, NULL
    )) {
      void* sym_address = (void*)stack_frame.AddrPC.Offset;

      if (!sym_address)
        break;

      Callstack::Frame frame;

      if (!address_to_name(sym_address, &frame.name[0], 255 - 33)) {
        sprintf(
          &frame.name[0],
          "#<Function:%016" PRIx64 ">",
          (uint64_t)sym_address
        );
      } else {
        sprintf(
          &frame.name[strlen(&frame.name[0])],
          " - #<Function:%016" PRIx64 ">",
          (uint64_t)sym_address
        );
      }

      if (!address_to_file_path(sym_address, &frame.file[0], 255))
        frame.file[0] = '\0';

      if (!address_to_line_number(sym_address, frame.line))
        frame.line = 0;

      callstack.frames.push_back(frame);
    }

    return true;
#elif defined(FOUNDATION_PLATFORM_MACOSX) || defined(FOUNDATION_PLATFORM_LINUX)
    return false;
#else
    return false;
#endif
  } 
} // foundation

