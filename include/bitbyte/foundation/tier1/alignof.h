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
/// \brief Provide a fallback implementation of _Alignof and alignof.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER1_ALIGNOF_H_
#define _BITBYTE_FOUNDATION_TIER1_ALIGNOF_H_

//============================================================================//

#if defined(__cplusplus)
  // Bless me, Father, for I have sinned.
  template <typename _Type> struct __bitbyte_foundation_tier1_alignof;
  template <int _SzDiff> struct __bitbyte_foundation_tier1_alignof_ {
    template <typename _Type> struct E { enum { _ = _SzDiff }; }; };
  template <> struct __bitbyte_foundation_tier1_alignof_<0> {
    template <typename _Type> struct E { enum { _ = __bitbyte_foundation_tier1_alignof<_Type>::_ }; }; };
  template <typename _Type> struct __bitbyte_foundation_tier1_alignof {
    struct C { _Type __; char _; };
    enum { D = (sizeof(C) - sizeof(_Type)), _ = __bitbyte_foundation_tier1_alignof_<D>::template E<C>::_ }; };
  #define __bitbyte_foundation_tier1_alignof__(_Type) \
    ((size_t)__bitbyte_foundation_tier1_alignof<_Type>::_)
#else
  #define __bitbyte_foundation_tier1_alignof__(_Type) \
    ((size_t)offsetof(struct{char _; _Type __;},__))
#endif

//===----------------------------------------------------------------------===//

#if defined(_MSC_VER)
  // Prevent xkeycheck.h from bitching about us redefining keywords.
  // See http://msdn.microsoft.com/en-us/library/bb531344.aspx.
  #define _ALLOW_KEYWORD_MACROS

  #if _MSC_VER >= 1600
    // Use compiler-specific, compiler-provided operators if available.
    #ifndef __alignof_is_defined
      #define alignof __alignof
      #define _Alignof __alignof
      #define __alignof_is_defined 1
    #endif
  #else
    // Otherwise, fallback to our implementation.
    #define alignof __bitbyte_foundation_tier1_alignof__
    #define _Alignof __bitbyte_foundation_tier1_alignof__
  #endif
#else
  #ifndef __alignof_is_defined
    #define alignof __bitbyte_foundation_tier1_alignof__
    #define _Alignof __bitbyte_foundation_tier1_alignof__
    #define __alignof_is_defined 1
  #endif
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER1_ALIGNOF_H_

//============================================================================//
