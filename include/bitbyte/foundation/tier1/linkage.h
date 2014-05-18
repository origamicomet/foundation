//===-- bitbyte/foundation/tier1/linkage.h ----------------------*- C++ -*-===//
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

#ifndef _BITBYTE_FOUNDATION_TIER1_LINKAGE_H_
#define _BITBYTE_FOUNDATION_TIER1_LINKAGE_H_

//============================================================================//

/// \def BITBYTE_FOUNDATION_TIER1_INTERNAL_LINKAGE
/// \brief Exports symbols for inclusion of tier1 via objects.
///
#define BITBYTE_FOUNDATION_TIER1_INTERNAL_LINKAGE 0

/// \def BITBYTE_FOUNDATION_TIER1_STATIC_LINKAGE
/// \brief Exports symbols for inclusion of tier1 via static library.
///
#define BITBYTE_FOUNDATION_TIER1_STATIC_LINKAGE 1

/// \def BITBYTE_FOUNDATION_TIER1_DYNAMIC_LINKAGE
/// \brief Exports symbols for inclusion of tier1 via dynamic library.
///
#define BITBYTE_FOUNDATION_TIER1_DYNAMIC_LINKAGE 2

//===----------------------------------------------------------------------===//

/// \def BITBYTE_FOUNDATION_TIER1_EXPORT
/// \brief Marks a symbol for export.
///
#ifdef _MSC_VER
  #ifdef BITBYTE_FOUNDATION_TIER1_LINKAGE
    #if BITBYTE_FOUNDATION_TIER1_LINKAGE == BITBYTE_FOUNDATION_TIER1_INTERNAL_LINKAGE
      #define BITBYTE_FOUNDATION_TIER1_EXPORT
    #elif BITBYTE_FOUNDATION_TIER1_LINKAGE == BITBYTE_FOUNDATION_TIER1_STATIC_LINKAGE
      #define BITBYTE_FOUNDATION_TIER1_EXPORT
    #elif BITBYTE_FOUNDATION_TIER1_DYNAMIC_LINKAGE == BITBYTE_FOUNDATION_TIER1_DYNAMIC_LINKAGE
      #ifdef BITBYTE_FOUNDATION_TIER1_COMPILING
        #define BITBYTE_FOUNDATION_TIER1_EXPORT __declspec(dllexport)
      #else
        #define BITBYTE_FOUNDATION_TIER1_EXPORT __declspec(dllimport)
      #endif
    #endif
  #else
    #error ("You need to specify BITBYTE_FOUNDATION_TIER1_LINKAGE when building and using tier1!")
  #endif
#else
  #define BITBYTE_FOUNDATION_TIER1_EXPORT
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER1_LINKAGE_H_

//============================================================================//
