//=== bitbyte/foundation/tier1/heap.h ========================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier1/heap.h
/// @brief Provides a foundation::tier1::Allocator interface for the heap.
///

#ifndef _BITBYTE_FOUNDATION_TIER1_HEAP_H_
#define _BITBYTE_FOUNDATION_TIER1_HEAP_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/export.h>
#include <bitbyte/foundation/tier1/allocator.h>

namespace bitbyte {
namespace foundation {
namespace tier1 {

/// ...
extern BITBYTE_FOUNDATION_TIER1_EXPORT Allocator &heap();

} // tier1
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER1_HEAP_H_
