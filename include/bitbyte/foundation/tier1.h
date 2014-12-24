//===-- bitbyte/foundation/tier1.h ------------------------------*- C++ -*-===//
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
/// \brief Imports tier1 into Foundation's namespace.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER1_H_
#define _BITBYTE_FOUNDATION_TIER1_H_

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {

/// \namespace ::bitbyte::foundation::tier1
/// \brief Enforces or implements standardized behaviour for the standard
/// library and compiler.
///
namespace tier1 {}

using namespace ::bitbyte::foundation::tier1;

} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#include "bitbyte/foundation/tier1/linkage.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier1/alignof.h"
#include "bitbyte/foundation/tier1/inttypes.h"
#include "bitbyte/foundation/tier1/malloc.h"
#include "bitbyte/foundation/tier1/stdbool.h"
#include "bitbyte/foundation/tier1/stdint.h"
#include "bitbyte/foundation/tier1/stdio.h"

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER1_H_

//============================================================================//
