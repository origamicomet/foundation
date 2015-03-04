//===-- bitbyte/foundation/tier3/mutex.c ------------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier3/mutex.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier0/system.h"
#include "bitbyte/foundation/tier2/assert.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #include <windows.h>
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  // TODO(mtwilliams): Implement mutexes on Mac OS X.
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX_
  // TODO(mtwilliams): Implement mutexes on Linux.
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

typedef struct bitbyte_foundation_tier3_mutex_impl {
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  CRITICAL_SECTION cs;
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#endif
} bitbyte_foundation_tier3_mutex_impl_t;

//===----------------------------------------------------------------------===//

bitbyte_foundation_tier3_mutex_t *
bitbyte_foundation_tier3_mutex_create(void)
{
  bitbyte_foundation_tier3_mutex_impl_t *mutex =
    (bitbyte_foundation_tier3_mutex_impl_t *)malloc(sizeof(bitbyte_foundation_tier3_mutex_impl_t));
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  BOOL bInitialized = InitializeCriticalSectionAndSpinCount(&mutex->cs, 0x00000000ul);
  bitbyte_foundation_tier2_assert(bInitialized);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#endif
  return (bitbyte_foundation_tier3_mutex_t *)mutex;
}

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier3_mutex_destroy(
  bitbyte_foundation_tier3_mutex_t *mutex)
{
  bitbyte_foundation_tier3_mutex_impl_t *impl =
    (bitbyte_foundation_tier3_mutex_impl_t *)mutex;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  DeleteCriticalSection(&impl->cs);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#endif
  free((void *)impl);
}

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier3_mutex_lock(
  bitbyte_foundation_tier3_mutex_t *mutex)
{
  bitbyte_foundation_tier3_mutex_impl_t *impl =
    (bitbyte_foundation_tier3_mutex_impl_t *)mutex;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  EnterCriticalSection(&impl->cs);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#endif
}

//===----------------------------------------------------------------------===//

bool
bitbyte_foundation_tier3_mutex_try_lock(
  bitbyte_foundation_tier3_mutex_t *mutex)
{
  bitbyte_foundation_tier3_mutex_impl_t *impl =
    (bitbyte_foundation_tier3_mutex_impl_t *)mutex;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  return !!TryEnterCriticalSection(&impl->cs);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#endif
}

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier3_mutex_unlock(
  bitbyte_foundation_tier3_mutex_t *mutex)
{
  bitbyte_foundation_tier3_mutex_impl_t *impl =
    (bitbyte_foundation_tier3_mutex_impl_t *)mutex;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  LeaveCriticalSection(&impl->cs);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#endif
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
namespace tier3 {

//===----------------------------------------------------------------------===//

Mutex *Mutex::create(void)
{
  return (Mutex *)::bitbyte_foundation_tier3_mutex_create();
}

//===----------------------------------------------------------------------===//

void Mutex::destroy(void)
{
  return ::bitbyte_foundation_tier3_mutex_destroy((bitbyte_foundation_tier3_mutex_t *)this);
}

//===----------------------------------------------------------------------===//

void Mutex::lock(void)
{
  return ::bitbyte_foundation_tier3_mutex_lock((bitbyte_foundation_tier3_mutex_t *)this);
}

//===----------------------------------------------------------------------===//

bool Mutex::try_lock(void)
{
  return ::bitbyte_foundation_tier3_mutex_try_lock((bitbyte_foundation_tier3_mutex_t *)this);
}

//===----------------------------------------------------------------------===//

void Mutex::unlock(void)
{
  return ::bitbyte_foundation_tier3_mutex_unlock((bitbyte_foundation_tier3_mutex_t *)this);
}

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier3

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
