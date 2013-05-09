// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/allocators/proxy.h>

namespace foundation {
  ProxyAllocator::ProxyAllocator(
    const char* name,
    Allocator& to
  ) : Allocator(name)
    , _to(to)
  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    , _num_of_allocs(0)
    , _num_of_reallocs(0)
    , _num_of_frees(0)
  #endif
  {}

  ProxyAllocator::~ProxyAllocator()
  {
  }

  void* ProxyAllocator::alloc(
    size_t num_bytes,
    size_t alignment )
  {
    if (num_bytes == 0)
      return nullptr;
  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    _num_of_allocs += 1;
  #endif
    return _to.alloc(num_bytes, alignment);
  }

  void* ProxyAllocator::realloc(
    void* ptr,
    size_t num_bytes,
    size_t alignment )
  {
  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    if (!ptr)
      _num_of_allocs += 1;
    else if (num_bytes == 0)
      _num_of_frees += 1;
    else
      _num_of_reallocs += 1;
  #endif
    return _to.realloc(ptr, num_bytes, alignment);
  }

  void ProxyAllocator::free(
    void* ptr )
  {
  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    if (ptr)
      _num_of_frees += 1;
  #endif
    _to.free(ptr);
  }

  uint64_t ProxyAllocator::memory_usage()
  {
  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    return Allocator::invalid_memory_usage;
  #else
    return Allocator::invalid_memory_usage;
  #endif
  }

  bool ProxyAllocator::memory_usage_counts_towards_total()
  {
    return true;
  }

  uint64_t ProxyAllocator::num_of_allocations()
  {
  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    return _num_of_allocs;
  #else
    return 0;
  #endif
  }

  uint64_t ProxyAllocator::num_of_reallocations()
  {
  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    return _num_of_reallocs;
  #else
    return 0;
  #endif
  }

  uint64_t ProxyAllocator::num_of_frees()
  {
  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    return _num_of_frees;
  #else
    return 0;
  #endif
  }
} // foundation
