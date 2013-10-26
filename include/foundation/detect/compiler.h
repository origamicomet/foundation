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
     Detects known compilers.                                                 */
/* ========================================================================== */

#ifndef _FOUNDATION_DETECT_COMPILER_H_
#define _FOUNDATION_DETECT_COMPILER_H_

#include <foundation/config.h>

/* See include/foundation/compiler.h. */
#ifndef _FOUNDATION_COMPILER_H_
  #include <foundation/compiler.h>
#endif

/* ========================================================================== */
/*  Detection:                                                                */
/*   * Sanity checks;                                                         */
/*   * Detect based on pre-processor defines.                                 */
/* ========================================================================== */

/* ========================================================================== */
/*  Sanity checks:                                                            */
/* ========================================================================== */

#ifdef FND_DONT_AUTODETECT_COMPILER
  #ifndef FND_COMPILER
    #error ("Please specify which compiler you are using to compile Foundation by defining `FND_COMPILER`.")
  #else
    #if (FND_COMPILER != FND_COMPILER_MSVC) && \
        (FND_COMPILER != FND_COMPILER_GCC)  && \
        (FND_COMPILER != FND_COMPILER_CLANG)
      #error ("You specified an unknown or unsupported compiler. Did you define `FND_COMPILER` correctly?")
    #endif
  #endif
#endif

/* ========================================================================== */
/*  Detection based on pre-processor defines:                                 */
/* ========================================================================== */

#if defined(_MSC_VER)
  #define FND_COMPILER FND_COMPILER_MSVC
#elif defined(__GNUC__)
  #define FND_COMPILER FND_COMPILER_GCC
#elif defined(__clang__)
  #define FND_COMPILER FND_COMPILER_CLANG
#else
  #define FND_COMPILER FND_COMPILER_UNKNOWN_OR_UNSUPPORTED
#endif

#if (FND_COMPILER == FND_COMPILER_UNKNOWN_OR_UNSUPPORTED)
  #error ("Foundation was unable to detect which compiler you are using based on pre-processor defines. Are you using an unknown or unsupported compiler?")
#endif

#endif /* _FOUNDATION_DETECT_COMPILER_H_ */
