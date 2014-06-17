//===-- bitbyte/foundation/tier2/debug/symbols.h ----------------*- C++ -*-===//
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
/// \brief Platform agnostic symbols information.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER2_DEBUG_SYMBOLS_H_
#define _BITBYTE_FOUNDATION_TIER2_DEBUG_SYMBOLS_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdbool.h"
#include "bitbyte/foundation/tier2/linkage.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \def foundation_load_debug_symbols
/// \copydoc bitbyte_foundation_load_debug_symbols
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_load_debug_symbols bitbyte_foundation_load_debug_symbols
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_load_debug_symbols
/// \copydoc bitbyte_foundation_tier2_load_debug_symbols
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_load_debug_symbols bitbyte_foundation_tier2_load_debug_symbols
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Loads symbols information for the current process.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
bitbyte_foundation_tier2_load_debug_symbols(void);

//===----------------------------------------------------------------------===//

/// \def foundation_unload_debug_symbols
/// \copydoc bitbyte_foundation_unload_debug_symbols
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_unload_debug_symbols bitbyte_foundation_unload_debug_symbols
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_unload_debug_symbols
/// \copydoc bitbyte_foundation_tier2_unload_debug_symbols
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_unload_debug_symbols bitbyte_foundation_tier2_unload_debug_symbols
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Unloads symbols information for the current process.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
void
bitbyte_foundation_tier2_unload_debug_symbols(void);

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

namespace Symbols {

/// \copydoc ::bitbyte_foundation_tier2_load_debug_symbols
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
load(void);

/// \copydoc ::bitbyte_foundation_tier2_unload_debug_symbols
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
void
unload(void);

} // Symbols

//===----------------------------------------------------------------------===//

} // debug
} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER2_DEBUG_SYMBOLS_H_

//============================================================================//
