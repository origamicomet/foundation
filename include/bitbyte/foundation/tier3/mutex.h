//===-- bitbyte/foundation/tier3/mutex.h ------------------------*- C++ -*-===//
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
/// \brief Abstracts mutexes.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER3_MUTEX_H_
#define _BITBYTE_FOUNDATION_TIER3_MUTEX_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdint.h"
#include "bitbyte/foundation/tier3/linkage.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief A process-specific mutex.
///
typedef struct bitbyte_foundation_tier3_mutex {
} bitbyte_foundation_tier3_mutex_t;

/// \copydoc bitbyte_foundation_tier3_mutex_t
typedef bitbyte_foundation_tier3_mutex_t bitbyte_foundation_mutex_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_mutex_t
  typedef bitbyte_foundation_mutex_t foundation_mutex_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_mutex_create
/// \copydoc bitbyte_foundation_mutex_create
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_mutex_create bitbyte_foundation_mutex_create
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_mutex_create
/// \copydoc bitbyte_foundation_tier3_mutex_create
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_mutex_create bitbyte_foundation_tier3_mutex_create
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Creates a process-specific mutex.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
bitbyte_foundation_tier3_mutex_t *
bitbyte_foundation_tier3_mutex_create(void);

//===----------------------------------------------------------------------===//

/// \def foundation_mutex_destroy
/// \copydoc bitbyte_foundation_mutex_destroy
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_mutex_destroy bitbyte_foundation_mutex_destroy
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_mutex_destroy
/// \copydoc bitbyte_foundation_tier3_mutex_destroy
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_mutex_destroy bitbyte_foundation_tier3_mutex_destroy
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Destroys a process-specific mutex.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
void
bitbyte_foundation_tier3_mutex_destroy(
  bitbyte_foundation_tier3_mutex_t *mutex);

//===----------------------------------------------------------------------===//

/// \def foundation_mutex_lock
/// \copydoc bitbyte_foundation_mutex_lock
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_mutex_lock bitbyte_foundation_mutex_lock
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_mutex_lock
/// \copydoc bitbyte_foundation_tier3_mutex_lock
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_mutex_lock bitbyte_foundation_tier3_mutex_lock
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Exclusively locks a process-specific mutex, waiting indefinitely
/// until possible.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
void
bitbyte_foundation_tier3_mutex_lock(
  bitbyte_foundation_mutex_t *mutex);

//===----------------------------------------------------------------------===//

/// \def foundation_mutex_try_lock
/// \copydoc bitbyte_foundation_mutex_try_lock
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_mutex_try_lock bitbyte_foundation_mutex_try_lock
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_mutex_try_lock
/// \copydoc bitbyte_foundation_tier3_mutex_try_lock
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_mutex_try_lock bitbyte_foundation_tier3_mutex_try_lock
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Tries to exclusively lock a process-specific mutex, returning
/// immediately if not possible.
/// \returns A non-zero value if the mutex was locked, or zero if unsuccessful.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
bool
bitbyte_foundation_tier3_mutex_try_lock(
  bitbyte_foundation_mutex_t *mutex);

//===----------------------------------------------------------------------===//

/// \def foundation_mutex_unlock
/// \copydoc bitbyte_foundation_mutex_unlock
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_mutex_unlock bitbyte_foundation_mutex_unlock
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_mutex_unlock
/// \copydoc bitbyte_foundation_tier3_mutex_unlock
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_mutex_unlock bitbyte_foundation_tier3_mutex_unlock
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Unlocks a process-specific mutex.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
void
bitbyte_foundation_tier3_mutex_unlock(
  bitbyte_foundation_mutex_t *mutex);

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

/// \copydoc ::bitbyte_foundation_tier3_mutex_t
class BITBYTE_FOUNDATION_TIER3_EXPORT Mutex :
  public bitbyte_foundation_tier3_mutex_t
{
 public:
  /// \copydoc ::bitbyte_foundation_tier3_mutex_create
  static Mutex *create(void);
  /// \copydoc ::bitbyte_foundation_tier3_mutex_destroy
  void destroy(void);
 public:
  /// \copydoc ::bitbyte_foundation_tier3_mutex_lock
  void lock(void);
  /// \copydoc ::bitbyte_foundation_tier3_mutex_try_lock
  bool try_lock(void);
  /// \copydoc ::bitbyte_foundation_tier3_mutex_unlock
  void unlock(void);
};

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier3

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER3_MUTEX_H_

//============================================================================//
