//=== bitbyte/foundation/tier3/export.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier3/export.h
/// @brief Defines BITBYTE_FOUNDATION_TIER3_EXPORT based on configuration.
///

#ifndef _BITBYTE_FOUNDATION_TIER3_EXPORT_H_
#define _BITBYTE_FOUNDATION_TIER3_EXPORT_H_

//===----------------------------------------------------------------------===//
// Pre-processor defines
//

/// @def BITBYTE_FOUNDATION_TIER3_LINK_STATICALLY
/// @breif Linking to tier3 statically, e.g., using libtier3.a.
///
#define BITBYTE_FOUNDATION_TIER3_LINK_STATICALLY 1

/// @def BITBYTE_FOUNDATION_TIER3_LINK_DYNAMICALLY
/// @brief Linking to tier3 dynamically, e.g., using libtier3.so.
///
#define BITBYTE_FOUNDATION_TIER3_LINK_DYNAMICALLY 2

/// @def BITBYTE_FOUNDATION_TIER3_LINKAGE
/// @brief Specifies if tier3 is being linked to statically, or dynamically.
#ifndef BITBYTE_FOUNDATION_TIER3_LINKAGE
  #error ("Please specify how you are linking to Foundation by defining `BITBYTE_FOUNDATION_TIER3_LINKAGE`.")
#endif

/// @def BITBYTE_FOUNDATION_TIER3_EXPORT
/// @brief ...
///
#if (BITBYTE_FOUNDATION_TIER3_LINKAGE == BITBYTE_FOUNDATION_TIER3_LINK_STATICALLY)
  #define BITBYTE_FOUNDATION_TIER3_EXPORT
#elif (BITBYTE_FOUNDATION_TIER3_LINKAGE == BITBYTE_FOUNDATION_TIER3_LINK_DYNAMICALLY)
  #if defined(_MSC_VER)
    /// @def BITBYTE_FOUNDATION_TIER3_COMPILING
    /// @brief ...
    ///
    #if defined(BITBYTE_FOUNDATION_TIER3_COMPILING)
      #define BITBYTE_FOUNDATION_TIER3_EXPORT __declspec(dllexport)
    #else
      #define BITBYTE_FOUNDATION_TIER3_EXPORT __declspec(dllimport)
    #endif
  #else
    #define BITBYTE_FOUNDATION_TIER3_EXPORT
  #endif
#endif

#endif // _BITBYTE_FOUNDATION_TIER3_EXPORT_H_
