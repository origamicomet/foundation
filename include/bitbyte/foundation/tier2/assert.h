//===-- bitbyte/foundation/tier2/assert.h -----------------------*- C++ -*-===//
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
/// \brief Assertion macros and utilities.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER2_ASSERT_H_
#define _BITBYTE_FOUNDATION_TIER2_ASSERT_H_

//============================================================================//

#include <signal.h>

//============================================================================//

#include "bitbyte/foundation/tier1/stdbool.h"
#include "bitbyte/foundation/tier1/malloc.h"
#include "bitbyte/foundation/tier1/stdio.h"
#include "bitbyte/foundation/tier2/linkage.h"

//============================================================================//

/// \def foundation_assert
/// \copydoc bitbyte_foundation_assert
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_assert bitbyte_foundation_assert
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_assert
/// \copydoc bitbyte_foundation_tier2_assert
#define bitbyte_foundation_assert bitbyte_foundation_tier2_assert

/// \def bitbyte_foundation_tier2_assert
/// \brief Asserts if `_Predicate` is not true.
///
#define bitbyte_foundation_tier2_assert(_Predicate) \
  do { \
    if (!(_Predicate)) { \
      bitbyte_foundation_tier2_assertion_t assertion; \
      assertion.predicate = #_Predicate; \
      assertion.message = NULL; \
      assertion.context.occured.file = __FILE__; \
      assertion.context.occured.line = __LINE__; \
      bitbyte_foundation_tier2_assertion_handler_t handler; \
      void *ctx; \
      bitbyte_foundation_tier2_assertion_handler(&handler, &ctx); \
      if (handler) \
        handler(&assertion, ctx); \
      raise(SIGABRT); \
    } \
  } while (0)

//===----------------------------------------------------------------------===//

/// \def foundation_assertf
/// \copydoc bitbyte_foundation_assertf
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_assertf bitbyte_foundation_assertf
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_assertf
/// \copydoc bitbyte_foundation_tier2_assertf
#define bitbyte_foundation_assertf bitbyte_foundation_tier2_assertf

/// \def bitbyte_foundation_tier2_assertf
/// \brief Asserts if `_Predicate` is not true and provides a  formated message.
///
#define bitbyte_foundation_tier2_assertf(_Predicate, _Format, ...) \
  do { \
    if (!(_Predicate)) { \
      bitbyte_foundation_tier2_assertion_t assertion; \
      assertion.predicate = #_Predicate; \
      const size_t len = snprintf(NULL, 0, _Format, ##__VA_ARGS__) + 1; \
      char *buf = (char *)alloca(len); \
      assertion.message = (const char *)buf; \
      snprintf(buf, len, _Format, ##__VA_ARGS__); \
      assertion.context.occured.file = __FILE__; \
      assertion.context.occured.line = __LINE__; \
      bitbyte_foundation_tier2_assertion_handler_t handler; \
      void *ctx; \
      bitbyte_foundation_tier2_assertion_handler(&handler, &ctx); \
      if (handler) \
        handler(&assertion, ctx); \
      raise(SIGABRT); \
    } \
  } while (0)

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief Assertion information.
///
typedef struct bitbyte_foundation_tier2_assertion {
  const char *predicate;
  const char *message;
  struct {
    struct {
      const char *file;
      unsigned line;
    } occured;
  } context;
} bitbyte_foundation_tier2_assertion_t;

/// \copydoc bitbyte_foundation_tier2_assertion_t
typedef bitbyte_foundation_tier2_assertion_t bitbyte_foundation_assertion_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_assertion_t
  typedef bitbyte_foundation_assertion_t foundation_assertion_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \brief Assertion handler.
///
typedef void (*bitbyte_foundation_tier2_assertion_handler_t)(
  const bitbyte_foundation_tier2_assertion_t *assertion,
  void *ctx);

/// \copydoc bitbyte_foundation_tier2_assertion_handler_t
typedef bitbyte_foundation_tier2_assertion_handler_t bitbyte_foundation_assertion_handler_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_assertion_handler_t
  typedef bitbyte_foundation_assertion_handler_t foundation_assertion_handler_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_assertion_handler
/// \copydoc bitbyte_foundation_assertion_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_assertion_handler bitbyte_foundation_assertion_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_assertion_handler
/// \copydoc bitbyte_foundation_tier2_assertion_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_assertion_handler bitbyte_foundation_tier2_assertion_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Retrieves the user-specified global assertion handler.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
bitbyte_foundation_tier2_assertion_handler(
  bitbyte_foundation_tier2_assertion_handler_t *handler,
  void **ctx);

//===----------------------------------------------------------------------===//

/// \def foundation_set_assertion_handler
/// \copydoc bitbyte_foundation_set_assertion_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_set_assertion_handler bitbyte_foundation_set_assertion_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_set_assertion_handler
/// \copydoc bitbyte_foundation_tier2_set_assertion_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_set_assertion_handler bitbyte_foundation_tier2_set_assertion_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Sets the user-specified global assertion handler.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
bitbyte_foundation_tier2_set_assertion_handler(
  bitbyte_foundation_tier2_assertion_handler_t handler,
  void *ctx);

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

/// \copydoc ::bitbyte_foundation_tier2_assertion_t
class BITBYTE_FOUNDATION_TIER2_EXPORT Assertion :
  public bitbyte_foundation_tier2_assertion_t
{
 public:
  /// \copydoc ::bitbyte_foundation_tier2_assertion_handler_t
  typedef ::bitbyte_foundation_tier2_assertion_handler_t Handler;

 public:
  /// \copydoc ::bitbyte_foundation_tier2_get_assertion_handler
  static bool handler(Assertion::Handler *handler, void **ctx);

  /// \copydoc ::bitbyte_foundation_tier2_set_assertion_handler
  static bool set_handler(Assertion::Handler handler, void *ctx);
};

//===----------------------------------------------------------------------===//

} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER2_ASSERT_H_

//============================================================================//
