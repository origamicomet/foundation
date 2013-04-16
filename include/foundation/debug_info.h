// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DEBUG_INFO_H_
#define _FOUNDATION_DEBUG_INFO_H_

// Provides a cross-platform interface to look debug information.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/assert.h>
#include <foundation/array.h>

namespace foundation {
  // Attempts to load debug information relating to this executable.
  // An optional list of directories to search for debug information can be
  // specified with |search_dirs| and |num_search_dirs|.
  extern FOUNDATION_EXPORT bool load_debug_information(
    const char** search_dirs,
    size_t num_search_dirs );

  // Attempts to provide a textual representation of a symbol relating to a
  // specific address.
  extern FOUNDATION_EXPORT bool address_to_name(
    void* address,
    char* name,
    size_t name_len );

  // Attempts to determine a file path relating to a specific address.
  extern FOUNDATION_EXPORT bool address_to_file_path(
    void* address,
    char* file_path,
    size_t file_path_len );

  // Attempts to determine a line-number relating to a specific address.
  extern FOUNDATION_EXPORT bool address_to_line_number(
    void* address,
    uint32_t& line_number );

  struct ExecutionState {
  #if defined(FOUNDATION_ARCH_X86_64)
    uint64_t RAX;
    uint64_t RCX;
    uint64_t RDX;
    uint64_t RBX;
    uint64_t RSP;
    uint64_t RBP;
    uint64_t RSI;
    uint64_t RDI;
    uint64_t R8;
    uint64_t R9;
    uint64_t R10;
    uint64_t R11;
    uint64_t R12;
    uint64_t R13;
    uint64_t R14;
    uint64_t R15;
    uint64_t RIP;
  #elif defined(FOUNDATION_ARCH_X86)
    uint32_t EAX;
    uint32_t ECX;
    uint32_t EDX;
    uint32_t EBX;
    uint32_t ESP;
    uint32_t EBP;
    uint32_t ESI;
    uint32_t EDI;
    uint32_t EIP;
  #else
  #endif
  };

  // Grabs the current execution state (registers).
  extern FOUNDATION_EXPORT void FOUNDATION_STDCALL get_execution_state(
    ExecutionState& exec_state );

  struct Callstack {
    struct Frame {
      char     name[255];
      char     file[255];
      uint32_t line;
    };

    Array<Frame> frames;

    FOUNDATION_INLINE Callstack()
      : frames(Allocator::heap(), 0)
    {}
  };

  // Walks the callstack to attempt to provide symbol information.
  extern FOUNDATION_EXPORT bool callstack(
    Callstack& callstack ); 
} // foundation

#endif // _FOUNDATION_DEBUG_INFO_H_