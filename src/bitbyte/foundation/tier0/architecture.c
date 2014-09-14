//===-- bitbyte/foundation/tier0/architecture.h -----------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier0/architecture.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

bitbyte_foundation_tier0_architecture_t
bitbyte_foundation_tier0_target_architecture(void)
{
  return (bitbyte_foundation_tier0_architecture_t)BITBYTE_FOUNDATION_TIER0_ARCHITECTURE;
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

Architecture
architecture(void)
{
  return (Architecture)::bitbyte_foundation_tier0_target_architecture();
}

} // target

//===----------------------------------------------------------------------===//

} // tier0
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
