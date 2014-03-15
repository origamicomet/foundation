//=== bitbyte/foundation/tier2/atomics.cc ====================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier2/atomics.h>

#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  #include <intrin.h>
  #if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedCompareExchange)
  #elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedExchangeAdd64)
    #pragma intrinsic(_InterlockedCompareExchange)
    #pragma intrinsic(_InterlockedCompareExchange64)
  #endif
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
#else
  #error ("Unknown or unsupported compiler.")
#endif

namespace bitbyte {
namespace foundation {
namespace tier2 {

//===----------------------------------------------------------------------===//
// Load & Store
//

namespace atomic {
namespace relaxed {

atomic::s32 load(volatile atomic::s32 *v) {
#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
  return *v;
#elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
#endif
}

void store(volatile atomic::s32 *v, atomic::s32 desired) {
#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
  *v = desired;
#elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
#endif
}

atomic::u32 load(volatile atomic::u32 *v) {
#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
  return *v;
#elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
#endif
}

void store(volatile atomic::u32 *v, atomic::u32 desired) {
#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
  *v = desired;
#elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
#endif
}

atomic::s64 load(volatile atomic::s64 *v) {
#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
  return *v;
#elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
#endif
}

void store(volatile atomic::s64 *v, atomic::s64 desired) {
#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
  *v = desired;
#elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
#endif
}

atomic::u64 load(volatile atomic::u64 *v) {
#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
  return *v;
#elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
#endif
}

void store(volatile atomic::u64 *v, atomic::u64 desired) {
#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
  *v = desired;
#elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
#endif
}

} // relaxed
} // atomic

//===----------------------------------------------------------------------===//
// Increment & Decrement
//

namespace atomic {
namespace relaxed {

atomic::s32 increment(volatile atomic::s32 *v) {
  return add(v, 1) + 1;
}

atomic::s32 decrement(volatile atomic::s32 *v) {
  return sub(v, 1) - 1;
}

atomic::u32 increment(volatile atomic::u32 *v) {
  return add(v, 1) + 1;
}

atomic::u32 decrement(volatile atomic::u32 *v) {
  return sub(v, 1) - 1;
}

#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)

atomic::s64 increment(volatile atomic::s64 *v) {
  return add(v, 1) + 1;
}

atomic::s64 decrement(volatile atomic::s64 *v) {
  return sub(v, 1) - 1;
}

atomic::u64 increment(volatile atomic::u64 *v) {
  return add(v, 1) + 1;
}

atomic::u64 decrement(volatile atomic::u64 *v) {
  return sub(v, 1) - 1;
}

#endif

} // relaxed
} // atomic

//===----------------------------------------------------------------------===//
// Add & Subtract
//

namespace atomic {
namespace relaxed {

atomic::s32 add(volatile atomic::s32 *lhs, atomic::s32 rhs) {
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return (atomic::s32)_InterlockedExchangeAdd((volatile long *)lhs, (long)rhs);
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

atomic::s32 sub(volatile atomic::s32 *lhs, atomic::s32 rhs) {
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return (atomic::s32)_InterlockedExchangeAdd((volatile long *)lhs, (long)-rhs);
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

atomic::u32 add(volatile atomic::u32 *lhs, atomic::u32 rhs) {
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return (*(atomic::u32 *)&_InterlockedExchangeAdd((volatile long *)lhs, *((long *)&rhs)));
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

atomic::u32 sub(volatile atomic::u32 *lhs, atomic::u32 rhs) {
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return (*(atomic::u32 *)&_InterlockedExchangeAdd((volatile long *)lhs, *((long *)&(-rhs))));
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)

atomic::s64 add(volatile atomic::s64 *lhs, atomic::s64 rhs) {
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

atomic::s64 sub(volatile atomic::s64 *lhs, atomic::s64 rhs) {
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

atomic::u64 add(volatile atomic::u64 *lhs, atomic::u64 rhs) {
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return (*(atomic::u64 *)&_InterlockedExchangeAdd((volatile __int64 *)lhs, *((__int64 *)&rhs)));
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

atomic::u64 sub(volatile atomic::u64 *lhs, atomic::u64 rhs) {
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return (*(atomic::u64 *)&_InterlockedExchangeAdd((volatile __int64 *)lhs, *((__int64 *)&(-rhs))));
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

#endif

} // relaxed
} // atomic

//===----------------------------------------------------------------------===//
// Compare and Swap
//

namespace atomic {
namespace relaxed {

atomic::s32 compare_and_swap(
  volatile atomic::s32 *v,
  atomic::s32 expected,
  atomic::s32 desired)
{
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return (atomic::s32 )_InterlockedCompareExchange((volatile long *)v, (long)desired, (long)expected);
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

atomic::u32 compare_and_swap(
  volatile atomic::u32 *v,
  atomic::u32 expected,
  atomic::u32 desired)
{
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return *((atomic::u32 *)&_InterlockedCompareExchange((volatile long *)v, *((long *)&desired), *((long *)&expected)));
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)

atomic::s64 compare_and_swap(
  volatile atomic::s64 *v,
  atomic::s64 expected,
  atomic::s64 desired)
{
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return (atomic::s64 )_InterlockedCompareExchange64((volatile __int64 *)v, (__int64)desired, (__int64)expected);
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

atomic::u64 compare_and_swap(
  volatile atomic::u64 *v,
  atomic::u64 expected,
  atomic::u64 desired)
{
#if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
  return *((atomic::u64 *)&_InterlockedCompareExchange64((volatile __int64 *)v, *((__int64 *)&desired), *((__int64 *)&expected)));
#elif (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_GCC) || \
      (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_CLANG)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

#endif

} // relaxed
} // atomic

} // tier2
} // foundation
} // bitbyte
