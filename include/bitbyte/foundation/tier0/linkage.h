//===-- bitbyte/foundation/tier0/linkage.h ----------------------*- C++ -*-===//
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
///
/// \file
/// \brief Defines the pre-processor macros that assist with symbol visibility.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER0_LINKAGE_H_
#define _BITBYTE_FOUNDATION_TIER0_LINKAGE_H_

//============================================================================//

/// \def BITBYTE_FOUNDATION_TIER0_INTERNAL_LINKAGE
/// \brief Exports symbols for inclusion of tier0 via objects.
///
#define BITBYTE_FOUNDATION_TIER0_INTERNAL_LINKAGE 0

/// \def BITBYTE_FOUNDATION_TIER0_STATIC_LINKAGE
/// \brief Exports symbols for inclusion of tier0 via static library.
///
#define BITBYTE_FOUNDATION_TIER0_STATIC_LINKAGE 1

/// \def BITBYTE_FOUNDATION_TIER0_DYNAMIC_LINKAGE
/// \brief Exports symbols for inclusion of tier0 via dynamic library.
///
#define BITBYTE_FOUNDATION_TIER0_DYNAMIC_LINKAGE 2

//===----------------------------------------------------------------------===//

/// \def BITBYTE_FOUNDATION_TIER0_EXPORT
/// \brief Marks a symbol for export.
///
#ifdef _MSC_VER
  #ifdef BITBYTE_FOUNDATION_TIER0_LINKAGE
    #if BITBYTE_FOUNDATION_TIER0_LINKAGE == BITBYTE_FOUNDATION_TIER0_INTERNAL_LINKAGE
      #define BITBYTE_FOUNDATION_TIER0_EXPORT
    #elif BITBYTE_FOUNDATION_TIER0_LINKAGE == BITBYTE_FOUNDATION_TIER0_STATIC_LINKAGE
      #define BITBYTE_FOUNDATION_TIER0_EXPORT
    #elif BITBYTE_FOUNDATION_TIER0_DYNAMIC_LINKAGE == BITBYTE_FOUNDATION_TIER0_DYNAMIC_LINKAGE
      #ifdef BITBYTE_FOUNDATION_TIER0_COMPILING
        #define BITBYTE_FOUNDATION_TIER0_EXPORT __declspec(dllexport)
      #else
        #define BITBYTE_FOUNDATION_TIER0_EXPORT __declspec(dllimport)
      #endif
    #endif
  #else
    #error ("You need to specify BITBYTE_FOUNDATION_TIER0_LINKAGE when building and using tier0!")
  #endif
#else
  #define BITBYTE_FOUNDATION_TIER0_EXPORT
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER0_LINKAGE_H_

//============================================================================//
