//===-- bitbyte/foundation/tier2/debug/symbol.c -----------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier2/debug/symbol.h"

//============================================================================//

#include "bitbyte/foundation/tier0/compiler.h"
#include "bitbyte/foundation/tier0/system.h"
#include "bitbyte/foundation/tier1/malloc.h"
#include "bitbyte/foundation/tier1/stdio.h"

#include <string.h>

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
bitbyte_foundation_tier2_debug_symbol_from_address(
  void *address,
  bitbyte_foundation_tier2_debug_symbol_t *symbol)
{
  if (address == NULL)
    return false;
  if (symbol == NULL)
    return false;

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
    SYMBOL_INFO *si = (SYMBOL_INFO *)alloca(sizeof(SYMBOL_INFO) + 255);
    si->SizeOfStruct = sizeof(SYMBOL_INFO);
    si->MaxNameLen = 256;
    if (SymFromAddr(GetCurrentProcess(), (DWORD64)address, 0, si))
      strncpy(&symbol->name[0], &si->Name[0], 256);
    else
      snprintf(&symbol->name[0], 256, "%p", address);
    IMAGEHLP_LINE64 ihl;
    ihl.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    DWORD displacement = 0;
    if (SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)address, &displacement, &ihl)) {
      strncpy(&symbol->file[0], &ihl.FileName[0], 256);
      symbol->line = ihl.LineNumber;
    } else {
      symbol->file[0] = '\0';
      symbol->line = 0;
    }
  #elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__)   || \
        (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
    snprintf(&symbol->name[0], 256, "%p", address);
    symbol->file[0] = '\0';
    symbol->line = 0;
  #endif
#elif (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__) || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__)    || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__)  || \
      (BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__)
  char **symbols = backtrace_symbols(&address, 1);
  if (symbols != NULL) {
    strncpy(&symbol->name[0], symbols[0], 256);
    free((void *)symbols[0]);
    free((void *)symbols);
  } else {
    snprintf(&symbol->name[0], 256, "%p", address);
  }
  // TODO(mike): Extract file and line information.
  symbol->file[0] = '\0';
  symbol->line = 0;
#endif

  return true;
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

bool Symbol::from_address(void *address_, Symbol *symbol_)
{
  return ::bitbyte_foundation_tier2_debug_symbol_from_address(address_, symbol_);
}

//===----------------------------------------------------------------------===//

} // debug
} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
