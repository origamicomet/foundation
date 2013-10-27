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
/*! @file include/foundation/allocator.h
     Defines a generic stateful allocator interface.                          */
/* ========================================================================== */

#ifndef _FOUNDATION_ALLOCATOR_H_
#define _FOUNDATION_ALLOCATOR_H_

#include <foundation/config.h>
#include <foundation/compat/stdint.h>
#include <foundation/compat/inttypes.h>
#include <foundation/compat/stdalign.h>
#include <foundation/assert.h>

/* ========================================================================== */
/*  Allocator:                                                                */
/*   * C (fnd_allocator_t);                                                   */
/*   * C++ (foundation::allocator).                                           */
/* ========================================================================== */

/* ========================================================================== */
/*  C (fnd_allocator_t):                                                      */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/*! A genertic stateful allocator interface. */
typedef struct fnd_allocator {
  void *(*alloc)(
    struct fnd_allocator *allocator,
    const size_t sz,
    const size_t alignment);
  void *(*realloc)(
    struct fnd_allocator *allocator,
    void *ptr,
    const size_t sz,
    const size_t alignment);
  void (*free)(
    struct fnd_allocator *allocator,
    void *ptr);
} fnd_allocator_t;

/* ========================================================================== */

/*! */
extern void *fnd_allocator_alloc(
  fnd_allocator_t *allocator,
  const size_t sz,
  const size_t alignment);

/*! */
extern void *fnd_allocator_realloc(
  fnd_allocator_t *allocator,
  void *ptr,
  const size_t sz,
  const size_t alignment);

/*! */
extern void fnd_allocator_free(
  fnd_allocator_t *allocator,
  void *ptr);

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::allocator):                                              */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
  /*! @copydoc fnd_allocator_t */
  class allocator {
    private:
      allocator(const allocator &);
      allocator &operator= (const allocator &);
    protected:
      allocator();
      virtual ~allocator();
    public:
      virtual void *alloc(const size_t sz, const size_t alignment) = 0;
      virtual void *realloc(void *ptr, const size_t sz, const size_t alignment) = 0;
      virtual void free(void *ptr) = 0;
    private:
      static void *alloc_(fnd_allocator_t *_, const size_t sz, const size_t alignment);
      static void *realloc_(fnd_allocator_t *_, void *ptr, const size_t sz, const size_t alignment);
      static void free_(fnd_allocator_t *_, void *ptr);
    private:
      fnd_allocator_t _;
      allocator *this_;
  };
} /* foundation */
#endif

#endif /* _FOUNDATION_ALLOCATOR_H_ */
