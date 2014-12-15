//===-- bitbyte/foundation/tier4/heap.c ------------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@bitbyte.ca>
//
//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier4/heap.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier2/assert.h"

//===----------------------------------------------------------------------===//

#include "../../../nedmalloc.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

static
void *bitbyte_foundation_tier4_heap_alloc(
  bitbyte_foundation_tier4_allocator_t *allocator,
  const size_t sz,
  const size_t alignment)
{
  return nedmalloc2(sz, alignment, 0);
}

static
void *bitbyte_foundation_tier4_heap_realloc(
  bitbyte_foundation_tier4_allocator_t *allocator,
  void *ptr,
  const size_t sz,
  const size_t alignment)
{
  return nedrealloc2(ptr, sz, alignment, 0);
}

static
void *bitbyte_foundation_tier4_heap_free(
  bitbyte_foundation_tier4_allocator_t *allocator,
  void *ptr)
{
  nedfree2(ptr, 0);
  return NULL;
}

//===----------------------------------------------------------------------===//

static bitbyte_foundation_tier4_allocator_t heap_ = {
  /* .alloc = */ (bitbyte_foundation_tier4_allocator_alloc_fn)&bitbyte_foundation_tier4_heap_alloc,
  /* .realloc = */ (bitbyte_foundation_tier4_allocator_realloc_fn)&bitbyte_foundation_tier4_heap_realloc,
  /* .free = */ (bitbyte_foundation_tier4_allocator_free_fn)&bitbyte_foundation_tier4_heap_free
};

bitbyte_foundation_tier4_allocator_t *
bitbyte_foundation_tier4_heap(void)
{
  return &heap_;
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier4 {

//===----------------------------------------------------------------------===//

class Heap :
  public Allocator
{
 public:
  Heap() : Allocator() {}
  ~Heap() {}

 public:
  void *alloc(const size_t sz, const size_t alignment) {
    return ::nedmalloc2(sz, alignment, 0);
  }

  void *realloc(void *ptr, const size_t sz, const size_t alignment) {
    return ::nedrealloc2(ptr, sz, alignment, 0);
  }

  void *free(void *ptr) {
    ::nedfree2(ptr, 0);
    return NULL;
  }
};

//===----------------------------------------------------------------------===//

static Heap heap_;
Allocator *heap(void)
{
  return (Allocator *)&heap_;
}

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier4

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
