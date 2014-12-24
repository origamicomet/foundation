//===-- bitbyte/foundation/tier4/heap.h -------------------------*- C++ -*-===//
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
/// \brief Provides a heap allocator.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER4_HEAP_H_
#define _BITBYTE_FOUNDATION_TIER4_HEAP_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdint.h"
#include "bitbyte/foundation/tier4/linkage.h"
#include "bitbyte/foundation/tier4/allocator.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \def foundation_heap
/// \copydoc bitbyte_foundation_heap
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_heap bitbyte_foundation_heap
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_heap
/// \copydoc bitbyte_foundation_tier4_allocator_to_s
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_heap bitbyte_foundation_tier4_heap
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief QQQ
///
extern
BITBYTE_FOUNDATION_TIER4_EXPORT
bitbyte_foundation_allocator_t *
bitbyte_foundation_tier4_heap(void);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier4 {

//===----------------------------------------------------------------------===//

/// \copydoc ::bitbyte_foundation_tier4_heap
extern
BITBYTE_FOUNDATION_TIER4_EXPORT
Allocator *
heap(void);

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier4

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER4_HEAP_H_

//============================================================================//
