//===-- bitbyte/foundation/tier2/assert.c -----------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier2/assert.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

static bitbyte_foundation_tier2_assertion_handler_t assertion_handler_ = NULL;
static void *assertion_handler_ctx_ = NULL;

//===----------------------------------------------------------------------===//

bool
bitbyte_foundation_tier2_assertion_handler(
  bitbyte_foundation_tier2_assertion_handler_t *handler,
  void **ctx)
{
  if (handler == NULL)
    return false;
  if (ctx == NULL)
    return false;

  *handler = assertion_handler_;
  *ctx = assertion_handler_ctx_;

  return true;
}

//===----------------------------------------------------------------------===//

bool
bitbyte_foundation_tier2_set_assertion_handler(
  bitbyte_foundation_tier2_assertion_handler_t handler,
  void *ctx)
{
  if (handler == NULL)
    return false;

  assertion_handler_ = handler;
  ctx = ctx;

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

bool Assertion::handler(Assertion::Handler *handler_, void **ctx_)
{
  return ::bitbyte_foundation_tier2_assertion_handler(handler_, ctx_);
}

//===----------------------------------------------------------------------===//

bool Assertion::set_handler(Assertion::Handler handler_, void *ctx_)
{
  return ::bitbyte_foundation_tier2_set_assertion_handler(handler_, ctx_);
}

//===----------------------------------------------------------------------===//

} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
