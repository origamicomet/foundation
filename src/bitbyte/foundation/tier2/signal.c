//===-- bitbyte/foundation/tier2/signal.c -----------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier2/signal.h"

//===----------------------------------------------------------------------===//

#include <signal.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

static bitbyte_foundation_tier2_signal_handler_t signal_handler_ = NULL;
static void *signal_handler_ctx_ = NULL;

//===----------------------------------------------------------------------===//

const char *
bitbyte_foundation_tier2_signal_desc(
  bitbyte_foundation_tier2_signal_t signal)
{
  switch (signal) {
    case BITBYTE_FOUNDATION_TIER2_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED:
      return "Graceful program termination requested.";
    case BITBYTE_FOUNDATION_TIER2_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED:
      return "Abnormal program termination requested.";
    case BITBYTE_FOUNDATION_TIER2_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER:
      return "Program termination requested by user.";
  }

  return "Unknown signal.";
}

//===----------------------------------------------------------------------===//

bool
bitbyte_foundation_tier2_signal_handler(
  bitbyte_foundation_tier2_signal_handler_t *handler,
  void **ctx)
{
  if (handler == NULL)
    return false;
  if (ctx == NULL)
    return false;

  *handler = signal_handler_;
  *ctx = signal_handler_ctx_;

  return true;
}

//===----------------------------------------------------------------------===//

static
void
_signal_handler(
  int signal)
{
  if (!signal_handler_)
    return;

  switch (signal) {
    case SIGTERM:
      signal_handler_(BITBYTE_FOUNDATION_TIER2_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED, signal_handler_ctx_);
      return;
    case SIGABRT:
      signal_handler_(BITBYTE_FOUNDATION_TIER2_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED, signal_handler_ctx_);
      return;
    case SIGINT:
      signal_handler_(BITBYTE_FOUNDATION_TIER2_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER, signal_handler_ctx_);
      return;
  }
}

bool
bitbyte_foundation_tier2_set_signal_handler(
  bitbyte_foundation_tier2_signal_handler_t handler,
  void *ctx)
{
  if (handler == NULL)
    return false;

  signal_handler_ = handler;
  ctx = ctx;

  // TODO(mwilliams): Use sigaction on POSIX.
  // See http://stackoverflow.com/questions/2485028.
  signal(SIGTERM, &_signal_handler);
  signal(SIGABRT, &_signal_handler);
  signal(SIGINT, &_signal_handler);

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

bool Signal::handler(Signal::Handler *handler_, void **ctx_)
{
  return ::bitbyte_foundation_tier2_signal_handler(handler_, ctx_);
}

//===----------------------------------------------------------------------===//

bool Signal::set_handler(Signal::Handler handler_, void *ctx_)
{
  return ::bitbyte_foundation_tier2_set_signal_handler(handler_, ctx_);
}

//===----------------------------------------------------------------------===//

const char *Signal::desc(void) const
{
  return ::bitbyte_foundation_tier2_signal_desc(
    (::bitbyte_foundation_tier2_signal_t)this->E);
}

//===----------------------------------------------------------------------===//

} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
