// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/allocator.h>

#include <foundation/assert.h>
#include <foundation/allocators/proxy.h>
#include <foundation/thread_safe/static.h>

#if defined(FOUNDATION_TRACK_MEMORY_USAGE)
  namespace foundation {
    static Mutex* __mutex_initializer() {
      return new Mutex();
    }

    static const thread_safe::Static< Mutex >
      __ts_mutex(&__mutex_initializer);

    Mutex& Allocator::_Statistics::mutex() {
      return __ts_mutex();
    }

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
          if (num_bytes == 0)
            return nullptr;
        #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
          __sync_fetch_and_add(&_num_of_allocs, 1);
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
          __sync_fetch_and_add(&_num_of_reallocs, 1);
        #endif
          return nedrealloc2(ptr, num_bytes, alignment, 0);
        }

        void free(
          void* ptr ) override
        {
          if (!ptr)
            return;
        #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
          __sync_fetch_and_add(&_num_of_frees, 1);
        #endif
          nedfree2(ptr, 0);
        }

      public:
      #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
        int64_t memory_usage() override
        { return nedmalloc_footprint(); }

        bool memory_usage_counts_towards_total() override
        { return true; }

        int64_t num_of_allocations() override
        { return _num_of_allocs; }

        int64_t num_of_reallocations() override
        { return _num_of_reallocs; }

        int64_t num_of_frees() override
        { return _num_of_frees; }
      #else
        int64_t memory_usage() override
        { return Allocator::invalid_memory_usage; }

        bool memory_usage_counts_towards_total() override
        { return true; }

        int64_t num_of_allocations() override
        { return 0; }

        int64_t num_of_reallocations() override
        { return 0; }

        int64_t num_of_frees() override
        { return 0; }
      #endif

      private:
      #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
        int64_t _num_of_allocs;
        int64_t _num_of_reallocs;
        int64_t _num_of_frees;
      #endif
    };
  }
} // foundation

namespace foundation {
  namespace Allocators {
    static Allocator* __heap_initializer() {
      return new HeapAllocator();
    }

    static const thread_safe::Static< Allocator >
      __ts_heap(&__heap_initializer);

    Allocator& heap() {
      return __ts_heap();
    }

    static Allocator* __scratch_initializer() {
      return new ProxyAllocator("scratch", heap());
    }

    static const thread_safe::Static< Allocator >
      __ts_scratch(&__scratch_initializer);

    Allocator& scratch() {
      return __ts_scratch();
    }

    void for_each(
      bool (*callback)(
        Allocator* allocator,
        void* closure ),
      void* closure )
    {
    #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
      #if defined(FOUNDATION_MEMORY_USAGE_STATISTICS_ARE_THREAD_SAFE)
        Mutex::ScopedLock lock(Allocator::_Statistics::mutex());
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

    struct Stats {
      int64_t memory_usage;
      int64_t num_of_allocations;
      int64_t num_of_reallocations;
      int64_t num_of_frees;
    };

    static bool __stats_for_each(
      Allocator* allocator, void* closure )
    {
      assert(allocator != nullptr);

      if (allocator->memory_usage() != Allocator::invalid_memory_usage)
        if (allocator->memory_usage_counts_towards_total())
          ((Stats*)closure)->memory_usage += allocator->memory_usage();

      ((Stats*)closure)->num_of_allocations = allocator->num_of_allocations();
      ((Stats*)closure)->num_of_reallocations = allocator->num_of_reallocations();
      ((Stats*)closure)->num_of_frees = allocator->num_of_frees();

      return true;
    }

    void stats(
      int64_t& memory_usage,
      int64_t& num_of_allocations,
      int64_t& num_of_reallocations,
      int64_t& num_of_frees )
    {
      Stats stats;

      stats.memory_usage = 0;
      stats.num_of_allocations = 0;
      stats.num_of_reallocations = 0;
      stats.num_of_frees = 0;

      for_each(&__stats_for_each, (void*)&stats);

      memory_usage = stats.memory_usage;
      num_of_allocations = stats.num_of_allocations;
      num_of_reallocations = stats.num_of_reallocations;
      num_of_frees = stats.num_of_frees;
    }

    static bool __memory_usage_for_each(
      Allocator* allocator, void* closure )
    {
      assert(allocator != nullptr);
      if (allocator->memory_usage() == Allocator::invalid_memory_usage)
        return true;
      if (!allocator->memory_usage_counts_towards_total())
        return true;
      *((int64_t*)closure) += allocator->memory_usage();
      return true;
    }

    int64_t memory_usage()
    {
      int64_t mem_usage = 0;
      for_each(&__memory_usage_for_each, (void*)&mem_usage);
      return mem_usage;
    }

    static bool __num_of_allocations_for_each(
      Allocator* allocator, void* closure )
    {
      assert(allocator != nullptr);
      *((int64_t*)closure) += allocator->num_of_allocations();
      return true;
    }

    int64_t num_of_allocations()
    {
      int64_t num_of_allocs = 0;
      for_each(&__num_of_allocations_for_each, (void*)&num_of_allocs);
      return num_of_allocs;
    }

    static bool __num_of_reallocations_for_each(
      Allocator* allocator, void* closure )
    {
      assert(allocator != nullptr);
      *((int64_t*)closure) += allocator->num_of_reallocations();
      return true;
    }

    int64_t num_of_reallocations()
    {
      int64_t num_of_reallocs = 0;
      for_each(&__num_of_reallocations_for_each, (void*)&num_of_reallocs);
      return num_of_reallocs;
    }

    static bool __num_of_frees_for_each(
      Allocator* allocator, void* closure )
    {
      assert(allocator != nullptr);
      *((int64_t*)closure) += allocator->num_of_frees();
      return true;
    }

    int64_t num_of_frees()
    {
      int64_t num_of_frees = 0;
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
      Mutex::ScopedLock lock(Allocator::_Statistics::mutex());
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
      Mutex::ScopedLock lock(Allocator::_Statistics::mutex());
    #endif

    statistics.prev->statistics.next = statistics.next;
    statistics.next->statistics.prev = statistics.prev;

    if (_Statistics::head == this)
      _Statistics::head = nullptr;
    if (_Statistics::tail == this)
      _Statistics::tail = nullptr;
  #endif
  }
} // foundation
