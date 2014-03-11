//=== bitbyte/foundation/tier0/export.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier0/export.h
/// @brief Defines BITBYTE_FOUNDATION_TIER0_EXPORT based on configuration.
///

#ifndef _BITBYTE_FOUNDATION_TIER0_EXPORT_H_
#define _BITBYTE_FOUNDATION_TIER0_EXPORT_H_

//===----------------------------------------------------------------------===//
// Pre-processor defines
//

/// @def BITBYTE_FOUNDATION_TIER0_LINK_STATICALLY
/// @breif Linking to tier0 statically, e.g., using libtier0.a.
///
#define BITBYTE_FOUNDATION_TIER0_LINK_STATICALLY 1

/// @def BITBYTE_FOUNDATION_TIER0_LINK_DYNAMICALLY
/// @brief Linking to tier0 dynamically, e.g., using libtier0.so.
///
#define BITBYTE_FOUNDATION_TIER0_LINK_DYNAMICALLY 2

/// @def BITBYTE_FOUNDATION_TIER0_LINKAGE
/// @brief Specifies if tier0 is being linked to statically, or dynamically.
#ifndef BITBYTE_FOUNDATION_TIER0_LINKAGE
  #error ("Please specify how you are linking to Foundation by defining `BITBYTE_FOUNDATION_TIER0_LINKAGE`.")
#endif

/// @def BITBYTE_FOUNDATION_TIER0_EXPORT
/// @brief ...
///
#if (BITBYTE_FOUNDATION_TIER0_LINKAGE == BITBYTE_FOUNDATION_TIER0_LINK_STATICALLY)
  #define BITBYTE_FOUNDATION_TIER0_EXPORT
#elif (BITBYTE_FOUNDATION_TIER0_LINKAGE == BITBYTE_FOUNDATION_TIER0_LINK_DYNAMICALLY)
  #if defined(_MSC_VER)
    /// @def BITBYTE_FOUNDATION_TIER0_COMPILING
    /// @brief ...
    ///
    #if defined(BITBYTE_FOUNDATION_TIER0_COMPILING)
      #define BITBYTE_FOUNDATION_TIER0_EXPORT __declspec(dllexport)
    #else
      #define BITBYTE_FOUNDATION_TIER0_EXPORT __declspec(dllimport)
    #endif
  #else
    #define BITBYTE_FOUNDATION_TIER0_EXPORT
  #endif
#endif

#endif // _BITBYTE_FOUNDATION_TIER0_EXPORT_H_
