//=== bitbyte/foundation/tier2/export.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier2/export.h
/// @brief Defines BITBYTE_FOUNDATION_TIER2_EXPORT based on configuration.
///

#ifndef _BITBYTE_FOUNDATION_TIER2_EXPORT_H_
#define _BITBYTE_FOUNDATION_TIER2_EXPORT_H_

//===----------------------------------------------------------------------===//
// Pre-processor defines
//

/// @def BITBYTE_FOUNDATION_TIER2_LINK_STATICALLY
/// @breif Linking to tier2 statically, e.g., using libtier2.a.
///
#define BITBYTE_FOUNDATION_TIER2_LINK_STATICALLY 1

/// @def BITBYTE_FOUNDATION_TIER2_LINK_DYNAMICALLY
/// @brief Linking to tier2 dynamically, e.g., using libtier2.so.
///
#define BITBYTE_FOUNDATION_TIER2_LINK_DYNAMICALLY 2

/// @def BITBYTE_FOUNDATION_TIER2_LINKAGE
/// @brief Specifies if tier2 is being linked to statically, or dynamically.
#ifndef BITBYTE_FOUNDATION_TIER2_LINKAGE
  #error ("Please specify how you are linking to Foundation by defining `BITBYTE_FOUNDATION_TIER2_LINKAGE`.")
#endif

/// @def BITBYTE_FOUNDATION_TIER2_EXPORT
/// @brief ...
///
#if (BITBYTE_FOUNDATION_TIER2_LINKAGE == BITBYTE_FOUNDATION_TIER2_LINK_STATICALLY)
  #define BITBYTE_FOUNDATION_TIER2_EXPORT
#elif (BITBYTE_FOUNDATION_TIER2_LINKAGE == BITBYTE_FOUNDATION_TIER2_LINK_DYNAMICALLY)
  #if defined(_MSC_VER)
    /// @def BITBYTE_FOUNDATION_TIER2_COMPILING
    /// @brief ...
    ///
    #if defined(BITBYTE_FOUNDATION_TIER2_COMPILING)
      #define BITBYTE_FOUNDATION_TIER2_EXPORT __declspec(dllexport)
    #else
      #define BITBYTE_FOUNDATION_TIER2_EXPORT __declspec(dllimport)
    #endif
  #else
    #define BITBYTE_FOUNDATION_TIER2_EXPORT
  #endif
#endif

#endif // _BITBYTE_FOUNDATION_TIER2_EXPORT_H_
