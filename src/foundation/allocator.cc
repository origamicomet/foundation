// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/allocator.h>

#include <foundation/assert.h>
#include <foundation/allocators/proxy.h>

#if defined(FOUNDATION_TRACK_MEMORY_USAGE)
  namespace foundation {
    Mutex Allocator::_Statistics::mutex;
    Allocator* Allocator::_Statistics::head = nullptr;
    Allocator* Allocator::_Statistics::tail = nullptr;
  } // foundation
#endif

#include "../nedmalloc.h"
namespace foundation {
  namespace {
    class HeapAllocator final
      : public Allocator
    {
      __foundation_trait(HeapAllocator, non_copyable);

      public:
        HeapAllocator()
          : Allocator("heap")
        #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
          , _num_of_allocs(0)
          , _num_of_reallocs(0)
          , _num_of_frees(0)
        #endif
        {}

        ~HeapAllocator()
        {}

      public:
        void* alloc(
          size_t num_bytes,
          size_t alignment ) override
        {
        #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
          _num_of_allocs += 1;
        #endif
          return nedmalloc2(num_bytes, alignment, 0);
        }

        void* realloc(
          void* ptr,
          size_t num_bytes,
          size_t alignment ) override
        {
          if (!ptr)
            return alloc(num_bytes, alignment);
          if (num_bytes == 0)
            { free(ptr); return nullptr; }
        #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
          _num_of_reallocs += 1;
        #endif
          return nedrealloc2(ptr, num_bytes, alignment, 0);
        }

        void free(
          void* ptr ) override
        {
          if (!ptr)
            return;
        #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
          _num_of_frees += 1;
        #endif
          nedfree2(ptr, 0);
        }

      public:
      #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
        uint64_t memory_usage() override
        { return nedmalloc_footprint(); }

        bool memory_usage_counts_towards_total() override
        { return true; }

        uint64_t num_of_allocations() override
        { return _num_of_allocs; }

        uint64_t num_of_reallocations() override
        { return _num_of_reallocs; }

        uint64_t num_of_frees() override
        { return _num_of_frees; }
      #else
        uint64_t memory_usage() override
        { return Allocator::invalid_memory_usage; }

        bool memory_usage_counts_towards_total() override
        { return true; }

        uint64_t num_of_allocations() override
        { return 0; }

        uint64_t num_of_reallocations() override
        { return 0; }

        uint64_t num_of_frees() override
        { return 0; }
      #endif

      private:
      #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
        uint64_t _num_of_allocs;
        uint64_t _num_of_reallocs;
        uint64_t _num_of_frees;
      #endif
    };
  }
} // foundation

namespace foundation {
  namespace Allocators {
    Allocator& heap() {
      static HeapAllocator heap;
      return heap;
    }

    Allocator& scratch() {
      static ProxyAllocator scratch("scratch", heap());
      return scratch;
    }

    void for_each(
      bool (*callback)(
        Allocator* allocator,
        void* closure ),
      void* closure )
    {
    #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
      #if defined(FOUNDATION_MEMORY_USAGE_STATISTICS_ARE_THREAD_SAFE)
        Mutex::ScopedLock lock(Allocator::_Statistics::mutex);
      #endif

      Allocator* allocator = Allocator::_Statistics::head;
      while (allocator) {
        if (!callback(allocator, closure))
          break;
        if (allocator->statistics.next == Allocator::_Statistics::head)
          break;
        allocator = allocator->statistics.next;
      }
    #else
      (void)callback;
      (void)closure;
    #endif
    }

    static bool __memory_usage_for_each(
      Allocator* allocator, void* closure )
    {
      assert(allocator != nullptr);
      if (allocator->memory_usage() == Allocator::invalid_memory_usage)
        return true;
      if (!allocator->memory_usage_counts_towards_total())
        return true;
      *((uint64_t*)closure) += allocator->memory_usage();
    }

    uint64_t memory_usage()
    {
      uint64_t mem_usage = 0;
      for_each(&__memory_usage_for_each, (void*)&mem_usage);
      return mem_usage;
    }

    static bool __num_of_allocations_for_each(
      Allocator* allocator, void* closure )
    {
      assert(allocator != nullptr);
      *((uint64_t*)closure) += allocator->num_of_allocations();
    }

    uint64_t num_of_allocations()
    {
      uint64_t num_of_allocs = 0;
      for_each(&__num_of_allocations_for_each, (void*)&num_of_allocs);
      return num_of_allocs;
    }

    static bool __num_of_reallocations_for_each(
      Allocator* allocator, void* closure )
    {
      assert(allocator != nullptr);
      *((uint64_t*)closure) += allocator->num_of_reallocations();
    }

    uint64_t num_of_reallocations()
    {
      uint64_t num_of_reallocs = 0;
      for_each(&__num_of_reallocations_for_each, (void*)&num_of_reallocs);
      return num_of_reallocs;
    }

    static bool __num_of_frees_for_each(
      Allocator* allocator, void* closure )
    {
      assert(allocator != nullptr);
      *((uint64_t*)closure) += allocator->num_of_frees();
    }

    uint64_t num_of_frees()
    {
      uint64_t num_of_frees = 0;
      for_each(&__num_of_frees_for_each, (void*)&num_of_frees);
      return num_of_frees;
    }
  } // Allocators
} // foundation

namespace foundation {
  Allocator::Allocator(
    const char* name )
  {
    register_for_memory_usage_statistics(name);
  }

  Allocator::~Allocator()
  {
    unregister_from_memory_usage_statistics();
  }

  void Allocator::register_for_memory_usage_statistics(
    const char* name )
  {
    assert(name != nullptr);

  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    #if defined(FOUNDATION_MEMORY_USAGE_STATISTICS_ARE_THREAD_SAFE)
      Mutex::ScopedLock lock(Allocator::_Statistics::mutex);
    #endif

    statistics.name = name;
    statistics.next = _Statistics::head;
    statistics.prev = _Statistics::tail;

    Allocator*& head = Allocator::_Statistics::head;
    Allocator*& tail = Allocator::_Statistics::tail;

    if (head) {
      head->statistics.prev = this;
    } else {
      head = this;
      head->statistics.next = this;
      head->statistics.prev = this;
    }

    if (tail) {
      tail->statistics.next = this;
      statistics.prev = tail;
      tail = this;
    } else {
      tail = this;
      tail->statistics.next = this;
      tail->statistics.prev = this;
    }
  #else
    (void)name;
  #endif
  }

  void Allocator::unregister_from_memory_usage_statistics()
  {
  #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
    #if defined(FOUNDATION_MEMORY_USAGE_STATISTICS_ARE_THREAD_SAFE)
      Mutex::ScopedLock lock(Allocator::_Statistics::mutex);
    #endif

    statistics.prev->statistics.next = statistics.next;
    statistics.next->statistics.prev = statistics.prev;

    if (_Statistics::head == this)
      _Statistics::head = nullptr;
    if (_Statistics::tail == this)
      _Statistics::tail == nullptr;
  #endif
  }
} // foundation
