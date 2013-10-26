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
/*! @file include/foundation/architecture.h
     Detects known architectures.                                             */
/* ========================================================================== */

#ifndef _FOUNDATION_DETECT_ARCHITECTURE_H_
#define _FOUNDATION_DETECT_ARCHITECTURE_H_

#include <foundation/config.h>

/* See include/foundation/architecture.h. */
#ifndef _FOUNDATION_ARCHITECTURE_H_
  #include <foundation/architecture.h>
#endif

/* ========================================================================== */
/*  Detection:                                                                */
/*   * Sanity checks;                                                         */
/*   * Detect based on pre-processor defines.                                 */
/* ========================================================================== */

/* ========================================================================== */
/*  Sanity checks:                                                            */
/* ========================================================================== */

#ifdef FND_DONT_AUTODETECT_ARCHITECTURE
  #ifndef FND_ARCHITECTURE
    #error ("Please specify which architecture you are targeting Foundation for by defining `FND_ARCHITECTURE`.")
  #else
    #if (FND_ARCHITECTURE != FND_ARCHITECTURE_X86)    && \
        (FND_ARCHITECTURE != FND_ARCHITECTURE_X86_64) && \
        (FND_ARCHITECTURE != FND_ARCHITECTURE_ARM)
      #error ("You specified an unknown or unsupported architecture. Did you define `FND_ARCHITECTURE` correctly?")
    #endif
  #endif
#endif

/* ========================================================================== */
/*  Detection based on pre-processor defines:                                 */
/* ========================================================================== */

#if (defined(_M_IX86) || defined(__i386__))
  #define FND_ARCHITECTURE FND_ARCHITECTURE_X86
#elif (defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) || defined(__amd64))
  #define FND_ARCHITECTURE FND_ARCHITECTURE_X86_64
#elif defined(__ARMEL__)
  #define FND_ARCHITECTURE FND_ARCHITECTURE_ARM
#else
  #define FND_ARCHITECTURE FND_ARCHITECTURE_UNKNOWN_OR_UNSUPPORTED
#endif

#if (FND_ARCHITECTURE == FND_ARCHITECTURE_UNKNOWN_OR_UNSUPPORTED)
  #error ("Foundation was unable to detect which architecture you are targeting based on pre-processor defines. Are you targeting an unknown or unsupported architecture?")
#endif

#endif /* _FOUNDATION_DETECT_ARCHITECTURE_H_ */
