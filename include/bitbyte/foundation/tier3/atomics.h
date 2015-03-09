//===-- bitbyte/foundation/tier3/atomics.h ----------------------*- C++ -*-===//
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
/// \brief Abstracts atomics.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER3_ATOMICS_H_
#define _BITBYTE_FOUNDATION_TIER3_ATOMICS_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdint.h"
#include "bitbyte/foundation/tier3/linkage.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  #include <intrin.h>
  #if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedCompareExchange)
    #pragma intrinsic(_InterlockedCompareExchange64)
  #elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedExchangeAdd64)
    #pragma intrinsic(_InterlockedCompareExchange)
    #pragma intrinsic(_InterlockedCompareExchange64)
  #endif
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

///
typedef int32_t bitbyte_foundation_tier3_atomic_int32_t;

/// \copydoc bitbyte_foundation_tier3_atomic_int32_t
typedef bitbyte_foundation_tier3_atomic_int32_t bitbyte_foundation_atomic_int32_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_atomic_int32_t
  typedef bitbyte_foundation_atomic_int32_t foundation_atomic_int32_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

///
typedef uint32_t bitbyte_foundation_tier3_atomic_uint32_t;

/// \copydoc bitbyte_foundation_tier3_atomic_uint32_t
typedef bitbyte_foundation_tier3_atomic_uint32_t bitbyte_foundation_atomic_uint32_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_atomic_uint32_t
  typedef bitbyte_foundation_atomic_uint32_t foundation_atomic_uint32_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

///
typedef int64_t bitbyte_foundation_tier3_atomic_int64_t;

/// \copydoc bitbyte_foundation_tier3_atomic_int64_t
typedef bitbyte_foundation_tier3_atomic_int64_t bitbyte_foundation_atomic_int64_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_atomic_int64_t
  typedef bitbyte_foundation_atomic_int64_t foundation_atomic_int64_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

///
typedef uint64_t bitbyte_foundation_tier3_atomic_uint64_t;

/// \copydoc bitbyte_foundation_tier3_atomic_uint64_t
typedef bitbyte_foundation_tier3_atomic_uint64_t bitbyte_foundation_atomic_uint64_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_atomic_uint64_t
  typedef bitbyte_foundation_atomic_uint64_t foundation_atomic_uint64_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

///
typedef void *bitbyte_foundation_tier3_atomic_ptr_t;

/// \copydoc bitbyte_foundation_tier3_atomic_ptr_t
typedef bitbyte_foundation_tier3_atomic_ptr_t bitbyte_foundation_atomic_ptr_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_atomic_ptr_t
  typedef bitbyte_foundation_atomic_ptr_t foundation_atomic_ptr_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int32_load_relaxed
/// \copydoc bitbyte_foundation_atomic_int32_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int32_load_relaxed bitbyte_foundation_atomic_int32_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int32_load_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int32_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int32_load_relaxed bitbyte_foundation_tier3_atomic_int32_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int32_t
bitbyte_foundation_tier3_atomic_int32_load_relaxed(
  const volatile bitbyte_foundation_tier3_atomic_int32_t *v)
{
#if (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__) || \
    (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__)
  return *v;
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint32_load_relaxed
/// \copydoc bitbyte_foundation_atomic_uint32_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint32_load_relaxed bitbyte_foundation_atomic_uint32_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint32_load_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint32_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint32_load_relaxed bitbyte_foundation_tier3_atomic_uint32_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint32_t
bitbyte_foundation_tier3_atomic_uint32_load_relaxed(
  const volatile bitbyte_foundation_tier3_atomic_uint32_t *v)
{
#if (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__) || \
    (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__)
  return *v;
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int64_load_relaxed
/// \copydoc bitbyte_foundation_atomic_int64_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int64_load_relaxed bitbyte_foundation_atomic_int64_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int64_load_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int64_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int64_load_relaxed bitbyte_foundation_tier3_atomic_int64_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int64_t
bitbyte_foundation_tier3_atomic_int64_load_relaxed(
  const volatile bitbyte_foundation_tier3_atomic_int64_t *v)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  #if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
    bitbyte_foundation_tier3_atomic_int64_t result;
    __asm {
      mov esi, v;
      mov ebx, eax;
      mov ecx, edx;
      lock cmpxchg8b [esi];
      mov dword ptr result, eax;
      mov dword ptr result[4], edx;
    }
    return result;
  #elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
        (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
    bitbyte_foundation_tier3_atomic_int64_t original;
    asm volatile("movl %%ebx, %%eax\n"
                 "movl %%ecx, %%edx\n"
                 "lock; cmpxchg8b %1"
                 : "=&A"(original)
                 : "m"(v));
    return original;
  #endif
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  return *v;
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint64_load_relaxed
/// \copydoc bitbyte_foundation_atomic_uint64_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint64_load_relaxed bitbyte_foundation_atomic_uint64_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint64_load_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint64_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint64_load_relaxed bitbyte_foundation_tier3_atomic_uint64_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint64_t
bitbyte_foundation_tier3_atomic_uint64_load_relaxed(
  const volatile bitbyte_foundation_tier3_atomic_uint64_t *v)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  #if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
    bitbyte_foundation_tier3_atomic_uint64_t result;
    __asm {
      mov esi, v;
      mov ebx, eax;
      mov ecx, edx;
      lock cmpxchg8b [esi];
      mov dword ptr result, eax;
      mov dword ptr result[4], edx;
    }
    return result;
  #elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
        (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
    bitbyte_foundation_tier3_atomic_uint64_t original;
    asm volatile("movl %%ebx, %%eax\n"
                 "movl %%ecx, %%edx\n"
                 "lock; cmpxchg8b %1"
                 : "=&A"(original)
                 : "m"(v));
    return original;
  #endif
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  return *v;
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_ptr_load_relaxed
/// \copydoc bitbyte_foundation_atomic_ptr_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_ptr_load_relaxed bitbyte_foundation_atomic_ptr_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_ptr_load_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_ptr_load_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_ptr_load_relaxed bitbyte_foundation_tier3_atomic_ptr_load_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_ptr_t
bitbyte_foundation_tier3_atomic_ptr_load_relaxed(
  const volatile bitbyte_foundation_tier3_atomic_ptr_t *v)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint32_load_relaxed((volatile bitbyte_foundation_tier3_atomic_uint32_t *)v);
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint64_load_relaxed((volatile bitbyte_foundation_tier3_atomic_uint64_t *)v);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int32_store_relaxed
/// \copydoc bitbyte_foundation_atomic_int32_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int32_store_relaxed bitbyte_foundation_atomic_int32_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int32_store_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int32_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int32_store_relaxed bitbyte_foundation_tier3_atomic_int32_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
void
bitbyte_foundation_tier3_atomic_int32_store_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int32_t *v,
  bitbyte_foundation_tier3_atomic_int32_t desired)
{
#if (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__) || \
    (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__)
  *v = desired;
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint32_store_relaxed
/// \copydoc bitbyte_foundation_atomic_uint32_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint32_store_relaxed bitbyte_foundation_atomic_uint32_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint32_store_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint32_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint32_store_relaxed bitbyte_foundation_tier3_atomic_uint32_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
void
bitbyte_foundation_tier3_atomic_uint32_store_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint32_t *v,
  bitbyte_foundation_tier3_atomic_uint32_t desired)
{
#if (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__) || \
    (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__)
  *v = desired;
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int64_store_relaxed
/// \copydoc bitbyte_foundation_atomic_int64_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int64_store_relaxed bitbyte_foundation_atomic_int64_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int64_store_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int64_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int64_store_relaxed bitbyte_foundation_tier3_atomic_int64_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
void
bitbyte_foundation_tier3_atomic_int64_store_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int64_t *v,
  bitbyte_foundation_tier3_atomic_int64_t desired)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  #if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
    __asm {
      mov esi, v;
      mov ebx, dword ptr desired;
      mov ecx, dword ptr desired[4];
    retry:
      cmpxchg8b [esi];
      jne retry;
    }
  #elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
        (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
    bitbyte_foundation_tier3_atomic_int64_t expected = *v;
    asm volatile("1:  cmpxchg8b %0\n"
                 "    jne 1b"
                 : "=m"(*v)
                 : "b"((uint32_t)desired), "c"((uint32_t)(desired >> 32)), "A"(expected));
  #endif
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  *v = desired;
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint64_store_relaxed
/// \copydoc bitbyte_foundation_atomic_uint64_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint64_store_relaxed bitbyte_foundation_atomic_uint64_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint64_store_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint64_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint64_store_relaxed bitbyte_foundation_tier3_atomic_uint64_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
void
bitbyte_foundation_tier3_atomic_uint64_store_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint64_t *v,
  bitbyte_foundation_tier3_atomic_uint64_t desired)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  #if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
    __asm {
      mov esi, v;
      mov ebx, dword ptr desired;
      mov ecx, dword ptr desired[4];
    retry:
      cmpxchg8b [esi];
      jne retry;
    }
  #elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
        (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
    bitbyte_foundation_tier3_atomic_uint64_t expected = *v;
    asm volatile("1:  cmpxchg8b %0\n"
                 "    jne 1b"
                 : "=m"(*v)
                 : "b"((uint32_t)desired), "c"((uint32_t)(desired >> 32)), "A"(expected));
  #endif
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  *v = desired;
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_ptr_store_relaxed
/// \copydoc bitbyte_foundation_atomic_ptr_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_ptr_store_relaxed bitbyte_foundation_atomic_ptr_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_ptr_store_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_ptr_store_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_ptr_store_relaxed bitbyte_foundation_tier3_atomic_ptr_store_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
void
bitbyte_foundation_tier3_atomic_ptr_store_relaxed(
  const volatile bitbyte_foundation_tier3_atomic_ptr_t *v,
  const volatile bitbyte_foundation_tier3_atomic_ptr_t desired)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  bitbyte_foundation_tier3_atomic_uint32_store_relaxed((volatile bitbyte_foundation_tier3_atomic_uint32_t *)v,
                                                       (bitbyte_foundation_tier3_atomic_uint32_t)desired);
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  bitbyte_foundation_tier3_atomic_uint64_store_relaxed((volatile bitbyte_foundation_tier3_atomic_uint64_t *)v,
                                                       (bitbyte_foundation_tier3_atomic_uint64_t)desired);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int32_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_atomic_int32_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int32_fetch_and_add_relaxed bitbyte_foundation_atomic_int32_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int32_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int32_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int32_fetch_and_add_relaxed bitbyte_foundation_tier3_atomic_int32_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int32_t
bitbyte_foundation_tier3_atomic_int32_fetch_and_add_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int32_t *lhs,
  bitbyte_foundation_tier3_atomic_int32_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  return _InterlockedExchangeAdd((volatile long *)lhs, (long)rhs);
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint32_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_atomic_uint32_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint32_fetch_and_add_relaxed bitbyte_foundation_atomic_uint32_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint32_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint32_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint32_fetch_and_add_relaxed bitbyte_foundation_tier3_atomic_uint32_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint32_t
bitbyte_foundation_tier3_atomic_uint32_fetch_and_add_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint32_t *lhs,
  bitbyte_foundation_tier3_atomic_uint32_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  return _InterlockedExchangeAdd((volatile long *)lhs, (long)rhs);
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int64_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_atomic_int64_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int64_fetch_and_add_relaxed bitbyte_foundation_atomic_int64_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int64_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int64_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int64_fetch_and_add_relaxed bitbyte_foundation_tier3_atomic_int64_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int64_t
bitbyte_foundation_tier3_atomic_int64_fetch_and_add_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int64_t *lhs,
  bitbyte_foundation_tier3_atomic_int64_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  #if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
    bitbyte_foundation_tier3_atomic_int64_t expected = *lhs;
    for (;;) {
      bitbyte_foundation_tier3_atomic_int64_t original =
        _InterlockedCompareExchange64((volatile __int64 *)lhs, expected + rhs, expected);
      if (original == expected)
        return original;
      expected = original;
    }
  #elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
    return _InterlockedExchangeAdd64((volatile __int64 *)lhs, (__int64)rhs);
  #endif
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint64_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_atomic_uint64_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint64_fetch_and_add_relaxed bitbyte_foundation_atomic_uint64_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint64_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint64_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint64_fetch_and_add_relaxed bitbyte_foundation_tier3_atomic_uint64_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint64_t
bitbyte_foundation_tier3_atomic_uint64_fetch_and_add_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint64_t *lhs,
  bitbyte_foundation_tier3_atomic_uint64_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  #if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
    bitbyte_foundation_tier3_atomic_uint64_t expected = *lhs;
    for (;;) {
      bitbyte_foundation_tier3_atomic_uint64_t original =
        _InterlockedCompareExchange64((volatile __int64 *)lhs, expected + rhs, expected);
      if (original == expected)
        return original;
      expected = original;
    }
  #elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
    return _InterlockedExchangeAdd64((volatile __int64 *)lhs, (__int64)rhs);
  #endif
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_fetch_and_add(lhs, rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_ptr_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_atomic_ptr_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_ptr_fetch_and_add_relaxed bitbyte_foundation_atomic_ptr_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_ptr_fetch_and_add_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_ptr_fetch_and_add_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_ptr_fetch_and_add_relaxed bitbyte_foundation_tier3_atomic_ptr_fetch_and_add_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_ptr_t
bitbyte_foundation_tier3_atomic_ptr_fetch_and_add_relaxed(
  volatile bitbyte_foundation_tier3_atomic_ptr_t *lhs,
  bitbyte_foundation_tier3_atomic_ptr_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint32_fetch_and_add_relaxed((volatile bitbyte_foundation_tier3_atomic_uint32_t *)lhs,
                                                                                                             (bitbyte_foundation_tier3_atomic_uint32_t)rhs);
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint64_fetch_and_add_relaxed((volatile bitbyte_foundation_tier3_atomic_uint64_t *)lhs,
                                                                                                             (bitbyte_foundation_tier3_atomic_uint64_t)rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int32_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_atomic_int32_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int32_fetch_and_sub_relaxed bitbyte_foundation_atomic_int32_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int32_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int32_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int32_fetch_and_sub_relaxed bitbyte_foundation_tier3_atomic_int32_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int32_t
bitbyte_foundation_tier3_atomic_int32_fetch_and_sub_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int32_t *lhs,
  bitbyte_foundation_tier3_atomic_int32_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  return _InterlockedExchangeAdd((volatile long *)lhs, -((long)rhs));
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint32_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_atomic_uint32_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint32_fetch_and_sub_relaxed bitbyte_foundation_atomic_uint32_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint32_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint32_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint32_fetch_and_sub_relaxed bitbyte_foundation_tier3_atomic_uint32_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint32_t
bitbyte_foundation_tier3_atomic_uint32_fetch_and_sub_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint32_t *lhs,
  bitbyte_foundation_tier3_atomic_uint32_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  return _InterlockedExchangeAdd((volatile long *)lhs, -((long)rhs));
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int64_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_atomic_int64_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int64_fetch_and_sub_relaxed bitbyte_foundation_atomic_int64_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int64_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int64_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int64_fetch_and_sub_relaxed bitbyte_foundation_tier3_atomic_int64_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int64_t
bitbyte_foundation_tier3_atomic_int64_fetch_and_sub_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int64_t *lhs,
  bitbyte_foundation_tier3_atomic_int64_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  #if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
    bitbyte_foundation_tier3_atomic_int64_t expected = *lhs;
    for (;;) {
      bitbyte_foundation_tier3_atomic_int64_t original =
        _InterlockedCompareExchange64((volatile __int64 *)lhs, expected - rhs, expected);
      if (original == expected)
        return original;
      expected = original;
    }
  #elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
    return _InterlockedExchangeAdd64((volatile __int64 *)lhs, -((__int64)rhs));
  #endif
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint64_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_atomic_uint64_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint64_fetch_and_sub_relaxed bitbyte_foundation_atomic_uint64_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint64_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint64_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint64_fetch_and_sub_relaxed bitbyte_foundation_tier3_atomic_uint64_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint64_t
bitbyte_foundation_tier3_atomic_uint64_fetch_and_sub_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint64_t *lhs,
  bitbyte_foundation_tier3_atomic_uint64_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  #if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
    bitbyte_foundation_tier3_atomic_uint64_t expected = *lhs;
    for (;;) {
      bitbyte_foundation_tier3_atomic_uint64_t original =
        _InterlockedCompareExchange64((volatile __int64 *)lhs, expected - rhs, expected);
      if (original == expected)
        return original;
      expected = original;
    }
  #elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
    return _InterlockedExchangeAdd64((volatile __int64 *)lhs, -((__int64)rhs));
  #endif
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_fetch_and_sub(lhs, rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_ptr_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_atomic_ptr_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_ptr_fetch_and_sub_relaxed bitbyte_foundation_atomic_ptr_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_ptr_fetch_and_sub_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_ptr_fetch_and_sub_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_ptr_fetch_and_sub_relaxed bitbyte_foundation_tier3_atomic_ptr_fetch_and_sub_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_ptr_t
bitbyte_foundation_tier3_atomic_ptr_fetch_and_sub_relaxed(
  volatile bitbyte_foundation_tier3_atomic_ptr_t *lhs,
  bitbyte_foundation_tier3_atomic_ptr_t rhs)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint32_fetch_and_sub_relaxed((volatile bitbyte_foundation_tier3_atomic_uint32_t *)lhs,
                                                                                                             (bitbyte_foundation_tier3_atomic_uint32_t)rhs);
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint64_fetch_and_sub_relaxed((volatile bitbyte_foundation_tier3_atomic_uint64_t *)lhs,
                                                                                                             (bitbyte_foundation_tier3_atomic_uint64_t)rhs);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int32_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_atomic_int32_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int32_fetch_and_incr_relaxed bitbyte_foundation_atomic_int32_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int32_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int32_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int32_fetch_and_incr_relaxed bitbyte_foundation_tier3_atomic_int32_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int32_t
bitbyte_foundation_tier3_atomic_int32_fetch_and_incr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int32_t *v)
{
  return bitbyte_foundation_tier3_atomic_int32_fetch_and_add_relaxed(v, 1);
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint32_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_atomic_uint32_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint32_fetch_and_incr_relaxed bitbyte_foundation_atomic_uint32_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint32_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint32_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint32_fetch_and_incr_relaxed bitbyte_foundation_tier3_atomic_uint32_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint32_t
bitbyte_foundation_tier3_atomic_uint32_fetch_and_incr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint32_t *v)
{
  return bitbyte_foundation_tier3_atomic_uint32_fetch_and_add_relaxed(v, 1);
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int64_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_atomic_int64_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int64_fetch_and_incr_relaxed bitbyte_foundation_atomic_int64_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int64_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int64_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int64_fetch_and_incr_relaxed bitbyte_foundation_tier3_atomic_int64_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int64_t
bitbyte_foundation_tier3_atomic_int64_fetch_and_incr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int64_t *v)
{
  return bitbyte_foundation_tier3_atomic_int64_fetch_and_add_relaxed(v, 1);
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint64_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_atomic_uint64_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint64_fetch_and_incr_relaxed bitbyte_foundation_atomic_uint64_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint64_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint64_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint64_fetch_and_incr_relaxed bitbyte_foundation_tier3_atomic_uint64_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint64_t
bitbyte_foundation_tier3_atomic_uint64_fetch_and_incr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint64_t *v)
{
  return bitbyte_foundation_tier3_atomic_uint64_fetch_and_add_relaxed(v, 1);
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_ptr_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_atomic_ptr_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_ptr_fetch_and_incr_relaxed bitbyte_foundation_atomic_ptr_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_ptr_fetch_and_incr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_ptr_fetch_and_incr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_ptr_fetch_and_incr_relaxed bitbyte_foundation_tier3_atomic_ptr_fetch_and_incr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_ptr_t
bitbyte_foundation_tier3_atomic_ptr_fetch_and_incr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_ptr_t *v)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint32_fetch_and_incr_relaxed((volatile bitbyte_foundation_tier3_atomic_uint32_t *)v);
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint64_fetch_and_incr_relaxed((volatile bitbyte_foundation_tier3_atomic_uint64_t *)v);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int32_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_atomic_int32_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int32_fetch_and_decr_relaxed bitbyte_foundation_atomic_int32_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int32_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int32_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int32_fetch_and_decr_relaxed bitbyte_foundation_tier3_atomic_int32_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int32_t
bitbyte_foundation_tier3_atomic_int32_fetch_and_decr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int32_t *v)
{
  return bitbyte_foundation_tier3_atomic_int32_fetch_and_sub_relaxed(v, 1);
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint32_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_atomic_uint32_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint32_fetch_and_decr_relaxed bitbyte_foundation_atomic_uint32_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint32_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint32_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint32_fetch_and_decr_relaxed bitbyte_foundation_tier3_atomic_uint32_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint32_t
bitbyte_foundation_tier3_atomic_uint32_fetch_and_decr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint32_t *v)
{
  return bitbyte_foundation_tier3_atomic_uint32_fetch_and_sub_relaxed(v, 1);
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int64_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_atomic_int64_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int64_fetch_and_decr_relaxed bitbyte_foundation_atomic_int64_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int64_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int64_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int64_fetch_and_decr_relaxed bitbyte_foundation_tier3_atomic_int64_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int64_t
bitbyte_foundation_tier3_atomic_int64_fetch_and_decr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int64_t *v)
{
  return bitbyte_foundation_tier3_atomic_int64_fetch_and_sub_relaxed(v, 1);
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint64_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_atomic_uint64_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint64_fetch_and_decr_relaxed bitbyte_foundation_atomic_uint64_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint64_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint64_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint64_fetch_and_decr_relaxed bitbyte_foundation_tier3_atomic_uint64_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint64_t
bitbyte_foundation_tier3_atomic_uint64_fetch_and_decr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint64_t *v)
{
  return bitbyte_foundation_tier3_atomic_uint64_fetch_and_sub_relaxed(v, 1);
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_ptr_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_atomic_ptr_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_ptr_fetch_and_decr_relaxed bitbyte_foundation_atomic_ptr_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_ptr_fetch_and_decr_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_ptr_fetch_and_decr_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_ptr_fetch_and_decr_relaxed bitbyte_foundation_tier3_atomic_ptr_fetch_and_decr_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_ptr_t
bitbyte_foundation_tier3_atomic_ptr_fetch_and_decr_relaxed(
  volatile bitbyte_foundation_tier3_atomic_ptr_t *v)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint32_fetch_and_decr_relaxed((volatile bitbyte_foundation_tier3_atomic_uint32_t *)v);
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint64_fetch_and_decr_relaxed((volatile bitbyte_foundation_tier3_atomic_uint64_t *)v);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int32_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_atomic_int32_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int32_compare_and_swap_relaxed bitbyte_foundation_atomic_int32_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int32_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int32_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int32_compare_and_swap_relaxed bitbyte_foundation_tier3_atomic_int32_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int32_t
bitbyte_foundation_tier3_atomic_int32_compare_and_swap_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int32_t *v,
  bitbyte_foundation_tier3_atomic_int32_t expected,
  bitbyte_foundation_tier3_atomic_int32_t desired)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  return _InterlockedCompareExchange((volatile long *)v, (long)desired, (long)expected);
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint32_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_atomic_uint32_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint32_compare_and_swap_relaxed bitbyte_foundation_atomic_uint32_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint32_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint32_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint32_compare_and_swap_relaxed bitbyte_foundation_tier3_atomic_uint32_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint32_t
bitbyte_foundation_tier3_atomic_uint32_compare_and_swap_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint32_t *v,
  bitbyte_foundation_tier3_atomic_uint32_t expected,
  bitbyte_foundation_tier3_atomic_uint32_t desired)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  return _InterlockedCompareExchange((volatile long *)v, (long)desired, (long)expected);
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_int64_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_atomic_int64_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_int64_compare_and_swap_relaxed bitbyte_foundation_atomic_int64_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_int64_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_int64_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_int64_compare_and_swap_relaxed bitbyte_foundation_tier3_atomic_int64_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_int64_t
bitbyte_foundation_tier3_atomic_int64_compare_and_swap_relaxed(
  volatile bitbyte_foundation_tier3_atomic_int64_t *v,
  bitbyte_foundation_tier3_atomic_int64_t expected,
  bitbyte_foundation_tier3_atomic_int64_t desired)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  return _InterlockedCompareExchange64((volatile __int64 *)v, (__int64)desired, (__int64)expected);
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_uint64_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_atomic_uint64_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_uint64_compare_and_swap_relaxed bitbyte_foundation_atomic_uint64_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_uint64_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_uint64_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_uint64_compare_and_swap_relaxed bitbyte_foundation_tier3_atomic_uint64_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_uint64_t
bitbyte_foundation_tier3_atomic_uint64_compare_and_swap_relaxed(
  volatile bitbyte_foundation_tier3_atomic_uint64_t *v,
  bitbyte_foundation_tier3_atomic_uint64_t expected,
  bitbyte_foundation_tier3_atomic_uint64_t desired)
{
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  return _InterlockedCompareExchange64((volatile __int64 *)v, (__int64)desired, (__int64)expected);
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__) || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  return __sync_val_compare_and_swap(v, expected, desired);
#endif
}

//===----------------------------------------------------------------------===//

/// \def foundation_atomic_ptr_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_atomic_ptr_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_atomic_ptr_compare_and_swap_relaxed bitbyte_foundation_atomic_ptr_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_atomic_ptr_compare_and_swap_relaxed
/// \copydoc bitbyte_foundation_tier3_atomic_ptr_compare_and_swap_relaxed
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_atomic_ptr_compare_and_swap_relaxed bitbyte_foundation_tier3_atomic_ptr_compare_and_swap_relaxed
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief
///
static
bitbyte_foundation_tier3_atomic_ptr_t
bitbyte_foundation_tier3_atomic_ptr_compare_and_swap_relaxed(
  volatile bitbyte_foundation_tier3_atomic_ptr_t *v,
  bitbyte_foundation_tier3_atomic_ptr_t expected,
  bitbyte_foundation_tier3_atomic_ptr_t desired)
{
#if BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint32_compare_and_swap_relaxed((volatile bitbyte_foundation_tier3_atomic_uint32_t *)v,
                                                                                                                (bitbyte_foundation_tier3_atomic_uint32_t)expected,
                                                                                                                (bitbyte_foundation_tier3_atomic_uint32_t)desired);
#elif BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  return (bitbyte_foundation_tier3_atomic_ptr_t)bitbyte_foundation_tier3_atomic_uint64_compare_and_swap_relaxed((volatile bitbyte_foundation_tier3_atomic_uint64_t *)v,
                                                                                                                (bitbyte_foundation_tier3_atomic_uint64_t)expected,
                                                                                                                (bitbyte_foundation_tier3_atomic_uint64_t)desired);
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

/// \brief
///
template <typename _Type> class Atomic {};

//===----------------------------------------------------------------------===//

#define _Specialize(_Undecorated_type) \
  template <> \
  class Atomic<::bitbyte_foundation_tier3_atomic_##_Undecorated_type##_t> { \
   public: \
    typedef ::bitbyte_foundation_tier3_atomic_##_Undecorated_type##_t _Type_c; \
    typedef ::bitbyte::foundation::tier3::Atomic<_Type_c> _Type_cxx; \
   public: \
    Atomic(const _Type_c v) { this->store_relaxed(v); } \
    Atomic(const _Type_cxx &v) { this->store_relaxed(v.load_relaxed()); } \
    _Type_cxx &operator=(const _Type_c rhs) { this->store_relaxed(rhs); return *this; } \
    _Type_cxx &operator=(const _Type_cxx &rhs) { this->store_relaxed(rhs.load_relaxed()); return *this; } \
   public: \
    _Type_c load_relaxed() const { \
      return ::bitbyte_foundation_tier3_atomic_##_Undecorated_type##_load_relaxed(&this->__value__); } \
    void store_relaxed(const _Type_c desired) { \
      ::bitbyte_foundation_tier3_atomic_##_Undecorated_type##_store_relaxed(&this->__value__, desired); } \
    _Type_c fetch_and_add_relaxed(const _Type_c rhs) { \
      return ::bitbyte_foundation_tier3_atomic_##_Undecorated_type##_fetch_and_add_relaxed(&this->__value__, rhs); } \
    _Type_c fetch_and_sub_relaxed(const _Type_c rhs) { \
      return ::bitbyte_foundation_tier3_atomic_##_Undecorated_type##_fetch_and_sub_relaxed(&this->__value__, rhs); } \
    _Type_c fetch_and_incr_relaxed() { \
      return ::bitbyte_foundation_tier3_atomic_##_Undecorated_type##_fetch_and_incr_relaxed(&this->__value__); } \
    _Type_c fetch_and_decr_relaxed() { \
      return ::bitbyte_foundation_tier3_atomic_##_Undecorated_type##_fetch_and_decr_relaxed(&this->__value__); } \
    _Type_c compare_and_swap_relaxed(_Type_c expected, _Type_c desired) { \
      return ::bitbyte_foundation_tier3_atomic_##_Undecorated_type##_compare_and_swap_relaxed(&this->__value__, expected, desired); } \
   private: \
    _Type_c __value__; \
  };

_Specialize(int32)
_Specialize(uint32)
_Specialize(int64)
_Specialize(uint64)
_Specialize(ptr)

#undef _Specialize

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier3

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER3_ATOMICS_H_

//============================================================================//
