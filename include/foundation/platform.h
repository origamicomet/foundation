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
     Enumerates known platforms.                                              */
/* ========================================================================== */

#ifndef _FOUNDATION_PLATFORM_H_
#define _FOUNDATION_PLATFORM_H_

#include <foundation/config.h>

/* ========================================================================== */
/*  Platform:                                                                 */
/*   * Enumeration;                                                           */
/*   * Detection.                                                             */
/* ========================================================================== */

/* ========================================================================== */
/*  Enumeration:                                                              */
/* ========================================================================== */

/*! @def FND_PLATFORM_UNKNOWN_OR_UNSUPPORTED
  An unknown or unsupported platform. */
#define FND_PLATFORM_UNKNOWN_OR_UNSUPPORTED 0

/*! @def FND_PLATFORM_WINDOWS
  Microsoft Windows. */
#define FND_PLATFORM_WINDOWS 1

/*! @def FND_PLATFORM_MACOSX
  Apple Mac OSX. */
#define FND_PLATFORM_MACOSX 2

/*! @def FND_PLATFORM_LINUX
  GNU/Linux. */
#define FND_PLATFORM_LINUX 3

/*! @def FND_PLATFORM_ANDROID
  Google Android. */
#define FND_PLATFORM_ANDROID 4

/*! @def FND_PLATFORM_IOS
  Apple iOS. */
#define FND_PLATFORM_IOS 5

/* ========================================================================== */
/*  Detection:                                                                */
/* ========================================================================== */

/* See include/foundation/detect/platform.h. */
#ifndef _FOUNDATION_DETECT_PLATFORM_H_
  #include <foundation/detect/platform.h>
#endif

#endif /* _FOUNDATION_PLATFORM_H_ */
