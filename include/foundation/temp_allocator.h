// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_TEMP_ALLOCATOR_H_
#define _FOUNDATION_TEMP_ALLOCATOR_H_

// A simple linear allocator used for temporary scoped allocations.
// Note: alloctions are not explictly freed but are upon scope exit.
// Warning: allocations can be no larger than the size of a block.

#include <foundation/allocator.h>

namespace foundation {
  template <size_t _BlockSize>
  class FOUNDATION_EXPORT TempAllocator
    : public Allocator 
  {
    FOUNDATION_NON_COPYABLE(TempAllocator);

    private:
      struct Block {
        Block* next;
        size_t num_used_bytes;
        uint8_t bytes[_BlockSize];

        Block() 
          : next(nullptr)
          , num_used_bytes(0)
        {
          zero((void*)&bytes[0], _BlockSize);
        }
      };

    public:
      explicit TempAllocator( Allocator& allocator );
      ~TempAllocator();

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
      Block _head;
  };

  typedef TempAllocator<256>  TempAllocator256;
  typedef TempAllocator<512>  TempAllocator512;
  typedef TempAllocator<1024> TempAllocator1024;
  typedef TempAllocator<2048> TempAllocator2048;
  typedef TempAllocator<4096> TempAllocator4096;
} // foundation

#endif // _FOUNDATION_TEMP_ALLOCATOR_H_