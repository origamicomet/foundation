//===-- bitbyte/foundation/tier4/allocator.c -------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier4/allocator.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier2/assert.h"

//===----------------------------------------------------------------------===//

#include <stdlib.h>
#include <string.h>

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

int
bitbyte_foundation_tier4_allocator_to_s(
  const bitbyte_foundation_allocator_t *allocator,
  char buf[],
  const size_t buf_sz)
{
  bitbyte_foundation_tier2_assert(allocator != NULL);
  return snprintf(&buf[0], buf_sz, "#bitbyte_foundation_tier4_allocator_t<%p>", allocator);
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

Allocator::Allocator()
  : __self__(this)
{
  struct Proxy {
    #define __allocator__ \
      (*(Allocator **)( \
        ((uintptr_t)allocator) + \
        sizeof(::bitbyte_foundation_tier4_allocator_t)))

    static void *alloc(::bitbyte_foundation_tier4_allocator_t *allocator,
                       const size_t sz, const size_t alignment) {
      return __allocator__->alloc(sz, alignment);
    }

    static void *realloc(::bitbyte_foundation_tier4_allocator_t *allocator,
                         void *ptr, const size_t sz, const size_t alignment) {
      return __allocator__->realloc(ptr, sz, alignment);
    }

    static void *free(::bitbyte_foundation_tier4_allocator_t *allocator,
                      void *ptr) {
      return __allocator__->free(ptr);
    }

    #undef __allocator__
  };

  memset((void *)&__allocator__, 0, sizeof(::bitbyte_foundation_tier4_allocator_t));

  __allocator__.alloc = (bitbyte_foundation_tier4_allocator_alloc_fn)&Proxy::alloc;
  __allocator__.realloc = (bitbyte_foundation_tier4_allocator_realloc_fn)&Proxy::realloc;
  __allocator__.free = (bitbyte_foundation_tier4_allocator_free_fn)&Proxy::free;
}

Allocator::~Allocator()
{
}

//===----------------------------------------------------------------------===//

int Allocator::to_s(char buf[], const size_t buf_sz)
{
  return snprintf(&buf[0], buf_sz, "#bitbyte::foundation::tier4::Allocator<%p>", this);
}

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier4

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
