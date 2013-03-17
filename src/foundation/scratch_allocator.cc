// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/scratch_allocator.h>
#include <foundation/memory.h>

namespace foundation {
  ScratchAllocator::ScratchAllocator(
    Allocator& allocator,
    size_t num_bytes
  ) : _allocator(allocator)
    , _begin(0), _end(0)
    , _allocate(0), _free(0)
  {
    _begin = (uintptr_t)allocator.alloc(num_bytes);
    _end = _begin + num_bytes;
    _allocate = _begin;
    _free = _begin;
  }

  ScratchAllocator::~ScratchAllocator()
  {
    assert(_allocate == _free);
    _allocator.free((void*)_begin);
  }

  void* ScratchAllocator::alloc(
    size_t num_bytes,
    size_t alignment )
  {
    assert((alignment % 4) == 0);
    num_bytes = ((num_bytes + 3) / 4) * 4;

    uintptr_t ptr = _allocate;
    Header* header = (Header*)ptr;
    void* p = align_forward(((void*)(header + 1)), alignment);
    ptr = (uintptr_t)p + num_bytes;

    if (ptr > _end) {
      header->num_bytes = ((uintptr_t)_end - (uintptr_t)header) | 0x80000000u;
      ptr = _begin;
      header = (Header *)ptr;
      p = align_forward(((void*)(header + 1)), alignment);
      ptr = (uintptr_t)p + num_bytes;
    }
    
    if (is_allocated((void*)ptr))
      return _allocator.alloc(num_bytes, alignment);

    header->num_bytes = (ptr - (uintptr_t)header);
    uint32_t* pad = ((uint32_t*)(header + 1));
    while (pad < p) *pad++ = Header::Padding;
    _allocate = ptr;
    return p;
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
    if (!ptr)
      return;

    if ((ptr < (void*)_begin) || (ptr >= (void*)_end)) {
      _allocator.free(ptr);
      return;
    }

    Header* header; {
      uint32_t* pad = ((uint32_t*)ptr);
      while (pad[-1] == Header::Padding)
        --pad;
      header = ((Header*)(pad - 1));
    }

    assert((header->num_bytes & 0x80000000u) == 0);
    header->num_bytes = header->num_bytes | 0x80000000u;

    while (_free != _allocate) {
      header = (Header*)_free;
      if ((header->num_bytes & 0x80000000u) == 0)
        break;

      _free += header->num_bytes & 0x7fffffffu;
      if (_free == _end)
        _free = _begin;
    }
  }

  bool ScratchAllocator::is_allocated( void* ptr ) const
  {
    if (_allocate == _free)
      return false;

    if (_allocate > _free)
      return ((ptr >= (void*)_free) && (ptr < (void*)_allocate));

    return ((ptr >= (void*)_free) || (ptr < (void*)_allocate));
  }
} // foundation