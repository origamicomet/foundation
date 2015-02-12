//===-- bitbyte/foundation/tier1/constructor_and_destructor.h ---*- C++ -*-===//
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
/// \brief Provides compiler independent initializers and finalizers.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER1_CONSTRUCTOR_AND_DESTRUCTOR_H_
#define _BITBYTE_FOUNDATION_TIER1_CONSTRUCTOR_AND_DESTRUCTOR_H_

//============================================================================//

/// \def foundation_def_constructor
/// \copydoc bitbyte_foundation_def_constructor
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_def_constructor bitbyte_foundation_def_constructor
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def foundation_def_destructor
/// \copydoc bitbyte_foundation_def_destructor
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_def_destructor bitbyte_foundation_def_destructor
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_def_constructor
/// \copydoc bitbyte_foundation_tier1_def_constructor
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_def_constructor bitbyte_foundation_tier1_def_constructor
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_def_destructor
/// \copydoc bitbyte_foundation_tier1_def_destructor
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_def_destructor bitbyte_foundation_tier1_def_destructor
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_tier1_def_constructor
/// \param _Constructor
///

/// \def bitbyte_foundation_tier1_def_destructor
/// \param _Destructor
///

#if ((__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)) || defined(__clang__))
  #define bitbyte_foundation_tier1_def_constructor(_Constructor) \
    static void __attribute__((constructor)) _Constructor##(void);
  #define bitbyte_foundation_tier1_def_destructor(_Destructor) \
    static void __attribute__((destructor)) _Destructor##(void);
#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
  #define bitbyte_foundation_tier1_def_constructor(_Constructor) \
    static void _Constructor(void); \
    static int _Constructor##_wrapper(void) { _Constructor(); return 0; } \
    __pragma(section(".CRT$XCU",read)) \
    __declspec(allocate(".CRT$XCU")) static int (* _array##_Constructor)(void) = _Constructor##_wrapper;
  #define bitbyte_foundation_tier1_def_destructor(_Destructor) \
    static void _Destructor(void); \
    static int _Destructor##_constructor(void) { atexit (_Destructor); return 0; } \
    __pragma(section(".CRT$XCU",read)) \
    __declspec(allocate(".CRT$XCU")) static int (* _array##_Destructor)(void) = _Destructor##_constructor;
#elif defined (_MSC_VER)
  #error ("Please use Microsoft Visual C/C++ 2008 or newer.")
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER1_CONSTRUCTOR_AND_DESTRUCTOR_H_

//============================================================================//
