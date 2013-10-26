/* ========================================================================== */
/*                                                                            */
/* This file is part of Foundation.                                           */
/*                                                                            */
/* Author(s):                                                                 */
/*                                                                            */
/*   Michael Williams <devbug@bitbyte.ca>                                     */
/*                                                                            */
/* This is free and unencumbered software released into the public domain.    */
/*                                                                            */
/* Anyone is free to copy, modify, publish, use, compile, sell, or distribute */
/* this software, either in source code form or as a compiled binary, for any */
/* purpose, commercial or non-commercial, and by any means.                   */
/*                                                                            */
/* In jurisdictions that recognize copyright laws, the author or authors of   */
/* this software dedicate any and all copyright interest in the software to   */
/* the public domain. We make this dedication for the benefit of the public   */
/* large and to the detriment of our heirs and successors. We intend this     */
/* dedication to be an overt act of relinquishment in perpetuity of all       */
/* present and future rights to this software under copyright law.            */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   */
/* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR      */
/* OTHER DEALINGS IN THE SOFTWARE.                                            */
/*                                                                            */
/* For more information, please refer to <http://unlicense.org/>              */
/*                                                                            */
/* ========================================================================== */
/*! @file include/foundation/compat/stdalign.h.
     Provides an ISO C1x compliant stdalign.h.                                */
/* ========================================================================== */

#ifndef _FOUNDATION_COMPAT_STDALIGN_H_
#define _FOUNDATION_COMPAT_STDALIGN_H_

#include <foundation/detect/compiler.h>

/* ========================================================================== */
/*  Fallback implementation for non-supporting compilers:                     */
/* ========================================================================== */

#if ((defined(__STDC_VERSION__) && (__STDC_VERSION__ < 201112L)) || (!defined(__cplusplus) && defined(_MSC_VER)))
  #ifndef fnd_alignof
    #define fnd_alignof(_Type) ((size_t)offsetof(struct{char _; _Type __;},__))
  #endif /* ifndef fnd_alignof */
#elif ((defined(__cplusplus) && (__cplusplus < 201103L) && !defined(__GXX_EXPERIMENTAL_CXX0X__)) || (defined(__cplusplus) && defined(_MSC_VER)))
  /* Bless me, Father, for I have sinned. */
  template <typename _Type> struct __fnd_alignof;
  template <int _SzDiff> struct __fnd_alignof_ {
    template <typename _Type> struct E { enum { _ = _SzDiff }; }; };
  template <> struct __fnd_alignof_<0> {
    template <typename _Type> struct E { enum { _ = __fnd_alignof<_Type>::_ }; }; };
  template <typename _Type> struct __fnd_alignof {
    struct C { _Type __; char _; };
    enum { D = (sizeof(C) - sizeof(_Type)), _ = __fnd_alignof_<D>::template E<C>::_ }; };
  #ifndef fnd_alignof
    #define fnd_alignof(_Type) ((size_t)__fnd_alignof<_Type>::_)
  #endif /* ifndef fnd_alignof */
#else
  #include <stdalign.h>
#endif

#endif /* _FOUNDATION_COMPAT_STDALIGN_H_ */
