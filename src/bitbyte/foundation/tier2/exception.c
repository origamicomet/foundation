//===-- bitbyte/foundation/tier2/exception.c --------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mwilliams@bitbyte.ca>
//
//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier2/exception.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier0/architecture.h"
#include "bitbyte/foundation/tier0/compiler.h"
#include "bitbyte/foundation/tier0/system.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #include <windows.h>
#endif

#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  #include <new.h>
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

static bitbyte_foundation_tier2_exception_handler_t exception_handler_ = NULL;
static void *exception_handler_ctx_ = NULL;

//===----------------------------------------------------------------------===//

bool
bitbyte_foundation_tier2_exception_handler(
  bitbyte_foundation_tier2_exception_handler_t *handler,
  void **ctx)
{
  if (handler == NULL)
    return false;
  if (ctx == NULL)
    return false;

  *handler = exception_handler_;
  *ctx = exception_handler_ctx_;

  return true;
}

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
static
LONG
WINAPI
_unhandled_exception_filter(
  EXCEPTION_POINTERS *ep)
{
  bitbyte_foundation_tier2_exception_t E;

  switch (ep->ExceptionRecord->ExceptionCode) {
    case EXCEPTION_ACCESS_VIOLATION:
    case EXCEPTION_IN_PAGE_ERROR:
      E.type = BITBYTE_FOUNDATION_TIER2_EXCEPTION_ACCESS_VIOLATION;
      E.info.access_violation.address = (void *)ep->ExceptionRecord->ExceptionInformation[1];
      E.info.access_violation.read  = (ep->ExceptionRecord->ExceptionInformation[0] == 0);
      E.info.access_violation.write = (ep->ExceptionRecord->ExceptionInformation[0] == 1);
      E.info.access_violation.execute = (ep->ExceptionRecord->ExceptionInformation[0] == 8);
      break;

    case EXCEPTION_DATATYPE_MISALIGNMENT:
      E.type = BITBYTE_FOUNDATION_TIER2_EXCEPTION_MISALIGNED_READ_OR_WRITE;
      break;

    case EXCEPTION_ILLEGAL_INSTRUCTION:
    case EXCEPTION_PRIV_INSTRUCTION:
      E.type = BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_INSTRUCTION;
      break;

    case EXCEPTION_FLT_DENORMAL_OPERAND:
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
    case EXCEPTION_FLT_INEXACT_RESULT:
    case EXCEPTION_FLT_INVALID_OPERATION:
    case EXCEPTION_FLT_OVERFLOW:
    case EXCEPTION_FLT_STACK_CHECK:
    case EXCEPTION_FLT_UNDERFLOW:
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
    case EXCEPTION_INT_OVERFLOW:
      E.type = BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_ARITHMETIC;
      break;

    case EXCEPTION_STACK_OVERFLOW:
      E.type = BITBYTE_FOUNDATION_TIER2_EXCEPTION_STACK_OVERFLOW;
      break;

    default:
      E.type = BITBYTE_FOUNDATION_TIER2_EXCEPTION_UNKNOWN;
      break;
  }

  exception_handler_(&E, exception_handler_ctx_);
  return EXCEPTION_CONTINUE_SEARCH;
}
#endif

#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
static
int
_new_handler(
  size_t)
{
  bitbyte_foundation_tier2_exception_t E;
  E.type = BITBYTE_FOUNDATION_TIER2_EXCEPTION_OUT_OF_MEMORY;
  exception_handler_(&E, exception_handler_ctx_);
  return 0;
}
#endif

bool
bitbyte_foundation_tier2_set_exception_handler(
  bitbyte_foundation_tier2_exception_handler_t handler,
  void *ctx)
{
  if (handler == NULL)
    return false;

  exception_handler_ = handler;
  ctx = ctx;

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  SetUnhandledExceptionFilter(&_unhandled_exception_filter);
#endif

#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  _set_new_mode(1);
  _set_new_handler(&_new_handler);
#endif

  return true;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier2 {

//===----------------------------------------------------------------------===//

bool Exception::handler(Exception::Handler *handler_, void **ctx_)
{
  return ::bitbyte_foundation_tier2_exception_handler(handler_, ctx_);
}

//===----------------------------------------------------------------------===//

bool Exception::set_handler(Exception::Handler handler_, void *ctx_)
{
  return ::bitbyte_foundation_tier2_set_exception_handler(handler_, ctx_);
}

//===----------------------------------------------------------------------===//

} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
