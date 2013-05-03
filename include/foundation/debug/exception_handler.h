// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DEBUG_EXCEPTION_HANDLER_H_
#define _FOUNDATION_DEBUG_EXCEPTION_HANDLER_H_

// Provides a cross-platform interface to handle exceptions.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/debug/execution_state.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>

  namespace foundation {
    namespace windows {
      static const uint32_t exception_access_violation =
        EXCEPTION_ACCESS_VIOLATION;
      static const uint32_t exception_array_bounds_exceeded =
        EXCEPTION_ARRAY_BOUNDS_EXCEEDED;
      static const uint32_t exception_datatype_misalignment =
        EXCEPTION_DATATYPE_MISALIGNMENT;
      static const uint32_t exception_flt_denormal_operand =
        EXCEPTION_FLT_DENORMAL_OPERAND;
      static const uint32_t exception_flt_divide_by_zero =
        EXCEPTION_FLT_DIVIDE_BY_ZERO;
      static const uint32_t exception_flt_inexact_result =
        EXCEPTION_FLT_INEXACT_RESULT;
      static const uint32_t exception_flt_invalid_operation =
        EXCEPTION_FLT_INVALID_OPERATION;
      static const uint32_t exception_flt_overflow =
        EXCEPTION_FLT_OVERFLOW;
      static const uint32_t exception_flt_stack_check =
        EXCEPTION_FLT_STACK_CHECK;
      static const uint32_t exception_flt_underflow =
        EXCEPTION_FLT_UNDERFLOW;
      static const uint32_t exception_int_divide_by_zero =
        EXCEPTION_INT_DIVIDE_BY_ZERO;
      static const uint32_t exception_int_overflow =
        EXCEPTION_INT_OVERFLOW;
      static const uint32_t exception_illegal_instruction =
        EXCEPTION_ILLEGAL_INSTRUCTION;
      static const uint32_t exception_priv_instruction =
        EXCEPTION_PRIV_INSTRUCTION;
      static const uint32_t exception_stack_overflow =
        EXCEPTION_STACK_OVERFLOW;
      static const uint32_t exception_breakpoint =
        EXCEPTION_BREAKPOINT;
      static const uint32_t exception_single_step =
        EXCEPTION_SINGLE_STEP;
      static const uint32_t exception_in_page_error =
        EXCEPTION_IN_PAGE_ERROR;
      static const uint32_t exception_invalid_disposition =
        EXCEPTION_INVALID_DISPOSITION;
      static const uint32_t exception_noncontinuable_exception =
        EXCEPTION_NONCONTINUABLE_EXCEPTION;
    } // windows
  } // foundation

  #undef EXCEPTION_ACCESS_VIOLATION
  #undef EXCEPTION_ARRAY_BOUNDS_EXCEEDED
  #undef EXCEPTION_DATATYPE_MISALIGNMENT
  #undef EXCEPTION_FLT_DENORMAL_OPERAND
  #undef EXCEPTION_FLT_DIVIDE_BY_ZERO
  #undef EXCEPTION_FLT_INEXACT_RESULT
  #undef EXCEPTION_FLT_INVALID_OPERATION
  #undef EXCEPTION_FLT_OVERFLOW
  #undef EXCEPTION_FLT_STACK_CHECK
  #undef EXCEPTION_FLT_UNDERFLOW
  #undef EXCEPTION_INT_DIVIDE_BY_ZERO
  #undef EXCEPTION_INT_OVERFLOW
  #undef EXCEPTION_ILLEGAL_INSTRUCTION
  #undef EXCEPTION_PRIV_INSTRUCTION
  #undef EXCEPTION_STACK_OVERFLOW
  #undef EXCEPTION_BREAKPOINT
  #undef EXCEPTION_SINGLE_STEP
  #undef EXCEPTION_IN_PAGE_ERROR
  #undef EXCEPTION_INVALID_DISPOSITION
  #undef EXCEPTION_NONCONTINUABLE_EXCEPTION
#endif

namespace foundation {
  enum Exception {
    // Raised when a graceful termination is requested.
    EXCEPTION_TERMINATION_REQUESTED = 1,
    // Raised when trying to access unaccessable memory, either due to access
    // permissions or non-existance.
    EXCEPTION_ACCESS_VIOLATION = 2,
    // Raised when a user wishes to interrupt.
    EXCEPTION_EXTERNAL_INTERRUPT = 3,
    // Raised when trying to execute an invalid or privleged instruction.
    EXCEPTION_INVALID_INSTRUCTION = 4,
    // Raised when abnormally terminating.
    EXCEPTION_ABNORMAL_PROGRAM_TERMINATION = 5,
    // Raised when an erroneous arithmetic operation is performed (division by
    // zero, for example).
    EXCEPTION_ERRONEOUS_ARITHMETIC_OPERATION = 6,
    // Raised when memory allocation fails.
    EXCEPTION_MEMORY_ALLOCATION_FAILED = 7,
    // Raised when a pure-virtual function is called.
    EXCEPTION_PURE_VIRTUAL_FUNCTION_CALLED = 8,
    // Raised when trying to read or write on misaligned data on hardware that
    // does not provide alignment.
    EXCEPTION_MISALIGNED_READ_OR_WRITE = 9,
    // Raised when the stack is exhausted.
    EXCEPTION_STACK_OVERFLOW = 10
  };

  typedef void (*ExceptionHandler)(
    Exception exception,
    ExecutionState& execution_state );

  extern FOUNDATION_EXPORT ExceptionHandler set_exception_handler(
    ExceptionHandler handler );
} // foundation

#endif // _FOUNDATION_DEBUG_EXCEPTION_HANDLER_H_
