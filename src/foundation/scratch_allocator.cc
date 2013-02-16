// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/scratch_allocator.h>

namespace foundation {
  ScratchAllocator::ScratchAllocator(
    Allocator& allocator,
    size_t num_bytes )
    : _allocator(allocator)
  {
    (void)num_bytes;
  }

  ScratchAllocator::~ScratchAllocator()
  {
  }

  void* ScratchAllocator::alloc(
    size_t num_bytes,
    size_t alignment )
  {
    (void)num_bytes;
    (void)alignment;
    
    return nullptr;
  }

  void* ScratchAllocator::realloc(
    void* ptr,
    size_t num_bytes,
    size_t alignment )
  {
    (void)ptr;
    (void)num_bytes;
    (void)alignment;

    return nullptr;
  }

  void ScratchAllocator::free(
    void* ptr )
  {
    (void)ptr;
  }
} // foundation