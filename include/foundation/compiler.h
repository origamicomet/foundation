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
/*! @file include/foundation/compiler.h
     Enumerates known compilers.                                              */
/* ========================================================================== */

#ifndef _FOUNDATION_COMPILER_H_
#define _FOUNDATION_COMPILER_H_

#include <foundation/config.h>

/* ========================================================================== */
/*  Compiler:                                                                 */
/*   * Enumeration;                                                           */
/*   * Detection.                                                             */
/* ========================================================================== */

/* ========================================================================== */
/*  Enumeration:                                                              */
/* ========================================================================== */

/*! @def FND_COMPILER_UNKNOWN_OR_UNSUPPORTED
  An unknown or unsupported compiler. */
#define FND_COMPILER_UNKNOWN_OR_UNSUPPORTED 0

/*! @def FND_COMPILER_MSVC
  Microsoft's Visual Studio C/C++ (cl). */
#define FND_COMPILER_MSVC 1

/*! @def FND_COMPILER_GCC
  GNU Compiler Collection (gcc or g++). */
#define FND_COMPILER_GCC 2

/*! @def FND_COMPILER_CLANG
  Clang front-end for LLVM (clang or clang++). */
#define FND_COMPILER_CLANG 3

/* ========================================================================== */
/*  Detection:                                                                */
/* ========================================================================== */

/* See include/foundation/detect/compiler.h. */
#ifndef _FOUNDATION_DETECT_COMPILER_H_
  #include <foundation/detect/compiler.h>
#endif

#endif /* _FOUNDATION_COMPILER_H_ */
