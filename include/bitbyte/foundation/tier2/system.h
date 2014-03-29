//=== bitbyte/foundation/tier2/system.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier2/system.h
/// @brief Provides system queries.
///

#ifndef _BITBYTE_FOUNDATION_TIER2_SYSTEM_H_
#define _BITBYTE_FOUNDATION_TIER2_SYSTEM_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/export.h>

namespace bitbyte {
namespace foundation {
namespace tier2 {

//===----------------------------------------------------------------------===//
// Processors
//

namespace system {

/// @brief
///
extern BITBYTE_FOUNDATION_TIER2_EXPORT size_t num_logical_processors();

/// @brief
///
extern BITBYTE_FOUNDATION_TIER2_EXPORT size_t num_physical_processors();

} // system

} // tier2
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER2_SYSTEM_H_
