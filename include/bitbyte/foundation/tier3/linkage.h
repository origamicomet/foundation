//===-- bitbyte/foundation/tier3/linkage.h ----------------------*- C++ -*-===//
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
///
/// \file
/// \brief Defines the pre-processor macros that assist with symbol visibility.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER3_LINKAGE_H_
#define _BITBYTE_FOUNDATION_TIER3_LINKAGE_H_

//============================================================================//

/// \def BITBYTE_FOUNDATION_TIER3_INTERNAL_LINKAGE
/// \brief Exports symbols for inclusion of tier3 via objects.
///
#define BITBYTE_FOUNDATION_TIER3_INTERNAL_LINKAGE 0

/// \def BITBYTE_FOUNDATION_TIER3_STATIC_LINKAGE
/// \brief Exports symbols for inclusion of tier3 via static library.
///
#define BITBYTE_FOUNDATION_TIER3_STATIC_LINKAGE 1

/// \def BITBYTE_FOUNDATION_TIER3_DYNAMIC_LINKAGE
/// \brief Exports symbols for inclusion of tier3 via dynamic library.
///
#define BITBYTE_FOUNDATION_TIER3_DYNAMIC_LINKAGE 2

//===----------------------------------------------------------------------===//

/// \def BITBYTE_FOUNDATION_TIER3_EXPORT
/// \brief Marks a symbol for export.
///
#ifdef _MSC_VER
  #ifdef BITBYTE_FOUNDATION_TIER3_LINKAGE
    #if BITBYTE_FOUNDATION_TIER3_LINKAGE == BITBYTE_FOUNDATION_TIER3_INTERNAL_LINKAGE
      #define BITBYTE_FOUNDATION_TIER3_EXPORT
    #elif BITBYTE_FOUNDATION_TIER3_LINKAGE == BITBYTE_FOUNDATION_TIER3_STATIC_LINKAGE
      #define BITBYTE_FOUNDATION_TIER3_EXPORT
    #elif BITBYTE_FOUNDATION_TIER3_DYNAMIC_LINKAGE == BITBYTE_FOUNDATION_TIER3_DYNAMIC_LINKAGE
      #ifdef BITBYTE_FOUNDATION_TIER3_COMPILING
        #define BITBYTE_FOUNDATION_TIER3_EXPORT __declspec(dllexport)
      #else
        #define BITBYTE_FOUNDATION_TIER3_EXPORT __declspec(dllimport)
      #endif
    #endif
  #else
    #error ("You need to specify BITBYTE_FOUNDATION_TIER3_LINKAGE when building and using tier3!")
  #endif
#else
  #define BITBYTE_FOUNDATION_TIER3_EXPORT
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER3_LINKAGE_H_

//============================================================================//
