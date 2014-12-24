//===-- bitbyte/foundation/tier3/timer.h ------------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Abstracts high-resolution monotonic timer access.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER3_TIMER_H_
#define _BITBYTE_FOUNDATION_TIER3_TIMER_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdint.h"
#include "bitbyte/foundation/tier3/linkage.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief A high-resolution monotonic timer.
///
typedef struct bitbyte_foundation_tier3_timer {
} bitbyte_foundation_tier3_timer_t;

/// \copydoc bitbyte_foundation_tier3_timer_t
typedef bitbyte_foundation_tier3_timer_t bitbyte_foundation_timer_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_timer_t
  typedef bitbyte_foundation_timer_t foundation_timer_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_timer_create
/// \copydoc bitbyte_foundation_timer_create
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_timer_create bitbyte_foundation_timer_create
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_timer_create
/// \copydoc bitbyte_foundation_tier3_timer_create
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_timer_create bitbyte_foundation_tier3_timer_create
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Creates a high-resolution monotonic timer.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
bitbyte_foundation_tier3_timer_t *
bitbyte_foundation_tier3_timer_create(void);

//===----------------------------------------------------------------------===//

/// \def foundation_timer_destroy
/// \copydoc bitbyte_foundation_timer_destroy
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_timer_destroy bitbyte_foundation_timer_destroy
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_timer_destroy
/// \copydoc bitbyte_foundation_tier3_timer_destroy
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_timer_destroy bitbyte_foundation_tier3_timer_destroy
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Destroys a high-resolution monotonic lock.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
void
bitbyte_foundation_tier3_timer_destroy(
  bitbyte_foundation_tier3_timer_t *timer);

//===----------------------------------------------------------------------===//

/// \def foundation_timer_reset
/// \copydoc bitbyte_foundation_timer_reset
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_timer_reset bitbyte_foundation_timer_reset
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_timer_reset
/// \copydoc bitbyte_foundation_tier3_timer_reset
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_timer_reset bitbyte_foundation_tier3_timer_reset
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Resets a high-resolution monotonic lock.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
void
bitbyte_foundation_tier3_timer_reset(
  bitbyte_foundation_timer_t *timer);

//===----------------------------------------------------------------------===//

/// \def foundation_timer_secs
/// \copydoc bitbyte_foundation_timer_secs
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_timer_secs bitbyte_foundation_timer_secs
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_timer_secs
/// \copydoc bitbyte_foundation_tier3_timer_secs
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_timer_secs bitbyte_foundation_tier3_timer_secs
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the number of seconds elapsed since the last reset.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
uint64_t
bitbyte_foundation_tier3_timer_secs(
  const bitbyte_foundation_timer_t *timer);

//===----------------------------------------------------------------------===//

/// \def foundation_timer_msecs
/// \copydoc bitbyte_foundation_timer_msecs
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_timer_msecs bitbyte_foundation_timer_msecs
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_timer_msecs
/// \copydoc bitbyte_foundation_tier3_timer_msecs
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_timer_msecs bitbyte_foundation_tier3_timer_msecs
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the number of miliseconds elapsed since the last reset.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
uint64_t
bitbyte_foundation_tier3_timer_msecs(
  const bitbyte_foundation_timer_t *timer);

//===----------------------------------------------------------------------===//

/// \def foundation_timer_usecs
/// \copydoc bitbyte_foundation_timer_usecs
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_timer_usecs bitbyte_foundation_timer_usecs
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_timer_usecs
/// \copydoc bitbyte_foundation_tier3_timer_usecs
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_timer_usecs bitbyte_foundation_tier3_timer_usecs
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the number of microseconds elapsed since the last reset.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
uint64_t
bitbyte_foundation_tier3_timer_usecs(
  const bitbyte_foundation_timer_t *timer);

//===----------------------------------------------------------------------===//

/// \def foundation_timer_nsecs
/// \copydoc bitbyte_foundation_timer_nsecs
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_timer_nsecs bitbyte_foundation_timer_nsecs
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_timer_nsecs
/// \copydoc bitbyte_foundation_tier3_timer_nsecs
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_timer_nsecs bitbyte_foundation_tier3_timer_nsecs
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the number of nanoseconds elapsed since the last reset.
///
/// \warning Nanosecond resolution is not guaranteed on some platforms, namely
/// Microsoft Windows as QueryPerformanceCounter usually takes the worst code
/// path possible.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
uint64_t
bitbyte_foundation_tier3_timer_nsecs(
  const bitbyte_foundation_timer_t *timer);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier3 {

//===----------------------------------------------------------------------===//

/// \copydoc ::bitbyte_foundation_tier3_timer_t
class BITBYTE_FOUNDATION_TIER3_EXPORT Timer :
  public bitbyte_foundation_tier3_timer_t
{
 public:
  /// \copydoc ::bitbyte_foundation_tier3_timer_create
  static Timer *create(void);
  /// \copydoc ::bitbyte_foundation_tier3_timer_destroy
  void destroy(void);
 public:
  /// \copydoc ::bitbyte_foundation_tier3_timer_reset
  void reset(void);
 public:
  /// \copydoc ::bitbyte_foundation_tier3_timer_secs
  uint64_t secs(void);
  /// \copydoc ::bitbyte_foundation_tier3_timer_secs
  uint64_t msecs(void);
  /// \copydoc ::bitbyte_foundation_tier3_timer_usecs
  uint64_t usecs(void);
  /// \copydoc ::bitbyte_foundation_tier3_timer_nsecs
  uint64_t nsecs(void);
};

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier3

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER3_TIMER_H_

//============================================================================//
