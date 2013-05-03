// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/debug/callstack.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #include <DbgHelp.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif 

namespace foundation {
  bool callstack(
    Callstack& callstack,
    ExecutionState& execution_state )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    CONTEXT context;
    STACKFRAME64 stack_frame;

    zero((void*)&context, sizeof(CONTEXT));
    zero((void*)&stack_frame, sizeof(STACKFRAME64));

    #if defined(FOUNDATION_ARCHITECTURE_X86_64)
      static const DWORD machine_type = IMAGE_FILE_MACHINE_AMD64;

      context.ContextFlags = CONTEXT_CONTROL;
      context.Rbp          = execution_state.RBP;
      context.Rsp          = execution_state.RSP;
      context.Rip          = execution_state.RIP;

      stack_frame.AddrFrame.Offset = cexecution_state.RBP;
      stack_frame.AddrFrame.Mode   = AddrModeFlat;
      stack_frame.AddrStack.Offset = execution_state.RSP;
      stack_frame.AddrStack.Mode   = AddrModeFlat;
      stack_frame.AddrPC.Offset    = execution_state.RIP;
      stack_frame.AddrPC.Mode      = AddrModeFlat;
    #elif defined(FOUNDATION_ARCHITECTURE_X86)
      static const DWORD machine_type = IMAGE_FILE_MACHINE_I386;

      context.ContextFlags = CONTEXT_CONTROL;
      context.Ebp          = execution_state.EBP;
      context.Esp          = execution_state.ESP;
      context.Eip          = execution_state.EIP;

      stack_frame.AddrFrame.Offset = context.Ebp;
      stack_frame.AddrFrame.Mode   = AddrModeFlat;
      stack_frame.AddrStack.Offset = context.Esp;
      stack_frame.AddrStack.Mode   = AddrModeFlat;
      stack_frame.AddrPC.Offset    = context.Eip;
      stack_frame.AddrPC.Mode      = AddrModeFlat;
    #endif

    while (StackWalk64(
      machine_type, GetCurrentProcess(), GetCurrentThread(),
      &stack_frame, &context, NULL,
      &SymFunctionTableAccess64, &SymGetModuleBase64, NULL))
    {
      void* symbol_address = (void*)stack_frame.AddrPC.Offset;
      if (!symbol_address)
        break;
      callstack.frames +=
        Callstack::Frame(Symbol::from_address(symbol_address));
    }

    return true;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }
} // foundation
