// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/allocator.h>
#include <foundation/scratch_allocator.h>

#define NO_NED_NAMESPACE
#include <nedmalloc.h>

namespace foundation {
  namespace {
    class DefaultAllocator :
      public Allocator
    {
      public:
        DefaultAllocator() {}
        ~DefaultAllocator() {}

      public:
        void* alloc( size_t num_bytes, size_t alignment ) {
          return nedmalloc2(num_bytes, alignment, 0);
        }

        void* realloc( void* ptr, size_t num_bytes, size_t alignment ) {
          return nedrealloc2(ptr, num_bytes, alignment, 0);
        }

        void free( void* ptr ) {
          nedfree2(ptr, 0);
        }
    };
  }

  Allocator& Allocator::heap()
  {
    static DefaultAllocator def_allocator;
    return def_allocator;
  }

  Allocator& Allocator::scratch()
  {
    static ScratchAllocator def_scratch_allocator(
      Allocator::heap(),
      FOUNDATION_DEF_SCRATCH_ALLOCATOR_SIZE
    );
    
    return def_scratch_allocator;
  }
} // foundation