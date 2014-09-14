//===-- bitbyte/foundation/tier0/compiler.c ---------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier0/compiler.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

bitbyte_foundation_tier0_compiler_t
bitbyte_foundation_tier0_host_compiler(void)
{
  return (bitbyte_foundation_tier0_compiler_t)BITBYTE_FOUNDATION_TIER0_COMPILER;
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

namespace host {

Compiler
compiler(void)
{
  return (Compiler)::bitbyte_foundation_tier0_host_compiler();
}

} // host

//===----------------------------------------------------------------------===//

} // tier0
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
