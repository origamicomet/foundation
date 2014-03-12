//=== bitbyte/foundation/tier1/export.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier1/export.h
/// @brief Defines BITBYTE_FOUNDATION_TIER1_EXPORT based on configuration.
///

#ifndef _BITBYTE_FOUNDATION_TIER1_EXPORT_H_
#define _BITBYTE_FOUNDATION_TIER1_EXPORT_H_

//===----------------------------------------------------------------------===//
// Pre-processor defines
//

/// @def BITBYTE_FOUNDATION_TIER1_LINK_STATICALLY
/// @breif Linking to tier1 statically, e.g., using libtier1.a.
///
#define BITBYTE_FOUNDATION_TIER1_LINK_STATICALLY 1

/// @def BITBYTE_FOUNDATION_TIER1_LINK_DYNAMICALLY
/// @brief Linking to tier1 dynamically, e.g., using libtier1.so.
///
#define BITBYTE_FOUNDATION_TIER1_LINK_DYNAMICALLY 2

/// @def BITBYTE_FOUNDATION_TIER1_LINKAGE
/// @brief Specifies if tier1 is being linked to statically, or dynamically.
#ifndef BITBYTE_FOUNDATION_TIER1_LINKAGE
  #error ("Please specify how you are linking to Foundation by defining `BITBYTE_FOUNDATION_TIER1_LINKAGE`.")
#endif

/// @def BITBYTE_FOUNDATION_TIER1_EXPORT
/// @brief ...
///
#if (BITBYTE_FOUNDATION_TIER1_LINKAGE == BITBYTE_FOUNDATION_TIER1_LINK_STATICALLY)
  #define BITBYTE_FOUNDATION_TIER1_EXPORT
#elif (BITBYTE_FOUNDATION_TIER1_LINKAGE == BITBYTE_FOUNDATION_TIER1_LINK_DYNAMICALLY)
  #if defined(_MSC_VER)
    /// @def BITBYTE_FOUNDATION_TIER1_COMPILING
    /// @brief ...
    ///
    #if defined(BITBYTE_FOUNDATION_TIER1_COMPILING)
      #define BITBYTE_FOUNDATION_TIER1_EXPORT __declspec(dllexport)
    #else
      #define BITBYTE_FOUNDATION_TIER1_EXPORT __declspec(dllimport)
    #endif
  #else
    #define BITBYTE_FOUNDATION_TIER1_EXPORT
  #endif
#endif

#endif // _BITBYTE_FOUNDATION_TIER1_EXPORT_H_
