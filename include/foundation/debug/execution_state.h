// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DEBUG_EXECUTION_STATE_H_
#define _FOUNDATION_DEBUG_EXECUTION_STATE_H_

// Grabs the current exectution state (registers).

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  struct ExecutionState {
  #if defined(FOUNDATION_ARCHITECTURE_X86_64)
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
  #elif defined(FOUNDATION_ARCHITECTURE_X86)
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

  extern FOUNDATION_EXPORT void FOUNDATION_STDCALL get_execution_state(
    ExecutionState& exec_state );
} // foundation

#endif // _FOUNDATION_DEBUG_EXECUTION_STATE_H_
