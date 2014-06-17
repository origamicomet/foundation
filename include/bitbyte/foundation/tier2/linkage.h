//===-- bitbyte/foundation/tier2/linkage.h ----------------------*- C++ -*-===//
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
/// \brief Defines the pre-processor macros that assist with symbol visibility.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER2_LINKAGE_H_
#define _BITBYTE_FOUNDATION_TIER2_LINKAGE_H_

//============================================================================//

/// \def BITBYTE_FOUNDATION_TIER2_INTERNAL_LINKAGE
/// \brief Exports symbols for inclusion of tier2 via objects.
///
#define BITBYTE_FOUNDATION_TIER2_INTERNAL_LINKAGE 0

/// \def BITBYTE_FOUNDATION_TIER2_STATIC_LINKAGE
/// \brief Exports symbols for inclusion of tier2 via static library.
///
#define BITBYTE_FOUNDATION_TIER2_STATIC_LINKAGE 1

/// \def BITBYTE_FOUNDATION_TIER2_DYNAMIC_LINKAGE
/// \brief Exports symbols for inclusion of tier2 via dynamic library.
///
#define BITBYTE_FOUNDATION_TIER2_DYNAMIC_LINKAGE 2

//===----------------------------------------------------------------------===//

/// \def BITBYTE_FOUNDATION_TIER2_EXPORT
/// \brief Marks a symbol for export.
///
#ifdef _MSC_VER
  #ifdef BITBYTE_FOUNDATION_TIER2_LINKAGE
    #if BITBYTE_FOUNDATION_TIER2_LINKAGE == BITBYTE_FOUNDATION_TIER2_INTERNAL_LINKAGE
      #define BITBYTE_FOUNDATION_TIER2_EXPORT
    #elif BITBYTE_FOUNDATION_TIER2_LINKAGE == BITBYTE_FOUNDATION_TIER2_STATIC_LINKAGE
      #define BITBYTE_FOUNDATION_TIER2_EXPORT
    #elif BITBYTE_FOUNDATION_TIER2_DYNAMIC_LINKAGE == BITBYTE_FOUNDATION_TIER2_DYNAMIC_LINKAGE
      #ifdef BITBYTE_FOUNDATION_TIER2_COMPILING
        #define BITBYTE_FOUNDATION_TIER2_EXPORT __declspec(dllexport)
      #else
        #define BITBYTE_FOUNDATION_TIER2_EXPORT __declspec(dllimport)
      #endif
    #endif
  #else
    #error ("You need to specify BITBYTE_FOUNDATION_TIER2_LINKAGE when building and using tier2!")
  #endif
#else
  #define BITBYTE_FOUNDATION_TIER2_EXPORT
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER2_LINKAGE_H_

//============================================================================//
