//===-- bitbyte/foundation/tier4.h ------------------------------*- C++ -*-===//
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
/// \brief Imports tier4 into Foundation's namespace.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER4_H_
#define _BITBYTE_FOUNDATION_TIER4_H_

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {

/// \namespace ::bitbyte::foundation::tier4
/// \brief Implements various data-structures and algorithims.
///
namespace tier4 {}

using namespace ::bitbyte::foundation::tier4;

} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#include "bitbyte/foundation/tier4/linkage.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier4/allocator.h"
#include "bitbyte/foundation/tier4/heap.h"
#include "bitbyte/foundation/tier4/uuid.h"

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER4_H_

//============================================================================//
