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
/*! @file include/foundation/platform.h
     Detects known platforms.                                                 */
/* ========================================================================== */

#ifndef _FOUNDATION_DETECT_PLATFORM_H_
#define _FOUNDATION_DETECT_PLATFORM_H_

#include <foundation/config.h>

/* See include/foundation/platform.h. */
#ifndef _FOUNDATION_PLATFORM_H_
  #include <foundation/platform.h>
#endif

/* ========================================================================== */
/*  Detection:                                                                */
/*   * Sanity checks;                                                         */
/*   * Detect based on pre-processor defines.                                 */
/* ========================================================================== */

/* ========================================================================== */
/*  Sanity checks:                                                            */
/* ========================================================================== */

#ifdef FND_DONT_AUTODETECT_PLATFORM
  #ifndef FND_PLATFORM
    #error ("Please specify which platform you are targeting Foundation for by defining `FND_PLATFORM`.")
  #else
    #if (FND_PLATFORM != FND_PLATFORM_WINDOWS) && \
        (FND_PLATFORM != FND_PLATFORM_MACOSX)  && \
        (FND_PLATFORM != FND_PLATFORM_LINUX)   && \
        (FND_PLATFORM != FND_PLATFORM_ANDROID) && \
        (FND_PLATFORM != FND_PLATFORM_IOS)
      #error ("You specified an unknown or unsupported platform. Did you define `FND_PLATFORM` correctly?")
    #endif
  #endif
#endif

/* ========================================================================== */
/*  Detection based on pre-processor defines:                                 */
/* ========================================================================== */

#if (defined(_WIN32) || defined(_WIN64))
  #define FND_PLATFORM FND_PLATFORM_WINDOWS
#elif defined(__APPLE__)
  #include <TargetConditionals.h>
  #if defined(TARGET_OS_IPHONE)
    #define FND_PLATFORM FND_PLATFORM_IOS
  #else
    #define FND_PLATFORM FND_PLATFORM_MACOSX
  #endif
#elif defined(__linux__)
  #if defined(ANDROID)
    #define FND_PLATFORM FND_PLATFORM_ANDROID
  #else
    #define FND_PLATFORM FND_PLATFORM_LINUX
  #endif
#else
  #define FND_PLATFORM FND_PLATFORM_UNKNOWN_OR_UNSUPPORTED
#endif

#if (FND_PLATFORM == FND_PLATFORM_UNKNOWN_OR_UNSUPPORTED)
  #error ("Foundation was unable to detect which platform you are targeting based on pre-processor defines. Are you targeting an unknown or unsupported platform?")
#endif

#endif /* _FOUNDATION_DETECT_PLATFORM_H_ */
