/* ========================================================================== */
/*                                                                            */
/* This file is part of Foundation.                                           */
/*                                                                            */
/* Author(s):                                                                 */
/*                                                                            */
/*   Michael Williams <devbug@bitbyte.ca>                                     */
/*                                                                            */
/* This is free and unencumbered software released into the public domain.    */
/*                                                                            */
/* Anyone is free to copy, modify, publish, use, compile, sell, or distribute */
/* this software, either in source code form or as a compiled binary, for any */
/* purpose, commercial or non-commercial, and by any means.                   */
/*                                                                            */
/* In jurisdictions that recognize copyright laws, the author or authors of   */
/* this software dedicate any and all copyright interest in the software to   */
/* the public domain. We make this dedication for the benefit of the public   */
/* large and to the detriment of our heirs and successors. We intend this     */
/* dedication to be an overt act of relinquishment in perpetuity of all       */
/* present and future rights to this software under copyright law.            */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   */
/* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR      */
/* OTHER DEALINGS IN THE SOFTWARE.                                            */
/*                                                                            */
/* For more information, please refer to <http://unlicense.org/>              */
/*                                                                            */
/* ========================================================================== */
/*! @file include/foundation/atomics.h
     Provides compiler, architecture, and platform independent atomic types
     and operations.                                                          */
/* ========================================================================== */

#ifndef _FOUNDATION_ATOMICS_H_
#define _FOUNDATION_ATOMICS_H_

#include <foundation/config.h>
#include <foundation/detect/compiler.h>
#include <foundation/detect/platform.h>
#include <foundation/detect/architecture.h>
#include <foundation/compat/stdint.h>
#include <foundation/compat/inttypes.h>

/* ========================================================================== */
/*  Atomics:                                                                  */
/*   * Types;                                                                 */
/*   * Load & Store;                                                          */
/*   * Increment & Add;                                                       */
/*   * Decrement & Sub;                                                       */
/*   * Compare and Swap;                                                      */
/*   * C++ (foundation::atomic::*).                                           */
/* ========================================================================== */

#if (FND_COMPILER == FND_COMPILER_MSVC)
  #include <intrin.h>
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedCompareExchange)
  #elif (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedExchangeAdd64)
    #pragma intrinsic(_InterlockedCompareExchange)
    #pragma intrinsic(_InterlockedCompareExchange64)
  #elif (FND_ARCHITECTURE == FND_ARCHITECTURE_ARM)
    #error ("Not implemented, yet.")
  #else
    #error ("Unknown or unsupported platform.")
  #endif
#elif (FND_COMPILER == FND_COMPILER_GCC)   || \
      (FND_COMPILER == FND_COMPILER_CLANG)
  #error ("Not implemented, yet.")
#else
  #error ("Unknown or unsupported compiler.")
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*  Types:                                                                    */
/* ========================================================================== */

typedef int32_t fnd_atomic_int32_t;
typedef uint32_t fnd_atomic_uint32_t;
typedef uintptr_t fnd_atomic_ptr_t;

/* ========================================================================== */
/*  Load & Store:                                                             */
/* ========================================================================== */

/*! */
static fnd_atomic_int32_t fnd_atomic_int32_load_relaxed(
  fnd_atomic_int32_t *v)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    return *v;
  #endif
#endif
}

/*! */
static void fnd_atomic_int32_store_relaxed(
  fnd_atomic_int32_t *v,
  fnd_atomic_int32_t desired)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    *v = desired;
  #endif
#endif
}

/*! */
static fnd_atomic_uint32_t fnd_atomic_uint32_load_relaxed(
  fnd_atomic_uint32_t *v)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    return *v;
  #endif
#endif
}

/*! */
static void fnd_atomic_uint32_store_relaxed(
  fnd_atomic_uint32_t *v,
  fnd_atomic_uint32_t desired)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    *v = desired;
  #endif
#endif
}

/*! */
static fnd_atomic_ptr_t fnd_atomic_ptr_load_relaxed(
  fnd_atomic_ptr_t *v)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    return *v;
  #endif
#endif
}

/*! */
static void fnd_atomic_ptr_store_relaxed(
  fnd_atomic_ptr_t *v,
  fnd_atomic_ptr_t desired)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    *v = desired;
  #endif
#endif
}

/* ========================================================================== */
/*  Increment & Add:                                                          */
/* ========================================================================== */

/*! */
static fnd_atomic_int32_t fnd_atomic_int32_fetch_add_relaxed(
  fnd_atomic_int32_t *lhs,
  fnd_atomic_int32_t rhs)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    return (fnd_atomic_int32_t)_InterlockedExchangeAdd((long volatile *)lhs, (long)rhs);
  #endif
#endif
}

/*! */
static fnd_atomic_int32_t fnd_atomic_int32_fetch_increment_relaxed(
  fnd_atomic_int32_t *v)
{
  return fnd_atomic_int32_fetch_add_relaxed(v, (fnd_atomic_int32_t)1);
}

/*! */
static fnd_atomic_uint32_t fnd_atomic_uint32_fetch_add_relaxed(
  fnd_atomic_uint32_t *lhs,
  fnd_atomic_uint32_t rhs)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    return (fnd_atomic_uint32_t)_InterlockedExchangeAdd((long volatile *)lhs, (long)rhs);
  #endif
#endif
}

/*! */
static fnd_atomic_uint32_t fnd_atomic_uint32_fetch_increment_relaxed(
  fnd_atomic_uint32_t *v)
{
  return fnd_atomic_uint32_fetch_add_relaxed(v, (fnd_atomic_uint32_t)1);
}

/*! */
static fnd_atomic_ptr_t fnd_atomic_ptr_fetch_add_relaxed(
  fnd_atomic_ptr_t *lhs,
  fnd_atomic_ptr_t rhs)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)
    return (fnd_atomic_ptr_t)_InterlockedExchangeAdd((long volatile *)lhs, (long)rhs);
  #elif (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    return (fnd_atomic_ptr_t)_InterlockedExchangeAdd64((__int64 volatile *)lhs, (__int64)rhs);
  #endif
#endif
}

/*! */
static fnd_atomic_ptr_t fnd_atomic_ptr_fetch_increment_relaxed(
  fnd_atomic_ptr_t *v)
{
  return fnd_atomic_ptr_fetch_add_relaxed(v, (fnd_atomic_ptr_t)1);
}

/* ========================================================================== */
/*  Decrement & Sub:                                                          */
/* ========================================================================== */

/*! */
static fnd_atomic_int32_t fnd_atomic_int32_fetch_sub_relaxed(
  fnd_atomic_int32_t *lhs,
  fnd_atomic_int32_t rhs)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    fnd_atomic_int32_t v, v_;
    do {
      v = *lhs; v_ = v - rhs;
    } while(_InterlockedCompareExchange((long volatile *)lhs, (long)v_, (long)v) != (long)v);
    return v;
  #endif
#endif
}

/*! */
static fnd_atomic_int32_t fnd_atomic_int32_fetch_decrement_relaxed(
  fnd_atomic_int32_t *v)
{
  return fnd_atomic_int32_fetch_sub_relaxed(v, (fnd_atomic_int32_t)1);
}

/*! */
static fnd_atomic_uint32_t fnd_atomic_uint32_fetch_sub_relaxed(
  fnd_atomic_uint32_t *lhs,
  fnd_atomic_uint32_t rhs)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    fnd_atomic_uint32_t v, v_;
    do {
      v = *lhs; v_ = v - rhs;
    } while(_InterlockedCompareExchange((long volatile *)lhs, (long)v_, (long)v) != (long)v);
    return v;
  #endif
#endif
}

/*! */
static fnd_atomic_uint32_t fnd_atomic_uint32_fetch_decrement_relaxed(
  fnd_atomic_uint32_t *v)
{
  return fnd_atomic_uint32_fetch_sub_relaxed(v, (fnd_atomic_uint32_t)1);
}

/*! */
static fnd_atomic_ptr_t fnd_atomic_ptr_fetch_sub_relaxed(
  fnd_atomic_ptr_t *lhs,
  fnd_atomic_ptr_t rhs)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)
    fnd_atomic_ptr_t v, v_;
    do {
      v = *lhs; v_ = v - rhs;
    } while(_InterlockedCompareExchange((long volatile *)lhs, (long)v_, (long)v) != (long)v);
    return v;
  #elif (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    fnd_atomic_ptr_t v, v_;
    do {
      v = *lhs; v_ = v - rhs;
    } while(_InterlockedCompareExchange64((__int64 volatile *)lhs, (__int64)v_, (__int64)v) != (__int64)v);
    return v;
  #endif
#endif
}

/*! */
static fnd_atomic_ptr_t fnd_atomic_ptr_fetch_decrement_relaxed(
  fnd_atomic_ptr_t *v)
{
  return fnd_atomic_ptr_fetch_sub_relaxed(v, (fnd_atomic_ptr_t)1);
}

/* ========================================================================== */
/*  Compare and Swap:                                                         */
/* ========================================================================== */

/*! */
static fnd_atomic_int32_t fnd_atomic_int32_compare_swap_relaxed(
  fnd_atomic_int32_t *v,
  fnd_atomic_int32_t expected,
  fnd_atomic_int32_t desired)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)

    return (fnd_atomic_int32_t)_InterlockedCompareExchange((long volatile *)v, (long)desired, (long)expected);
  #endif
#endif
}

/*! */
static fnd_atomic_uint32_t fnd_atomic_uint32_compare_swap_relaxed(
  fnd_atomic_uint32_t *v,
  fnd_atomic_uint32_t expected,
  fnd_atomic_uint32_t desired)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)    || \
      (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    return (fnd_atomic_uint32_t)_InterlockedCompareExchange((long volatile *)v, (long)desired, (long)expected);
  #endif
#endif
}

/*! */
static fnd_atomic_ptr_t fnd_atomic_ptr_compare_swap_relaxed(
  fnd_atomic_ptr_t *v,
  fnd_atomic_ptr_t expected,
  fnd_atomic_ptr_t desired)
{
#if (FND_COMPILER == FND_COMPILER_MSVC)
  #if (FND_ARCHITECTURE == FND_ARCHITECTURE_X86)
    return (fnd_atomic_ptr_t)_InterlockedCompareExchange((long volatile *)v, (long)desired, (long)expected);
  #elif (FND_ARCHITECTURE == FND_ARCHITECTURE_X86_64)
    return (fnd_atomic_ptr_t)_InterlockedCompareExchange64((__int64 volatile *)v, (__int64)desired, (__int64)expected);
  #endif
#endif
}

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::atomic::*).                                              */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
  namespace atomic {
    /* ====================================================================== */
    /*  Types:                                                                */
    /* ====================================================================== */
    /*! @copydoc fnd_atomic_int32_t */
    typedef fnd_atomic_int32_t int32;
    /*! @copydoc fnd_atomic_uint32_t */
    typedef fnd_atomic_uint32_t uint32;
    /*! @copydoc fnd_atomic_ptr_t */
    typedef fnd_atomic_ptr_t ptr;

    /* ====================================================================== */
    /*  Load & Store:                                                         */
    /* ====================================================================== */
    /*! @copydoc fnd_atomic_int32_load_relaxed */
    static int32 load_relaxed(int32 *v) {
      return fnd_atomic_int32_load_relaxed(v); }
    /*! @copydoc fnd_atomic_int32_store_relaxed */
    static void store_relaxed(int32 *v, int32 desired) {
      return fnd_atomic_int32_store_relaxed(v, desired); }
    /*! @copydoc fnd_atomic_uint32_load_relaxed */
    static uint32 load_relaxed(uint32 *v) {
      return fnd_atomic_uint32_load_relaxed(v); }
    /*! @copydoc fnd_atomic_uint32_store_relaxed */
    static void store_relaxed(uint32 *v, uint32 desired) {
      return fnd_atomic_uint32_store_relaxed(v, desired); }
    /*! @copydoc fnd_atomic_ptr_load_relaxed */
    static ptr load_relaxed(ptr *v) {
      return fnd_atomic_ptr_load_relaxed(v); }
    /*! @copydoc fnd_atomic_ptr_store_relaxed */
    static void store_relaxed(ptr *v, ptr desired) {
      return fnd_atomic_ptr_store_relaxed(v, desired); }

    /* ====================================================================== */
    /*  Add & Increment:                                                      */
    /* ====================================================================== */
    /*! @copydoc fnd_atomic_int32_fetch_add_relaxed */
    static int32 fetch_add_relaxed(int32 *lhs, int32 rhs) {
      return fnd_atomic_int32_fetch_add_relaxed(lhs, rhs); }
    /*! @copydoc fnd_atomic_int32_fetch_increment_relaxed */
    static int32 fetch_increment_relaxed(int32 *v) {
      return fnd_atomic_int32_fetch_increment_relaxed(v); }
    /*! @copydoc fnd_atomic_uint32_fetch_add_relaxed */
    static uint32 fetch_add_relaxed(uint32 *lhs, uint32 rhs) {
      return fnd_atomic_uint32_fetch_add_relaxed(lhs, rhs); }
    /*! @copydoc fnd_atomic_uint32_fetch_increment_relaxed */
    static uint32 fetch_increment_relaxed(uint32 *v) {
      return fnd_atomic_uint32_fetch_increment_relaxed(v); }
    /*! @copydoc fnd_atomic_ptr_fetch_add_relaxed */
    static ptr fetch_add_relaxed(ptr *lhs, ptr rhs) {
      return fnd_atomic_ptr_fetch_add_relaxed(lhs, rhs); }
    /*! @copydoc fnd_atomic_ptr_fetch_increment_relaxed */
    static ptr fetch_increment_relaxed(ptr *v) {
      return fnd_atomic_ptr_fetch_increment_relaxed(v); }

    /* ====================================================================== */
    /*  Sub & Decrement:                                                      */
    /* ====================================================================== */
    /*! @copydoc fnd_atomic_int32_fetch_sub_relaxed */
    static int32 fetch_sub_relaxed(int32 *lhs, int32 rhs) {
      return fnd_atomic_int32_fetch_sub_relaxed(lhs, rhs); }
    /*! @copydoc fnd_atomic_int32_fetch_decrement_relaxed */
    static int32 fetch_decrement_relaxed(int32 *v) {
      return fnd_atomic_int32_fetch_decrement_relaxed(v); }
    /*! @copydoc fnd_atomic_uint32_fetch_sub_relaxed */
    static uint32 fetch_sub_relaxed(uint32 *lhs, uint32 rhs) {
      return fnd_atomic_uint32_fetch_sub_relaxed(lhs, rhs); }
    /*! @copydoc fnd_atomic_uint32_fetch_decrement_relaxed */
    static uint32 fetch_decrement_relaxed(uint32 *v) {
      return fnd_atomic_uint32_fetch_decrement_relaxed(v); }
    /*! @copydoc fnd_atomic_ptr_fetch_sub_relaxed */
    static ptr fetch_sub_relaxed(ptr *lhs, ptr rhs) {
      return fnd_atomic_ptr_fetch_sub_relaxed(lhs, rhs); }
    /*! @copydoc fnd_atomic_ptr_fetch_decrement_relaxed */
    static ptr fetch_decrement_relaxed(ptr *v) {
      return fnd_atomic_ptr_fetch_decrement_relaxed(v); }

    /* ====================================================================== */
    /*  Compare and Swap:                                                     */
    /* ====================================================================== */
    /*! @copydoc fnd_atomic_int32_compare_swap_relaxed */
    static int32 compare_swap_relaxed(int32 *v, int32 expected, int32 desired) {
      return fnd_atomic_int32_compare_swap_relaxed(v, expected, desired); }
    /*! @copydoc fnd_atomic_uint32_compare_swap_relaxed */
    static uint32 compare_swap_relaxed(uint32 *v, uint32 expected, uint32 desired) {
      return fnd_atomic_uint32_compare_swap_relaxed(v, expected, desired); }
    /*! @copydoc fnd_atomic_ptr_compare_swap_relaxed */
    static ptr compare_swap_relaxed(ptr *v, ptr expected, ptr desired) {
      return fnd_atomic_ptr_compare_swap_relaxed(v, expected, desired); }
  } /* atomic */
} /* foundation */
#endif

#endif /* _FOUNDATION_ATOMICS_H_ */
