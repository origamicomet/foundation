// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/temp_allocator.h>

namespace foundation {
  template <size_t _BlockSize>
  TempAllocator<_BlockSize>::TempAllocator( Allocator& allocator )
    : _allocator(allocator)
  {
    _head.next = nullptr;
    _head.num_used_bytes = 0;
  }

  template <size_t _BlockSize>
  TempAllocator<_BlockSize>::~TempAllocator()
  {
    Block* block = _head.next;
    
    while (block) {
      Block* next = block->next;
      _allocator.free((void*)block);
      block = next;
    }
  }

  template <size_t _BlockSize>
  void* TempAllocator<_BlockSize>::alloc(
    size_t num_bytes,
    size_t alignment )
  {
  }

  template <size_t _BlockSize>
  void* TempAllocator<_BlockSize>::realloc(
    void* ptr,
    size_t num_bytes,
    size_t alignment )
  {
  }

  template <size_t _BlockSize>
  void TempAllocator<_BlockSize>::free(
    void* ptr )
  {
  }
} // foundation