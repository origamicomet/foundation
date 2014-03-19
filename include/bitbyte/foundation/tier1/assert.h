//=== bitbyte/foundation/tier1/assert.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier1/assert.h
/// @brief Provides various assertion macros.
///

#ifndef _BITBYTE_FOUNDATION_TIER1_ASSERT_H_
#define _BITBYTE_FOUNDATION_TIER1_ASSERT_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/export.h>
#include <bitbyte/foundation/tier1/assertion.h>

//===----------------------------------------------------------------------===//
// Configuration independent
//

/// @def bitbyte_foundation_assert_
/// @brief Asserts that the supplied `_Predicate` is true, and if not, invokes
///  the user-specified assertion handler.
///
#define bitbyte_foundation_assert_(_Predicate) \
  do { \
    if (!(_Predicate)) { \
      ::bitbyte::foundation::tier1::Assertion assertion; \
      assertion.predicate = bitbyte_foundation_stringify(_Predicate); \
      assertion.file = bitbyte_foundation_stringify(__FILE__); \
      assertion.line = __LINE__; \
      assertion.message = NULL; \
      assertion.handle(); \
    } \
  } while (0)

/// @def bitbyte_foundation_assertf_
/// @brief Asserts that the supplied `_Predicate` is true, and if not, invokes
///  the user-specified assertion handler.
///
#define bitbyte_foundation_assertf_(_Predicate, _Format, ...) \
  do { \
    if (!(_Predicate)) { \
      ::bitbyte::foundation::tier1::Assertion assertion; \
      assertion.predicate = bitbyte_foundation_stringify(_Predicate); \
      assertion.file = bitbyte_foundation_stringify(__FILE__); \
      assertion.line = __LINE__; \
      const size_t message_len = snprintf(NULL, 0, _Format, ##__VA_ARGS__) + 1; \
      char *message = (const char *)alloca(message_len + 1); \
      snprintf(message, message_len + 1, _Format, ##__VA_ARGS__); \
      assertion.message = (const char *)message; \
      assertion.handle(); \
    } \
  } while (0)

//===----------------------------------------------------------------------===//
// Configuration dependent
//

/// @def bitbyte_foundation_assert
/// @brief Conditonally compiles in assertions based on `_Level`.
///
#define bitbyte_foundation_assert(_Level, ...) \
  bitbyte_foundation_assert_##_Level(__VA_ARGS__)

/// @def bitbyte_foundation_assertf
/// @brief Conditonally compiles in assertions based on `_Level`.
///
#define bitbyte_foundation_assertf(_Level, ...) \
  bitbyte_foundation_assertf_##_Level(__VA_ARGS__)

//===----------------------------------------------------------------------===//

#define bitbyte_foundation_assert_always(_Message) \
  do { \
    ::bitbyte::foundation::tier1::Assertion assertion; \
    assertion.predicate = NULL; \
    assertion.file = bitbyte_foundation_stringify(__FILE__); \
    assertion.line = __LINE__; \
    assertion.message = _Message; \
    assertion.handle(); \
  } while (0)

#define bitbyte_foundation_assertf_always(_Format, ...) \
  do { \
    ::bitbyte::foundation::tier1::Assertion assertion; \
    assertion.predicate = NULL; \
    assertion.file = bitbyte_foundation_stringify(__FILE__); \
    assertion.line = __LINE__; \
    const size_t message_len = snprintf(NULL, 0, _Format, ##__VA_ARGS__) + 1; \
    char *message = (const char *)alloca(message_len + 1); \
    snprintf(message, message_len + 1, _Format, ##__VA_ARGS__); \
    assertion.message = (const char *)message; \
    assertion.handle(); \
  } while (0)

#ifdef BITBYTE_FOUNDATION_PARANOID
  #define bitbyte_foundation_assert_paranoid(_Predicate) \
    bitbyte_foundation_assert_(_Predicate)
  #define bitbyte_foundation_assertf_paranoid(_Predicate, _Format, ...) \
    bitbyte_foundation_assertf_(_Predicate, _Format, ##__VA_ARGS__)
#else
  #define bitbyte_foundation_assert_paranoid(_Predicate) \
    do { (void)sizeof(_Predicate); } while (0)
  #define bitbyte_foundation_assertf_paranoid(_Predicate, _Format, ...) \
    do { (void)sizeof(_Predicate); } while (0)
#endif

#if (BITBYTE_FOUNDATION_CONFIGURATION >= BITBYTE_FOUNDATION_DEBUG)
  #define bitbyte_foundation_assert_debug(_Predicate) \
    bitbyte_foundation_assert_(_Predicate)
  #define bitbyte_foundation_assertf_debug(_Predicate, _Format, ...) \
    bitbyte_foundation_assertf_(_Predicate, _Format, ##__VA_ARGS__)
#else
  #define bitbyte_foundation_assert_debug(_Predicate) \
    do { (void)sizeof(_Predicate); } while (0)
  #define bitbyte_foundation_assertf_debug(_Predicate, _Format, ...) \
    do { (void)sizeof(_Predicate); } while (0)
#endif

#if (BITBYTE_FOUNDATION_CONFIGURATION >= BITBYTE_FOUNDATION_DEVELOPMENT)
  #define bitbyte_foundation_assert_development(_Predicate) \
    bitbyte_foundation_assert_(_Predicate)
  #define bitbyte_foundation_assertf_development(_Predicate, _Format, ...) \
    bitbyte_foundation_assertf_(_Predicate, _Format, ##__VA_ARGS__)
#else
  #define bitbyte_foundation_assert_development(_Predicate) \
    do { (void)sizeof(_Predicate); } while (0)
  #define bitbyte_foundation_assertf_development(_Predicate, _Format, ...) \
    do { (void)sizeof(_Predicate); } while (0)
#endif

#if (BITBYTE_FOUNDATION_CONFIGURATION >= BITBYTE_FOUNDATION_RELEASE)
  #define bitbyte_foundation_assert_release(_Predicate) \
    bitbyte_foundation_assert_(_Predicate)
  #define bitbyte_foundation_assertf_release(_Predicate, _Format, ...) \
    bitbyte_foundation_assertf_(_Predicate, _Format, ##__VA_ARGS__)
#else
  #define bitbyte_foundation_assert_release(_Predicate) \
    do { (void)sizeof(_Predicate); } while (0)
  #define bitbyte_foundation_assertf_release(_Predicate, _Format, ...) \
    do { (void)sizeof(_Predicate); } while (0)
#endif

#endif // _BITBYTE_FOUNDATION_TIER1_ASSERT_H_
