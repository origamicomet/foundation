//===-- bitbyte/foundation/tier2/log.c --------------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier2/log.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier1/stdio.h"
#include "bitbyte/foundation/tier1/malloc.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

typedef struct bitbyte_foundation_tier2_subscribed_logger {
  struct bitbyte_foundation_tier2_subscribed_logger *next, *prev;
  bitbyte_foundation_tier2_logger_t logger;
  void *ctx;
} bitbyte_foundation_tier2_subscribed_logger_t;

static bitbyte_foundation_tier2_subscribed_logger_t *subscribed_loggers_head_ = NULL;
static bitbyte_foundation_tier2_subscribed_logger_t *subscribed_loggers_tail_ = NULL;

//===----------------------------------------------------------------------===//

void *
bitbyte_foundation_tier2_subscribe_logger(
  bitbyte_foundation_tier2_logger_t logger,
  void *ctx)
{
  if (logger == NULL)
    return NULL;

  bitbyte_foundation_tier2_subscribed_logger_t *subscribed =
    (bitbyte_foundation_tier2_subscribed_logger_t *)
      malloc(sizeof(bitbyte_foundation_tier2_subscribed_logger_t));

  subscribed->next = NULL;
  subscribed->prev = subscribed_loggers_tail_;
  subscribed_loggers_tail_ = subscribed;
  subscribed->logger = logger;
  subscribed->ctx = ctx;

  return (void *)subscribed;
}

//===----------------------------------------------------------------------===//

bool
bitbyte_foundation_tier2_unsubscribe_logger(
  void *subscribed_)
{
  if (subscribed_ == NULL)
    return false;

  bitbyte_foundation_tier2_subscribed_logger_t *subscribed =
    (bitbyte_foundation_tier2_subscribed_logger_t *)subscribed_;
  if (subscribed->prev)
    subscribed->prev->next = subscribed->next;
  if (subscribed->next)
    subscribed->next->prev = subscribed->prev;
  free((void *)subscribed);

  return true;
}

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier2_log_formatted(
  const bitbyte_foundation_log_level_t level,
  const char *format,
  ...)
{
  va_list ap;
  va_start(ap, format);
  const size_t len = vsnprintf(NULL, 0, format, ap) + 1;
  char *formatted = (char *)alloca(len);
  vsnprintf(formatted, len, format, ap);
  bitbyte_foundation_tier2_log_unformatted(level, formatted);
}

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier2_log_unformatted(
  const bitbyte_foundation_log_level_t level,
  const char *message)
{
  bitbyte_foundation_tier2_subscribed_logger_t *iter = subscribed_loggers_head_;
  while (iter) {
    iter->logger(level, message, iter->ctx);
    iter = iter->next;
  }
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

void
log::formatted(
  const log::Level level,
  const char *format,
  ...)
{
  va_list ap;
  va_start(ap, format);
  const size_t len = vsnprintf(NULL, 0, format, ap) + 1;
  char *formatted = (char *)alloca(len);
  vsnprintf(formatted, len, format, ap);
  ::bitbyte_foundation_tier2_log_unformatted(
    (::bitbyte_foundation_tier2_log_level_t)level,
    formatted);
}

//===----------------------------------------------------------------------===//

void
log::unformatted(
  const log::Level level,
  const char *message)
{
  ::bitbyte_foundation_tier2_log_unformatted(
    (::bitbyte_foundation_tier2_log_level_t)level,
    message);
}

//===----------------------------------------------------------------------===//

Logger::Logger()
  : __subscribed__(NULL)
{
}

//===----------------------------------------------------------------------===//

Logger::~Logger()
{
}

//===----------------------------------------------------------------------===//

bool Logger::subscribe(void) const
{
  if (__subscribed__ != NULL)
    return false;

  struct Proxier {
    static void proxy(
      const ::bitbyte_foundation_tier2_log_level_t level,
      const char *message,
      void *ctx)
    {
      ((Logger *)ctx)->log((log::Level)level, message);
    }
  };

  this->__subscribed__ =
    ::bitbyte_foundation_tier2_subscribe_logger(&Proxier::proxy, (void *)this);

  return (this->__subscribed__ != NULL);
}

//===----------------------------------------------------------------------===//

bool Logger::unsubscribe(void) const
{
  return ::bitbyte_foundation_tier2_unsubscribe_logger(this->__subscribed__);
}

//===----------------------------------------------------------------------===//

} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
