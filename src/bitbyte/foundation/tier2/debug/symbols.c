//===-- bitbyte/foundation/tier2/symbols.c ----------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier2/debug/symbols.h"

//============================================================================//

#include "bitbyte/foundation/tier0/compiler.h"
#include "bitbyte/foundation/tier0/system.h"

//============================================================================//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
    #include <windows.h>
    #include <dbghelp.h>
  #elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__)   || \
        (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  #endif
#elif (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__) || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__)    || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__)  || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__)
  #include <execinfo.h>
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

bool
bitbyte_foundation_tier2_load_debug_symbols(void)
{
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
    SymCleanup(GetCurrentProcess());
    SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_OMAP_FIND_NEAREST);
    return !!SymInitialize(GetCurrentProcess(), NULL, TRUE);
  #elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__)   || \
        (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
    return true;
  #endif
#elif (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__) || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__)    || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__)  || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__)
  return true;
#endif
}

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier2_unload_debug_symbols(void)
{
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
    SymCleanup(GetCurrentProcess());
  #elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__)   || \
        (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  #endif
#elif (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__) || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__)    || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__)  || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__)
#endif
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
namespace tier2 {
namespace debug {

//===----------------------------------------------------------------------===//

bool Symbols::load(void)
{
  return ::bitbyte_foundation_tier2_load_debug_symbols();
}

//===----------------------------------------------------------------------===//

void Symbols::unload(void)
{
  ::bitbyte_foundation_tier2_unload_debug_symbols();
}

//===----------------------------------------------------------------------===//

} // debug
} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
