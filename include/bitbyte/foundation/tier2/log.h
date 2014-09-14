//===-- bitbyte/foundation/tier2/log.h --------------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@bitbyte.ca>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Logging.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER2_LOG_H_
#define _BITBYTE_FOUNDATION_TIER2_LOG_H_

//============================================================================//

#include <signal.h>

//============================================================================//

#include <stddef.h>
#include "bitbyte/foundation/tier1/stdbool.h"
#include "bitbyte/foundation/tier2/linkage.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief Logging level.
///
typedef enum bitbyte_foundation_tier2_log_level {
  /// Useful debugging messages.
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_DEBUG = 1,
  /// Normal messages.
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_INFO = 2,
  /// Important messages.
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_NOTICE = 3,
  /// Warnings.
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_WARNING = 4,
  /// Recoverable errors.
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_ERROR = 5,
  /// Fatal errors.
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_FATAL = 6,
} bitbyte_foundation_tier2_log_level_t;

/// \copydoc bitbyte_foundation_tier2_log_level_t
typedef bitbyte_foundation_tier2_log_level_t bitbyte_foundation_log_level_t;

/// \def BITBYTE_FOUNDATION_LOG_LEVEL_DEBUG
/// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_DEBUG
#define BITBYTE_FOUNDATION_LOG_LEVEL_DEBUG \
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_DEBUG
/// \def BITBYTE_FOUNDATION_LOG_LEVEL_INFO
/// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_INFO
#define BITBYTE_FOUNDATION_LOG_LEVEL_INFO \
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_INFO
/// \def BITBYTE_FOUNDATION_LOG_LEVEL_NOTICE
/// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_NOTICE
#define BITBYTE_FOUNDATION_LOG_LEVEL_NOTICE \
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_NOTICE
/// \def BITBYTE_FOUNDATION_LOG_LEVEL_WARNING
/// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_WARNING
#define BITBYTE_FOUNDATION_LOG_LEVEL_WARNING \
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_WARNING
/// \def BITBYTE_FOUNDATION_LOG_LEVEL_ERROR
/// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_ERROR
#define BITBYTE_FOUNDATION_LOG_LEVEL_ERROR \
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_ERROR
/// \def BITBYTE_FOUNDATION_LOG_LEVEL_FATAL
/// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_FATAL
#define BITBYTE_FOUNDATION_LOG_LEVEL_FATAL \
  BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_FATAL

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_log_level_t
  typedef bitbyte_foundation_log_level_t foundation_log_level_t;

  /// \def FOUNDATION_LOG_LEVEL_DEBUG
  /// \copydoc BITBYTE_FOUNDATION_LOG_LEVEL_DEBUG
  #define FOUNDATION_LOG_LEVEL_DEBUG \
    BITBYTE_FOUNDATION_LOG_LEVEL_DEBUG
  /// \def FOUNDATION_LOG_LEVEL_INFO
  /// \copydoc BITBYTE_FOUNDATION_LOG_LEVEL_INFO
  #define FOUNDATION_LOG_LEVEL_INFO \
    BITBYTE_FOUNDATION_LOG_LEVEL_INFO
  /// \def FOUNDATION_LOG_LEVEL_NOTICE
  /// \copydoc BITBYTE_FOUNDATION_LOG_LEVEL_NOTICE
  #define FOUNDATION_LOG_LEVEL_NOTICE \
    BITBYTE_FOUNDATION_LOG_LEVEL_NOTICE
  /// \def FOUNDATION_LOG_LEVEL_WARNING
  /// \copydoc BITBYTE_FOUNDATION_LOG_LEVEL_WARNING
  #define FOUNDATION_LOG_LEVEL_WARNING \
    BITBYTE_FOUNDATION_LOG_LEVEL_WARNING
  /// \def FOUNDATION_LOG_LEVEL_ERROR
  /// \copydoc BITBYTE_FOUNDATION_LOG_LEVEL_ERROR
  #define FOUNDATION_LOG_LEVEL_ERROR \
    BITBYTE_FOUNDATION_LOG_LEVEL_ERROR
  /// \def FOUNDATION_LOG_LEVEL_FATAL
  /// \copydoc BITBYTE_FOUNDATION_LOG_LEVEL_FATAL
  #define FOUNDATION_LOG_LEVEL_FATAL \
    BITBYTE_FOUNDATION_LOG_LEVEL_FATAL
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \brief Logger.
///
typedef void (*bitbyte_foundation_tier2_logger_t)(
  const bitbyte_foundation_tier2_log_level_t level,
  const char *message,
  void *ctx);

/// \copydoc bitbyte_foundation_tier2_logger_t
typedef bitbyte_foundation_tier2_logger_t bitbyte_foundation_logger_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_logger_t
  typedef bitbyte_foundation_logger_t foundation_logger_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_subscribe_logger
/// \copydoc bitbyte_foundation_subscribe_logger
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_subscribe_logger bitbyte_foundation_subscribe_logger
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_subscribe_logger
/// \copydoc bitbyte_foundation_tier2_subscribe_logger
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_subscribe_logger bitbyte_foundation_tier2_subscribe_logger
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Registers a user-specified logger.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
void *
bitbyte_foundation_tier2_subscribe_logger(
  bitbyte_foundation_tier2_logger_t logger,
  void *ctx);

//===----------------------------------------------------------------------===//

/// \def foundation_unsubscribe_logger
/// \copydoc bitbyte_foundation_unsubscribe_logger
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_unsubscribe_logger bitbyte_foundation_unsubscribe_logger
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_unsubscribe_logger
/// \copydoc bitbyte_foundation_tier2_unsubscribe_logger
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_unsubscribe_logger bitbyte_foundation_tier2_unsubscribe_logger
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Unsubscribes a user-specified logger.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
bitbyte_foundation_tier2_unsubscribe_logger(
  void *subscribed);

//===----------------------------------------------------------------------===//

/// \def foundation_log_formatted
/// \copydoc bitbyte_foundation_log_formatted
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_log_formatted bitbyte_foundation_log_formatted
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_log_formatted
/// \copydoc bitbyte_foundation_tier2_log_formatted
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_log_formatted bitbyte_foundation_tier2_log_formatted
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Logs a formatted messsage.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
void
bitbyte_foundation_tier2_log_formatted(
  const bitbyte_foundation_log_level_t level,
  const char *format,
  ...);

//===----------------------------------------------------------------------===//

/// \def foundation_log_unformatted
/// \copydoc bitbyte_foundation_log_unformatted
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_log_unformatted bitbyte_foundation_log_unformatted
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_log_unformatted
/// \copydoc bitbyte_foundation_tier2_log_unformatted
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_log_unformatted bitbyte_foundation_tier2_log_unformatted
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Logs an unformatted messsage.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
void
bitbyte_foundation_tier2_log_unformatted(
  const bitbyte_foundation_log_level_t level,
  const char *message);

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

namespace log {

/// \namespace bitbyte::foundation::tier2::log::Levels
/// \copydoc ::bitbyte_foundation_tier2_log_level_t
namespace Levels {
enum __Enum__ {
  /// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_DEBUG
  Debug = BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_DEBUG,
  /// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_INFO
  Info = BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_INFO,
  /// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_NOTICE
  Notice = BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_NOTICE,
  /// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_WARNING
  Warning = BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_WARNING,
  /// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_ERROR
  Error = BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_ERROR,
  /// \copydoc BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_FATAL
  Fatal = BITBYTE_FOUNDATION_TIER2_LOG_LEVEL_FATAL
};
}

/// \copydoc ::bitbyte_foundation_tier2_log_level_t
typedef Levels::__Enum__ Level;

/// \copydoc ::foundation_log_formatted
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
void
formatted(
  const Level level,
  const char *format,
  ...);

/// \copydoc ::foundation_log_unformatted
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
void
unformatted(
  const Level level,
  const char *message);

} // log

//===----------------------------------------------------------------------===//

/// \copydoc ::bitbyte_foundation_tier2_logger_t
class BITBYTE_FOUNDATION_TIER2_EXPORT Logger
{
 protected:
  Logger();
  Logger(const Logger &logger);
  Logger &operator=(const Logger &logger);
  ~Logger();

 public:
  /// \brief Called when a `message` with a `level` is logged.
  virtual void log(
    const log::Level level,
    const char *message) const = 0;

 public:
  /// \copydoc ::bitbyte_foundation_tier2_subscribe_logger
  bool subscribe(void) const;

  /// \copydoc ::bitbyte_foundation_tier2_unsubscribe_logger
  bool unsubscribe(void) const;

 private:
  mutable void *__subscribed__;
};

//===----------------------------------------------------------------------===//

} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER2_LOG_H_

//============================================================================//
