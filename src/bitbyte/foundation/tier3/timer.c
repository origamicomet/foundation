//===-- bitbyte/foundation/tier3/timer.c ------------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier3/timer.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier0/system.h"
#include "bitbyte/foundation/tier2/assert.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #include <windows.h>
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  #include <unistd.h>
  #include <mach/mach_time.h>
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  #include <unistd.h>
  #include <time.h>
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

typedef struct bitbyte_foundation_tier3_timer_impl {
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  LARGE_INTEGER epoch;
  LARGE_INTEGER freq;
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  mach_timebase_info_data_t tbi;
  uint64_t epoch;
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  uint64_t epoch;
#endif
} bitbyte_foundation_tier3_timer_impl_t;

//===----------------------------------------------------------------------===//

bitbyte_foundation_tier3_timer_t *
bitbyte_foundation_tier3_timer_create(void)
{
  bitbyte_foundation_tier3_timer_impl_t *timer =
    (bitbyte_foundation_tier3_timer_impl_t *)malloc(sizeof(bitbyte_foundation_tier3_timer_impl_t));
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  // These error checks seem almost redundant, but end-users are funny buggers,
  // so let's just play it safe.
  BOOL bHasPerformanceCounterFrequency = QueryPerformanceFrequency(&timer->freq);
  bitbyte_foundation_tier2_assert(bHasPerformanceCounterFrequency);
  BOOL bHasEpoch = QueryPerformanceCounter(&timer->epoch);
  bitbyte_foundation_tier2_assert(bHasEpoch);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  mach_timebase_info(&impl->tbi);
  impl->epoch = mach_absolute_time();
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  timer->epoch = ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec;
#endif
  return (bitbyte_foundation_tier3_timer_t *)timer;
}

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier3_timer_destroy(
  bitbyte_foundation_tier3_timer_t *timer)
{
  bitbyte_foundation_tier3_timer_impl_t *impl =
    (bitbyte_foundation_tier3_timer_impl_t *)timer;
  free((void *)impl);
}

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier3_timer_reset(
  bitbyte_foundation_tier3_timer_t *timer)
{
  bitbyte_foundation_tier3_timer_impl_t *impl =
    (bitbyte_foundation_tier3_timer_impl_t *)timer;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  const BOOL bHasNewEpoch = QueryPerformanceCounter(&impl->epoch);
  bitbyte_foundation_tier2_assert(bHasNewEpoch);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  impl->epoch = mach_absolute_time();
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  impl->epoch = ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec;
#endif
}

//===----------------------------------------------------------------------===//

uint64_t
bitbyte_foundation_tier3_timer_secs(
  const bitbyte_foundation_tier3_timer_t *timer)
{
  bitbyte_foundation_tier3_timer_impl_t *impl =
    (bitbyte_foundation_tier3_timer_impl_t *)timer;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  LARGE_INTEGER liNow;
  const BOOL bHasNow = QueryPerformanceCounter(&liNow);
  bitbyte_foundation_tier2_assert(bHasNow);
  LARGE_INTEGER liElapsed;
  liElapsed.QuadPart = (liNow.QuadPart - impl->epoch.QuadPart);
  return (liElapsed.QuadPart / impl->freq.QuadPart);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  const uint64_t elapsed = mach_absolute_time() - impl->epoch;
  return ((elapsed * impl>tbi.numer * UINT64_C(1000000000)) / impl->tbi.denom);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  const uint64_t elapsed = (ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec) - impl->epoch;
  return (elapsed / UINT64_C(1000000000));
#endif
}

//===----------------------------------------------------------------------===//

uint64_t
bitbyte_foundation_tier3_timer_msecs(
  const bitbyte_foundation_tier3_timer_t *timer)
{
  bitbyte_foundation_tier3_timer_impl_t *impl =
    (bitbyte_foundation_tier3_timer_impl_t *)timer;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  LARGE_INTEGER liNow;
  const BOOL bHasNow = QueryPerformanceCounter(&liNow);
  bitbyte_foundation_tier2_assert(bHasNow);
  LARGE_INTEGER liElapsed;
  liElapsed.QuadPart = (liNow.QuadPart - impl->epoch.QuadPart);
  return ((liElapsed.QuadPart * UINT64_C(1000)) / impl->freq.QuadPart);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  const uint64_t elapsed = mach_absolute_time() - impl->epoch;
  return ((elapsed * impl>tbi.numer * UINT64_C(1000000)) / impl->tbi.denom);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  const uint64_t elapsed = (ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec) - impl->epoch;
  return (elapsed / UINT64_C(1000000));
#endif
}

//===----------------------------------------------------------------------===//

uint64_t
bitbyte_foundation_tier3_timer_usecs(
  const bitbyte_foundation_tier3_timer_t *timer)
{
  bitbyte_foundation_tier3_timer_impl_t *impl =
    (bitbyte_foundation_tier3_timer_impl_t *)timer;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  LARGE_INTEGER liNow;
  const BOOL bHasNow = QueryPerformanceCounter(&liNow);
  bitbyte_foundation_tier2_assert(bHasNow);
  LARGE_INTEGER liElapsed;
  liElapsed.QuadPart = (liNow.QuadPart - impl->epoch.QuadPart);
  return ((liElapsed.QuadPart * UINT64_C(1000000)) / impl->freq.QuadPart);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  const uint64_t elapsed = mach_absolute_time() - impl->epoch;
  return ((elapsed * impl>tbi.numer * UINT64_C(1000)) / impl->tbi.denom);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  const uint64_t elapsed = (ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec) - impl->epoch;
  return (elapsed / UINT64_C(1000));
#endif
}

//===----------------------------------------------------------------------===//

uint64_t
bitbyte_foundation_tier3_timer_nsecs(
  const bitbyte_foundation_tier3_timer_t *timer)
{
  bitbyte_foundation_tier3_timer_impl_t *impl =
    (bitbyte_foundation_tier3_timer_impl_t *)timer;
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  LARGE_INTEGER liNow;
  const BOOL bHasNow = QueryPerformanceCounter(&liNow);
  bitbyte_foundation_tier2_assert(bHasNow);
  LARGE_INTEGER liElapsed;
  liElapsed.QuadPart = (liNow.QuadPart - impl->epoch.QuadPart);
  return ((liElapsed.QuadPart * UINT64_C(1000000000)) / impl->freq.QuadPart);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  const uint64_t elapsed = mach_absolute_time() - impl->epoch;
  return ((elapsed * impl>tbi.numer) / impl->tbi.denom);
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  const uint64_t elapsed = (ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec) - impl->epoch;
  return elapsed;
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

Timer *Timer::create(void)
{
  return (Timer *)::bitbyte_foundation_tier3_timer_create();
}

//===----------------------------------------------------------------------===//

void Timer::destroy(void)
{
  return ::bitbyte_foundation_tier3_timer_destroy((bitbyte_foundation_tier3_timer_t *)this);
}

//===----------------------------------------------------------------------===//

void Timer::reset(void)
{
  return ::bitbyte_foundation_tier3_timer_reset((bitbyte_foundation_tier3_timer_t *)this);
}

//===----------------------------------------------------------------------===//

uint64_t Timer::secs(void)
{
  return ::bitbyte_foundation_tier3_timer_secs((const bitbyte_foundation_tier3_timer_t *)this);
}

//===----------------------------------------------------------------------===//

uint64_t Timer::msecs(void)
{
  return ::bitbyte_foundation_tier3_timer_msecs((const bitbyte_foundation_tier3_timer_t *)this);
}

//===----------------------------------------------------------------------===//

uint64_t Timer::usecs(void)
{
  return ::bitbyte_foundation_tier3_timer_usecs((const bitbyte_foundation_tier3_timer_t *)this);
}

//===----------------------------------------------------------------------===//

uint64_t Timer::nsecs(void)
{
  return ::bitbyte_foundation_tier3_timer_nsecs((const bitbyte_foundation_tier3_timer_t *)this);
}

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier3

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
