//===-- bitbyte/foundation/tier2/debug/symbol.h -----------------*- C++ -*-===//
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
/// \brief Platform agnostic symbol information.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER2_DEBUG_SYMBOL_H_
#define _BITBYTE_FOUNDATION_TIER2_DEBUG_SYMBOL_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdbool.h"
#include "bitbyte/foundation/tier2/linkage.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief Debug symbol information.
///
typedef struct bitbyte_foundation_tier2_debug_symbol {
  char name[256];
  char file[256];
  unsigned line;
} bitbyte_foundation_tier2_debug_symbol_t;

/// \copydoc bitbyte_foundation_tier2_debug_symbol_t
typedef bitbyte_foundation_tier2_debug_symbol_t bitbyte_foundation_debug_symbol_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_debug_symbol_t
  typedef bitbyte_foundation_debug_symbol_t foundation_debug_symbol_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_debug_symbol_from_address
/// \copydoc bitbyte_foundation_debug_symbol_from_address
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_debug_symbol_from_address bitbyte_foundation_debug_symbol_from_address
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_debug_symbol_from_address
/// \copydoc bitbyte_foundation_tier2_debug_symbol_from_address
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_debug_symbol_from_address bitbyte_foundation_tier2_debug_symbol_from_address
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Retrieves symbol information for the specified `address`.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
bitbyte_foundation_tier2_debug_symbol_from_address(
  void *address,
  bitbyte_foundation_tier2_debug_symbol_t *symbol);

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

/// \copydoc ::bitbyte_foundation_tier2_debug_symbol_t
class BITBYTE_FOUNDATION_TIER2_EXPORT Symbol :
  public bitbyte_foundation_tier2_debug_symbol_t
{
 public:
  // \copydoc ::bitbyte_foundation_tier2_debug_symbol_from_address
  static bool from_address(void *address, Symbol *symbol);
};

//===----------------------------------------------------------------------===//

} // debug
} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER2_DEBUG_SYMBOL_H_

//============================================================================//
