//=== bitbyte/foundation/tier1/log.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier1/log.h
/// @brief Provides various logging macros.
///

#ifndef _BITBYTE_FOUNDATION_TIER1_LOG_H_
#define _BITBYTE_FOUNDATION_TIER1_LOG_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/export.h>
#include <bitbyte/foundation/tier1/logger.h>

//===----------------------------------------------------------------------===//
// Configuration independent
//

/// @def bitbyte_foundation_log_
/// @brief Unconditionally logs an unformatted message.
///
#define bitbyte_foundation_log_(_Message) \
  do { \
    ::bitbyte::foundation::tier1::log( \
      bitbyte_foundation_stringify(__FILE__), \
      __LINE__, \
      _Message); \
  } while (0)

/// @def bitbyte_foundation_logf_
/// @brief Unconditionally logs a formatted message.
///
#define bitbyte_foundation_logf_(_Format, ...) \
  do { \
    const size_t message_len = snprintf(NULL, 0, _Format, ##__VA_ARGS__) + 1; \
    char *message = (const char *)alloca(message_len + 1); \
    snprintf(message, message_len + 1, _Format, ##__VA_ARGS__); \
    ::bitbyte::foundation::tier1::log( \
      bitbyte_foundation_stringify(__FILE__), \
      __LINE__, \
      (const char *message)); \
  } while (0)

//===----------------------------------------------------------------------===//
// Configuration dependent
//

/// @def bitbyte_foundation_log
/// @brief Conditonally compiles in logging based on `_Level`.
///
#define bitbyte_foundation_log(_Level, ...) \
  bitbyte_foundation_log_##_Level(__VA_ARGS__)

/// @def bitbyte_foundation_logf
/// @brief Conditonally compiles in logging based on `_Level`.
///
#define bitbyte_foundation_logf(_Level, ...) \
  bitbyte_foundation_logf_##_Level(__VA_ARGS__)

//===----------------------------------------------------------------------===//

#define bitbyte_foundation_log_always(_Message) \
  bitbyte_foundation_log_(_Message)

#define bitbyte_foundation_logf_always(_Format, ...) \
  bitbyte_foundation_logf_(_Format, ##__VA_ARGS__)

#ifdef BITBYTE_FOUNDATION_PARANOID
  #define bitbyte_foundation_log_paranoid(_Message) \
    bitbyte_foundation_log_(_Message)
  #define bitbyte_foundation_logf_paranoid(_Format, ...) \
    bitbyte_foundation_logf_(_Format, ##__VA_ARGS__)
#else
  #define bitbyte_foundation_log_paranoid(_Message) do {} while (0)
  #define bitbyte_foundation_logf_paranoid(_Format, ...) do {} while (0)
#endif

#if (BITBYTE_FOUNDATION_CONFIGURATION >= BITBYTE_FOUNDATION_DEBUG)
  #define bitbyte_foundation_log_debug(_Message) \
    bitbyte_foundation_log_(_Message)
  #define bitbyte_foundation_logf_debug(_Format, ...) \
    bitbyte_foundation_logf_(_Format, ##__VA_ARGS__)
#else
  #define bitbyte_foundation_log_debug(_Message) do {} while (0)
  #define bitbyte_foundation_logf_debug(_Format, ...) do {} while (0)
#endif

#if (BITBYTE_FOUNDATION_CONFIGURATION >= BITBYTE_FOUNDATION_DEVELOPMENT)
  #define bitbyte_foundation_log_development(_Message) \
    bitbyte_foundation_log_(_Message)
  #define bitbyte_foundation_logf_development(_Format, ...) \
    bitbyte_foundation_logf_(_Format, ##__VA_ARGS__)
#else
  #define bitbyte_foundation_log_development(_Message) do {} while (0)
  #define bitbyte_foundation_logf_development(_Format, ...) do {} while (0)
#endif

#if (BITBYTE_FOUNDATION_CONFIGURATION >= BITBYTE_FOUNDATION_RELEASE)
  #define bitbyte_foundation_log_release(_Message) \
    bitbyte_foundation_log_(_Message)
  #define bitbyte_foundation_logf_release(_Format, ...) \
    bitbyte_foundation_logf_(_Format, ##__VA_ARGS__)
#else
  #define bitbyte_foundation_log_release(_Message) do {} while (0)
  #define bitbyte_foundation_logf_release(_Format, ...) do {} while (0)
#endif

#endif // _BITBYTE_FOUNDATION_TIER1_LOG_H_
