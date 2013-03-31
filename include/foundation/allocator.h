// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALLOCATOR_H_
#define _FOUNDATION_ALLOCATOR_H_

// Defines an interface for stateful allocators.
// See ProxyAllocator, ScratchAllocator, TempAllocator, et cetra for examples.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/preprocessor.h>
#include <foundation/assert.h>

#include <new>

namespace foundation {
  class FOUNDATION_EXPORT Allocator {
    FOUNDATION_NON_COPYABLE(Allocator);

    protected:
      FOUNDATION_INLINE Allocator() {}
      FOUNDATION_INLINE virtual ~Allocator() {}

    public:
      virtual void* alloc(
        size_t num_bytes,
        size_t alignment = alignof(int) ) = 0;

      virtual void* realloc(
        void* ptr,
        size_t num_bytes,
        size_t alignment = alignof(int) ) = 0;

      virtual void free(
        void* ptr ) = 0;

    public:
      static Allocator& heap();
      static Allocator& scratch();
  };
} // foundation

#define MAKE_NEW( _Type, _Allocator ) \
  new ((_Allocator.alloc(sizeof(_Type), alignof(_Type)))) _Type

#define MAKE_DELETE( _Type, _Allocator, _Instance ) \
  do { _Instance->~_Type(); _Allocator.free((void*)_Instance); } while (0, 0)

#endif // _FOUNDATION_ALLOCATOR_H_