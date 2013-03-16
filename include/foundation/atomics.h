// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ATOMICS_H_
#define _FOUNDATION_ATOMICS_H_

// A collection of atomic read and write wrappers.

#include <foundation/config.h>
#include <foundation/detect.h>
#include <foundation/compat.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#elif 
#endif

namespace foundation {
namespace atomic {
#if defined(FOUNDATION_PLATFORM_WINDOWS)
  FOUNDATION_INLINE uint32_t add( volatile uint32_t* left, uint16_t right )
  { return InterlockedExchangeAdd((volatile unsigned long*)left, right); }

  FOUNDATION_INLINE uint32_t sub( volatile uint32_t* left, uint16_t right )
  { return InterlockedExchangeSubtract((volatile unsigned long*)left, right); }

  FOUNDATION_INLINE uint32_t compare_and_swap( volatile uint32_t* dest, uint32_t cmp, uint32_t xchg )
  { return InterlockedCompareExchange((volatile unsigned long*)dest, xchg, cmp); }
#elif defined(FOUNDATION_PLATFORM_POSIX)
#elif 
#endif
} // atomic
} // foundation

#endif // _FOUNDATION_ATOMICS_H_