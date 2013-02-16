// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SCRATCH_ALLOCATOR_H_
#define _FOUNDATION_SCRATCH_ALLOCATOR_H_

// A simple forwarding allocator.

#include <foundation/allocator.h>

namespace foundation {
  class FOUNDATION_EXPORT ProxyAllocator
    : public Allocator 
  {
    FOUNDATION_NON_COPYABLE(ProxyAllocator);

    public:
      FOUNDATION_INLINE explicit ProxyAllocator( Allocator& allocator )
        : _allocator(allocator)
      {}

      FOUNDATION_INLINE ~ProxyAllocator()
      {}

    public:
      FOUNDATION_INLINE void* alloc(
        size_t num_bytes,
        size_t alignment = alignof(int) )
      {
        return _allocator.alloc(num_bytes, alignment);
      }

      FOUNDATION_INLINE void* realloc(
        void* ptr,
        size_t num_bytes,
        size_t alignment = alignof(int) )
      {
        return _allocator.realloc(ptr, num_bytes, alignment);
      }

      FOUNDATION_INLINE void free(
        void* ptr )
      {
        return _allocator.free(ptr);
      }

    private:
      Allocator& _allocator;
  };
} // foundation

#endif // _FOUNDATION_SCRATCH_ALLOCATOR_H_