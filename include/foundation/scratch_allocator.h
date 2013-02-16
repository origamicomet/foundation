// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SCRATCH_ALLOCATOR_H_
#define _FOUNDATION_SCRATCH_ALLOCATOR_H_

// A simple ring-buffer based allocator for scratch allocation (temporary).

#include <foundation/allocator.h>

namespace foundation {
  class FOUNDATION_EXPORT ScratchAllocator
    : public Allocator 
  {
    FOUNDATION_NON_COPYABLE(ScratchAllocator);

    public:
      ScratchAllocator(
        Allocator& allocator,
        size_t num_bytes );
      
      ~ScratchAllocator();

    public:
      void* alloc(
        size_t num_bytes,
        size_t alignment = alignof(int) );

      void* realloc(
        void* ptr,
        size_t num_bytes,
        size_t alignment = alignof(int) );

      void free(
        void* ptr );

    private:
      Allocator& _allocator;
  };
} // foundation

#endif // _FOUNDATION_SCRATCH_ALLOCATOR_H_