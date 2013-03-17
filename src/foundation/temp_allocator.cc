// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/temp_allocator.h>

namespace foundation {
  template <size_t _BlockSize>
  TempAllocator<_BlockSize>::TempAllocator( Allocator& allocator )
    : _allocator(allocator)
  {
  }

  template <size_t _BlockSize>
  TempAllocator<_BlockSize>::~TempAllocator()
  {
    Block* block = _head.next;
    while (block) {
      Block* next = block->next;
      make_delete(Block, _allocator, block);
      block = next;
    }
  }

  template <size_t _BlockSize>
  void* TempAllocator<_BlockSize>::alloc(
    size_t num_bytes,
    size_t alignment )
  {
    assert(num_bytes > _BlockSize);

    Block* block = &_head;
    while (block) {
      if ((_BlockSize - block->num_used_bytes) < num_bytes) {
        block = block->next;
        continue;
      }

      void* ptr = &block->bytes[block->num_used_bytes];
      void* aligned = align_forward(ptr, alignment);

      const size_t num_used_bytes =
        ((uintptr_t)aligned) - ((uintptr_t)&block->bytes[0]) + num_bytes;

      if (num_used_bytes > _BlockSize)
        break;

      block->num_used_bytes = num_used_bytes;
      return aligned;
    }

    block = &_head;
    while (block->next)
      block = block->next;

    block->next = make_new(Block, _allocator)();
    block = block->next;

    void* ptr = &block->bytes[0];
    void* aligned = align_forward(ptr, alignment);
    
    const size_t num_used_bytes =
      ((uintptr_t)aligned) - ((uintptr_t)&block->bytes[0]) + num_bytes;

    if (num_used_bytes > _BlockSize)
      return nullptr;

    block->num_used_bytes = num_used_bytes;
    return aligned;
  }

  template <size_t _BlockSize>
  void* TempAllocator<_BlockSize>::realloc(
    void* ptr,
    size_t num_bytes,
    size_t alignment )
  {
    (void)ptr;
    return nullptr;
  }

  template <size_t _BlockSize>
  void TempAllocator<_BlockSize>::free(
    void* ptr )
  {
    (void)ptr;
  }
} // foundation