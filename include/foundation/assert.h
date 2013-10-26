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
/*! @file include/foundation/assert.h
     Provides configuration dependent and independent assertion macros.       */
/* ========================================================================== */

#ifndef _FOUNDATION_ASSERT_H_
#define _FOUNDATION_ASSERT_H_

#include <foundation/config.h>

#include <stdio.h>
#include <signal.h>

/* ========================================================================== */
/*  Assert:                                                                   */
/*   * Independent;                                                           */
/*   * Dependent.                                                             */
/* ========================================================================== */

/* ========================================================================== */
/*  Independent:                                                              */
/* ========================================================================== */

/*! @def fnd_assertf_
  Logs a message based on `_Format` and aborts if `_Condition` fails. */
#define fnd_assertf_(_Condition, _Format, ...) \
  do { \
    if (!(_Condition)) { \
      fprintf(stderr, _Format, ## __VA_ARGS__); \
      signal(SIGABRT); \
    } \
  } while (0)

/*! @def fnd_assert_
  Logs a message and aborts if `_Condition` fails. */
#define fnd_assert_(_Condition) \
  fnd_assertf_(_Condition, \
    "An assertion failed!\n" \
    "\n" \
    "  '%s' in %s on line %u\n" \
    "\n", \
    fnd_stringificate(_Condition), \
    fnd_stringificate(__FILE__), \
    ((unsigned)__LINE__) \
  )

/* ========================================================================== */
/*  Dependent:                                                                */
/* ========================================================================== */

/*! @def fnd_assertf
  @copydoc fnd_assert_f If, and only if, `_Level` is <= FND_CONFIGURATION. */
#define fnd_assertf(_Level, _Condition, _Format, ...) \
  fnd_assertf_#_Level(_Condition, _Format, ## __VA_ARGS__)

#if (FND_CONFIGURATION <= FND_DEBUG)
  #define fnd_assertf_debug(_Condition, _Format, ...) \
    fnd_assertf_(_Condition, _Format, ## __VA_ARGS__)
#else
  #define fnd_assertf_debug(_Condition, _Format) \
    do { (void)sizeof((_Condition)); } while (0)
#endif

#if (FND_CONFIGURATION <= FND_DEVELOPMENT)
  #define fnd_assertf_development(_Condition, _Format, ...) \
    fnd_assertf_(_Condition, _Format, ## __VA_ARGS__)
#else
  #define fnd_assertf_development(_Condition, _Format) \
    do { (void)sizeof((_Condition)); } while (0)
#endif

#if (FND_CONFIGURATION <= FND_RELEASE)
  #define fnd_assertf_release(_Condition, _Format, ...) \
    fnd_assertf_(_Condition, _Format, ## __VA_ARGS__)
#else
  #define fnd_assertf_release(_Condition, _Format) \
    do { (void)sizeof((_Condition)); } while (0)
#endif

/*! @def fnd_assert
  @copydoc fnd_assert_ If, and only if, `_Level` is <= FND_CONFIGURATION. */
#define fnd_assert(_Level, _Condition) \
  fnd_assertf(_Level, _Condition, \
    "An assertion failed!\n" \
    "\n" \
    "  '%s' in %s on line %u\n" \
    "\n", \
    fnd_stringificate(_Condition), \
    fnd_stringificate(__FILE__), \
    ((unsigned)__LINE__) \
  )

#endif /* _FOUNDATION_ASSERT_H_ */
