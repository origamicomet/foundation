// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/debug/execution_state.h>

#if defined(FOUNDATION_ARCHITECTURE_X86_64)
  extern "C" void __foundation_execution_state_x86_64();
#elif defined(FOUNDATION_ARCHITECTURE_X86)
  extern "C" void __foundation_execution_state_x86();
#endif

namespace foundation {
  void FOUNDATION_STDCALL get_execution_state(
    ExecutionState& exec_state )
  {
  (void)exec_state;
  #if defined(FOUNDATION_ARCH_X86_64)
    __foundation_execution_state_x86_64();
  #elif defined(FOUNDATION_ARCH_X86)
    __foundation_execution_state_x86();
  #endif
  }
} // foundation
