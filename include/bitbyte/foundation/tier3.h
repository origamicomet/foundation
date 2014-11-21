//===-- bitbyte/foundation/tier3.h ------------------------------*- C++ -*-===//
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
///
/// \file
/// \brief Imports tier3 into Foundation's namespace.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER3_H_
#define _BITBYTE_FOUNDATION_TIER3_H_

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {

/// \namespace ::bitbyte::foundation::tier3
/// \brief Abstracts platform-specific APIs.
///
namespace tier3 {}

using namespace ::bitbyte::foundation::tier3;

} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#include "bitbyte/foundation/tier3/linkage.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier3/cpu.h"
#include "bitbyte/foundation/tier3/timer.h"

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER3_H_

//============================================================================//
