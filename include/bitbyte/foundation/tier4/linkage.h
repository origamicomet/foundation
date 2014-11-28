//===-- bitbyte/foundation/tier4/linkage.h ----------------------*- C++ -*-===//
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

#ifndef _BITBYTE_FOUNDATION_TIER4_LINKAGE_H_
#define _BITBYTE_FOUNDATION_TIER4_LINKAGE_H_

//============================================================================//

/// \def BITBYTE_FOUNDATION_TIER4_INTERNAL_LINKAGE
/// \brief Exports symbols for inclusion of tier4 via objects.
///
#define BITBYTE_FOUNDATION_TIER4_INTERNAL_LINKAGE 0

/// \def BITBYTE_FOUNDATION_TIER4_STATIC_LINKAGE
/// \brief Exports symbols for inclusion of tier4 via static library.
///
#define BITBYTE_FOUNDATION_TIER4_STATIC_LINKAGE 1

/// \def BITBYTE_FOUNDATION_TIER4_DYNAMIC_LINKAGE
/// \brief Exports symbols for inclusion of tier4 via dynamic library.
///
#define BITBYTE_FOUNDATION_TIER4_DYNAMIC_LINKAGE 2

//===----------------------------------------------------------------------===//

/// \def BITBYTE_FOUNDATION_TIER4_EXPORT
/// \brief Marks a symbol for export.
///
#ifdef _MSC_VER
  #ifdef BITBYTE_FOUNDATION_TIER4_LINKAGE
    #if BITBYTE_FOUNDATION_TIER4_LINKAGE == BITBYTE_FOUNDATION_TIER4_INTERNAL_LINKAGE
      #define BITBYTE_FOUNDATION_TIER4_EXPORT
    #elif BITBYTE_FOUNDATION_TIER4_LINKAGE == BITBYTE_FOUNDATION_TIER4_STATIC_LINKAGE
      #define BITBYTE_FOUNDATION_TIER4_EXPORT
    #elif BITBYTE_FOUNDATION_TIER4_DYNAMIC_LINKAGE == BITBYTE_FOUNDATION_TIER4_DYNAMIC_LINKAGE
      #ifdef BITBYTE_FOUNDATION_TIER4_COMPILING
        #define BITBYTE_FOUNDATION_TIER4_EXPORT __declspec(dllexport)
      #else
        #define BITBYTE_FOUNDATION_TIER4_EXPORT __declspec(dllimport)
      #endif
    #endif
  #else
    #error ("You need to specify BITBYTE_FOUNDATION_TIER4_LINKAGE when building and using tier4!")
  #endif
#else
  #define BITBYTE_FOUNDATION_TIER4_EXPORT
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER4_LINKAGE_H_

//============================================================================//
