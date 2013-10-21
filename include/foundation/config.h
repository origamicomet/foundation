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
/*! @file include/foundation/config.h
     Documents a collection of pre-processor defines used for the
     configuration of Foundation's compile-, link-, and runtime behaviour.    */
/* ========================================================================== */

#ifndef _FOUNDATION_CONFIG_H_
#define _FOUNDATION_CONFIG_H_

/* ========================================================================== */
/*  Configuration:                                                            */
/*   * Linking;                                                               */
/*   * Compiler, architecture, and platform autodetection;                    */
/*   * Paranoid and/or debug, development, and release selection.             */
/* ========================================================================== */

/* ========================================================================== */
/*  Linking:                                                                  */
/* ========================================================================== */

/*! @def FND_LINK_STATICALLY
  Linking to Foundation statically, e.g., using libfoundation.a. */
#define FND_LINK_STATICALLY 1

/*! @def FND_LINK_DYNAMICALLY
  Linking to Foundation dynamically, e.g., using libfoundation.so. */
#define FND_LINK_DYNAMICALLY 2

/*! @def FND_LINK
  Specifies if Foundation is being linked to statically, or dynamically. */
#ifndef FND_LINK
  #error ("Please specify how you are linking to Foundation by defining `FND_LINK`.")
#endif

/* ========================================================================== */
/*  Compiler, architecture, and platform autodetection:                       */
/* ========================================================================== */

/*! @def FND_DONT_AUTODETECT_COMPILER
  Foundation won't attempt to detect the current compiler based on
  pre-processor defines, if defined.
  See include/foundation/detect/compiler.h for more details. */

/*! @def FND_DONT_AUTODETECT_PLATFORM
  Foundation won't attempt to detect the current platform based on
  pre-processor defines, if defined.
  See include/foundation/detect/platform.h for more details. */

/*! @def FND_DONT_AUTODETECT_ARCHITECTURE
  Foundation won't attempt to detect the current architecture based on
  pre-processor defines, if defined.
  See include/foundation/detect/architecture.h for more details. */

/* ========================================================================== */
/*  Paranoid and/or debug, development, and release selection:                */
/* ========================================================================== */

/*! @def FND_PARANOID
  Specifies how paranoid Foundation is; if defined Foundation will perform
  more sanity checks. */

/*! @def FND_DEBUG
  Enables debugging (and higher) checks and profiling. */
#define FND_DEBUG 3

/*! @def FND_DEVELOPMENT
  Enables development (and higher) checks and profiling. */
#define FND_DEVELOPMENT 2

/*! @def FND_RELEASE
  Enables release checks. */
#define FND_RELEASE 1

/*! @def FND_CONFIGURATION
  Specifies how "loose and fast" Foundation is. */
#ifndef FND_CONFIGURATION
  #error ("Please specify a configuration by defining `FND_CONFIGURATION`.")
#endif

#endif /* _FOUNDATION_CONFIG_H_ */
