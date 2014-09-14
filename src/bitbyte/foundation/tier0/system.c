//===-- bitbyte/foundation/tier0/system.c -----------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier0/system.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

bitbyte_foundation_tier0_system_t
bitbyte_foundation_tier0_target_system(void)
{
  return (bitbyte_foundation_tier0_system_t)BITBYTE_FOUNDATION_TIER0_SYSTEM;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier0 {

//===----------------------------------------------------------------------===//

namespace target {

System
system(void)
{
  return (System)::bitbyte_foundation_tier0_target_system();
}

} // target

//===----------------------------------------------------------------------===//

} // tier0
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
