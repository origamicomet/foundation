// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALLOCATORS_PROXY_H_
#define _FOUNDATION_ALLOCATORS_PROXY_H_

// Provides a proxying (pass-thru) allocator.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/allocator.h>

namespace foundation {
  class FOUNDATION_EXPORT ProxyAllocator final
    : public Allocator
  {
    __foundation_trait(ProxyAllocator, non_copyable);

    public:
      ProxyAllocator(
        const char* name,
        Allocator& to );

      ~ProxyAllocator();

    public:
      void* alloc(
        size_t num_bytes,
        size_t alignment = 4 ) override;

      void* realloc(
        void* ptr,
        size_t num_bytes,
        size_t alignment = 4 ) override;

      void free(
        void* ptr ) override;

    public:
      uint64_t memory_usage() override;
      bool memory_usage_counts_towards_total() override;
      uint64_t num_of_allocations() override;
      uint64_t num_of_reallocations() override;
      uint64_t num_of_frees() override;

    private:
      Allocator& _to;

    private:
    #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
      uint64_t _num_of_allocs;
      uint64_t _num_of_reallocs;
      uint64_t _num_of_frees;
    #endif
  };
} // foundation

#endif // _FOUNDATION_ALLOCATORS_PROXY_H_
