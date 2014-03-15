//=== bitbyte/foundation/tier2/atomic.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier2/atomic.h
/// @brief Provides atomic types and operations.
///

#ifndef _BITBYTE_FOUNDATION_TIER2_ATOMICS_H_
#define _BITBYTE_FOUNDATION_TIER2_ATOMICS_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/export.h>

namespace bitbyte {
namespace foundation {
namespace tier2 {

//===----------------------------------------------------------------------===//
// Types
//

namespace atomic {

typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

#if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86)
  typedef u32 ptr;
#elif (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE == BITBYTE_FOUNDATION_ARCHITECTURE_X86_64)
  typedef u64 ptr;
#endif

} // atomic

//===----------------------------------------------------------------------===//
// Load & Store
//

namespace atomic {
namespace relaxed {

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s32 load(
  volatile atomic::s32 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT void store(
  volatile atomic::s32 *v,
  atomic::s32 desired);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u32 load(
  volatile atomic::u32 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT void store(
  volatile atomic::u32 *v,
  atomic::u32 desired);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s64 load(
  volatile atomic::s64 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT void store(
  volatile atomic::s64 *v,
  atomic::s64 desired);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u64 load(
  volatile atomic::u64 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT void store(
  volatile atomic::u64 *v,
  atomic::u64 desired);

} // relaxed
} // atomic

//===----------------------------------------------------------------------===//
// Increment & Decrement
//

namespace atomic {
namespace relaxed {

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s32 increment(
  volatile atomic::s32 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s32 decrement(
  volatile atomic::s32 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u32 increment(
  volatile atomic::u32 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u32 decrement(
  volatile atomic::u32 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s64 increment(
  volatile atomic::s64 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s64 decrement(
  volatile atomic::s64 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u64 increment(
  volatile atomic::u64 *v);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u64 decrement(
  volatile atomic::u64 *v);

} // relaxed
} // atomic

//===----------------------------------------------------------------------===//
// Add & Subtract
//

namespace atomic {
namespace relaxed {

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s32 add(
  volatile atomic::s32 *lhs,
  atomic::s32 rhs);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s32 sub(
  volatile atomic::s32 *lhs,
  atomic::s32 rhs);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u32 add(
  volatile atomic::u32 *lhs,
  atomic::u32 rhs);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u32 sub(
  volatile atomic::u32 *lhs,
  atomic::u32 rhs);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s64 add(
  volatile atomic::s64 *lhs,
  atomic::s64 rhs);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s64 sub(
  volatile atomic::s64 *lhs,
  atomic::s64 rhs);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u64 add(
  volatile atomic::u64 *lhs,
  atomic::u64 rhs);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u64 sub(
  volatile atomic::u64 *lhs,
  atomic::u64 rhs);

} // relaxed
} // atomic

//===----------------------------------------------------------------------===//
// Compare and Swap
//

namespace atomic {
namespace relaxed {

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s32 compare_and_swap(
  volatile atomic::s32 *v,
  atomic::s32 expected,
  atomic::s32 desired);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u32 compare_and_swap(
  volatile atomic::u32 *v,
  atomic::u32 expected,
  atomic::u32 desired);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::s64 compare_and_swap(
  volatile atomic::s64 *v,
  atomic::s64 expected,
  atomic::s64 desired);

/// ...
extern BITBYTE_FOUNDATION_TIER2_EXPORT atomic::u64 compare_and_swap(
  volatile atomic::u64 *v,
  atomic::u64 expected,
  atomic::u64 desired);

} // relaxed
} // atomic

} // tier2
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER2_ATOMICS_H_
