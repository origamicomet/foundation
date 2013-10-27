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
 #  include <foundation/allocator.h>
/* ========================================================================== */

/* ========================================================================== */
/*  C (fnd_allocator_t):                                                      */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

void *fnd_allocator_alloc(
  fnd_allocator_t *allocator,
  const size_t sz,
  const size_t alignment)
{
  fnd_assert(debug, allocator != NULL);
  return allocator->alloc(allocator, sz, alignment);
}

void *fnd_allocator_realloc(
  fnd_allocator_t *allocator,
  void *ptr,
  const size_t sz,
  const size_t alignment)
{
  fnd_assert(debug, allocator != NULL);
  return allocator->realloc(allocator, ptr, sz, alignment);
}

void fnd_allocator_free(
  fnd_allocator_t *allocator,
  void *ptr)
{
  fnd_assert(debug, allocator != NULL);
  allocator->free(allocator, ptr);
}

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::allocator):                                              */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
  Allocator::Allocator() {
    _.alloc = &Allocator::alloc_;
    _.realloc = &Allocator::realloc_;
    _.free = &Allocator::free_;
    this_ = this;
  }

  Allocator::~Allocator() {
  }

  void *Allocator::alloc_(fnd_allocator_t *_, const size_t sz, const size_t alignment) {
    return (*((Allocator **)(((uintptr_t)_) + sizeof(fnd_allocator_t))))->alloc(sz, alignment);
  }

  void *Allocator::realloc_(fnd_allocator_t *_, void *ptr, const size_t sz, const size_t alignment) {
    return (*((Allocator **)(((uintptr_t)_) + sizeof(fnd_allocator_t))))->realloc(ptr, sz, alignment);
  }

  void Allocator::free_(fnd_allocator_t *_, void *ptr) {
    (*((Allocator **)(((uintptr_t)_) + sizeof(fnd_allocator_t))))->free(ptr);
  }
} /* foundation */
#endif