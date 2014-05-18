//===-- bitbyte/foundation/tier1/alignof.h ----------------------*- C++ -*-===//
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
/// \brief Provides a fallback implementation of alignof if required.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER1_ALIGNOF_H_
#define _BITBYTE_FOUNDATION_TIER1_ALIGNOF_H_

//============================================================================//

#if defined(__cplusplus)
  // Bless me, Father, for I have sinned.
  template <typename _Type> struct __fnd_alignof;
  template <int _SzDiff> struct __fnd_alignof_ {
    template <typename _Type> struct E { enum { _ = _SzDiff }; }; };
  template <> struct __fnd_alignof_<0> {
    template <typename _Type> struct E { enum { _ = __fnd_alignof<_Type>::_ }; }; };
  template <typename _Type> struct __fnd_alignof {
    struct C { _Type __; char _; };
    enum { D = (sizeof(C) - sizeof(_Type)), _ = __fnd_alignof_<D>::template E<C>::_ }; };
  #define bitbyte_foundation_tier1_alignof(_Type) ((size_t)__fnd_alignof<_Type>::_)
#else
  #define bitbyte_foundation_tier1_alignof(_Type) ((size_t)offsetof(struct{char _; _Type __;},__))
#endif

//===----------------------------------------------------------------------===//

#if defined(_MSC_VER)
  // Prevent xkeycheck.h from bitching about redefining keywords in 2012+
  // See http://msdn.microsoft.com/en-us/library/bb531344.aspx.
  #define _ALLOW_KEYWORD_MACROS

  // Microsoft Visual Studio 2010
  #if _MSC_VER < 1600
    #define alignof bitbyte_foundation_tier1_alignof
  #else
    #define alignof __alignof
  #endif
#else
  #include <stdalign.h>
  #if defined(__cplusplus)
    #if (__cplusplus < 201103L) && (!defined(__GXX_EXPERIMENTAL_CXX0X__))
      #define alignof bitbyte_foundation_tier1_alignof
    #endif
  #elif defined(__STDC_VERSION__)
    #if __STDC_VERSION__ < 201112L
      #define alignof bitbyte_foundation_tier1_alignof
    #endif
  #else
    #define alignof bitbyte_foundation_tier1_alignof
  #endif
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER1_ALIGNOF_H_

//============================================================================//
