// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/debug/exception_handler.h>

#include <new.h>

namespace foundation {
  static ExceptionHandler _exception_handler = nullptr;

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  static long __stdcall __unhandled_exception_filter(
    EXCEPTION_POINTERS* ep )
  {
    ExecutionState es;

  #if defined(FOUNDATION_ARCH_X86_64)
    es.RAX = ep->ContextRecord->Rax;
    es.RCX = ep->ContextRecord->Rcx;
    es.RDX = ep->ContextRecord->Rdx;
    es.RBX = ep->ContextRecord->Rbx;
    es.RSP = ep->ContextRecord->Rsp;
    es.RBP = ep->ContextRecord->Rbp;
    es.RSI = ep->ContextRecord->Rsi;
    es.RDI = ep->ContextRecord->Rdi;
    es.R8 = ep->ContextRecord->R8;
    es.R9 = ep->ContextRecord->R9;
    es.R10 = ep->ContextRecord->R10;
    es.R11 = ep->ContextRecord->R11;
    es.R12 = ep->ContextRecord->R12;
    es.R13 = ep->ContextRecord->R13;
    es.R14 = ep->ContextRecord->R14;
    es.R15 = ep->ContextRecord->R15;
    es.RIP = ep->ContextRecord->Rip;
  #elif defined(FOUNDATION_ARCH_X86)
    es.EAX = ep->ContextRecord->Rax;
    es.ECX = ep->ContextRecord->Rcx;
    es.EDX = ep->ContextRecord->Rdx;
    es.EBX = ep->ContextRecord->Rbx;
    es.ESP = ep->ContextRecord->Rsp;
    es.EBP = ep->ContextRecord->Rbp;
    es.ESI = ep->ContextRecord->Rsi;
    es.EDI = ep->ContextRecord->Rdi;
    es.EIP = ep->ContextRecord->Rip;
  #endif

    switch (ep->ExceptionRecord->ExceptionCode) {
      case windows::exception_access_violation:
      case windows::exception_array_bounds_exceeded:
        _exception_handler(EXCEPTION_ACCESS_VIOLATION, es);
        break;
      case windows::exception_datatype_misalignment:
        _exception_handler(EXCEPTION_MISALIGNED_READ_OR_WRITE, es);
        break;
      case windows::exception_flt_denormal_operand:
      case windows::exception_flt_divide_by_zero:
      case windows::exception_flt_inexact_result:
      case windows::exception_flt_invalid_operation:
      case windows::exception_flt_overflow:
      case windows::exception_flt_stack_check:
      case windows::exception_flt_underflow:
      case windows::exception_int_divide_by_zero:
      case windows::exception_int_overflow:
        _exception_handler(EXCEPTION_ERRONEOUS_ARITHMETIC_OPERATION, es);
        break;
      case windows::exception_illegal_instruction:
      case windows::exception_priv_instruction:
        _exception_handler(EXCEPTION_INVALID_INSTRUCTION, es);
        break;
      case windows::exception_stack_overflow:
        _exception_handler(EXCEPTION_STACK_OVERFLOW, es);
        break;
      default:
        return EXCEPTION_EXECUTE_HANDLER;
    }

    _Exit(EXIT_FAILURE);
  }

  static void __signal_handler( int sig ) {
    ExecutionState es;
    get_execution_state(es);

    switch (sig) {
      case SIGTERM:
        _exception_handler(EXCEPTION_TERMINATION_REQUESTED, es);
        break;
      case SIGSEGV:
        _exception_handler(EXCEPTION_ACCESS_VIOLATION, es);
        break;
      case SIGINT:
        _exception_handler(EXCEPTION_EXTERNAL_INTERRUPT, es);
        break;
      case SIGILL:
        _exception_handler(EXCEPTION_INVALID_INSTRUCTION, es);
        break;
      case SIGABRT:
        _exception_handler(EXCEPTION_ABNORMAL_PROGRAM_TERMINATION, es);
        break;
      case SIGFPE:
        _exception_handler(EXCEPTION_ERRONEOUS_ARITHMETIC_OPERATION, es);
        break;
    }

    _Exit(EXIT_FAILURE);
  }

  #if defined(FOUNDATION_COMPILER_MSVC)
    static int __new_handler( size_t ) {
      ExecutionState es;
      get_execution_state(es);
      _exception_handler(EXCEPTION_MEMORY_ALLOCATION_FAILED, es);
      return 0;
    }

    static void __pure_virtual_call_handler() {
      ExecutionState es;
      get_execution_state(es);
      _exception_handler(EXCEPTION_PURE_VIRTUAL_FUNCTION_CALLED, es);
    }
  #endif
#endif

  ExceptionHandler set_exception_handler(
    ExceptionHandler handler )
  {
    const ExceptionHandler previous = _exception_handler;
    _exception_handler = handler;

  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    if (handler) {
      signal(SIGTERM, &__signal_handler);
      signal(SIGSEGV, &__signal_handler);
      signal(SIGINT, &__signal_handler);
      signal(SIGILL, &__signal_handler);
      signal(SIGABRT, &__signal_handler);
      signal(SIGFPE, &__signal_handler);
    #if defined(FOUNDATION_COMPILER_MSVC)
      _set_new_handler(&__new_handler);
      _set_new_mode(1);
      _set_purecall_handler(&__pure_virtual_call_handler);
    #endif
    } else {
      signal(SIGTERM, SIG_DFL);
      signal(SIGSEGV, SIG_DFL);
      signal(SIGINT, SIG_DFL);
      signal(SIGILL, SIG_DFL);
      signal(SIGABRT, SIG_DFL);
      signal(SIGFPE, SIG_DFL);
    #if defined(FOUNDATION_COMPILER_MSVC)
      _set_new_handler(nullptr);
      _set_new_mode(0);
      _set_purecall_handler(nullptr);
    #endif
    }
  #elif defined(FOUNDATION_PLATFORM_POSIX)
    // http://stackoverflow.com/questions/2485028/signal-handling-in-c
  #endif

    return previous;
  }
} // foundation
