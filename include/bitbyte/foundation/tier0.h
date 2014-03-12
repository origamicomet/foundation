//=== bitbyte/foundation/tier0.h =============================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier0.h
/// @brief Includes bitbyte/foundation/tier0.h and imports tier0.
///

#ifndef _BITBYTE_FOUNDATION_TIER0_H_
#define _BITBYTE_FOUNDATION_TIER0_H_

/// @namespace ::bitbyte::foundation::tier0
/// @brief Detects the host and target platform, enforces (or implements if
///  required) standard behaviour for the standard library and compiler.
///
namespace bitbyte {
namespace foundation {

namespace tier0 {}
using namespace ::bitbyte::foundation::tier0;

} // foundation
} // bitbyte

#include <bitbyte/foundation/tier0/tier0.h>

#endif // _BITBYTE_FOUNDATION_TIER0_H_
