//===-- bitbyte/foundation/tier0.h ------------------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mwilliams@bitbyte.ca>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Imports tier0 into Foundation's namespace.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER0_H_
#define _BITBYTE_FOUNDATION_TIER0_H_

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {

/// \namespace ::bitbyte::foundation::tier0
/// \brief Detects compiler and target platform (architecture and system).
///
namespace tier0 {}

using namespace ::bitbyte::foundation::tier0;

} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#include "bitbyte/foundation/tier0/linkage.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier0/architecture.h"
#include "bitbyte/foundation/tier0/compiler.h"
#include "bitbyte/foundation/tier0/system.h"

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER0_H_

//============================================================================//
