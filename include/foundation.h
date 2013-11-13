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
/*! @file include/foundation.h
     Includes all public headers necessary to use Foundation.                 */
/* ========================================================================== */

#ifndef _FOUNDATION_H_
#define _FOUNDATION_H_

/* ========================================================================== */
/*  Foundation:                                                               */
/*   * Configuration;                                                         */
/*   * Compiler, architecture, and platform;                                  */
/*   * Compatability;                                                         */
/*   * Pre-processor and intrinsics;                                          */
/*   * Containers and data structures;                                        */
/*   * Concurrency;                                                           */
/*   * Misc.                                                                  */
/* ========================================================================== */

/* ========================================================================== */
/*  Configuration:                                                            */
/* ========================================================================== */

#include <foundation/config.h>

/* ========================================================================== */
/*  Compiler, architecture, and platform:                                     */
/* ========================================================================== */

#include <foundation/compiler.h>
#include <foundation/detect/compiler.h>

#include <foundation/architecture.h>
#include <foundation/detect/architecture.h>

#include <foundation/platform.h>
#include <foundation/detect/platform.h>

/* ========================================================================== */
/*  Compatability:                                                            */
/* ========================================================================== */

#include <foundation/compat/stdint.h>
#include <foundation/compat/inttypes.h>
#include <foundation/compat/stdbool.h>
#include <foundation/compat/stdalign.h>
#include <foundation/compat/malloc.h>

/* ========================================================================== */
/*  Pre-processor and intrinsics:                                             */
/* ========================================================================== */

#include <foundation/preprocessor.h>
#include <foundation/assert.h>

#include <foundation/atomics.h>

/* ========================================================================== */
/*  Containers and data structures:                                           */
/* ========================================================================== */

#include <foundation/array.h>

/* ========================================================================== */
/*  Concurrency:                                                              */
/* ========================================================================== */

#include <foundation/thread.h>
#include <foundation/mutex.h>

/* ========================================================================== */
/*  Misc.:                                                                    */
/* ========================================================================== */

#include <foundation/system.h>

/* ========================================================================== */

#endif /* _FOUNDATION_H_ */
