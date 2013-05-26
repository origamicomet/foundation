// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALLOCATOR_H_
#define _FOUNDATION_ALLOCATOR_H_

// Provides a stateful allocator interface along with introspective utilities.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#if defined(FOUNDATION_TRACK_MEMORY_USAGE) && defined(FOUNDATION_MEMORY_USAGE_STATISTICS_ARE_THREAD_SAFE)
  #include <foundation/system/concurrency.h>
#endif

namespace foundation {
  class Allocator;
  namespace Allocators {
    // Returns the heap allocator.
    extern FOUNDATION_EXPORT Allocator& heap();

    // Returns the global scratch allocator.
    extern FOUNDATION_EXPORT Allocator& scratch();

    // Calls |callback| for every registered foundation::Allocator.
    extern FOUNDATION_EXPORT void for_each(
      bool (*callback)(
        Allocator* allocator,
        void* closure ),
      void* closure = nullptr );

    // Returns the total number of actively used bytes, across all allocators.
    extern FOUNDATION_EXPORT uint64_t memory_usage();

    // Returns the total number of allocations, across all allocators.
    extern FOUNDATION_EXPORT uint64_t num_of_allocations();

    // Returns the total number of reallocations, across all allocators.
    extern FOUNDATION_EXPORT uint64_t num_of_reallocations();

    // Returns the total number of frees, across all allocators.
    extern FOUNDATION_EXPORT uint64_t num_of_frees();
  } // Allocators
} // foundation

namespace foundation {
  class FOUNDATION_EXPORT Allocator abstract {
    __foundation_trait(Allocator, non_copyable);

    private:
      friend void foundation::Allocators::for_each(
        bool (*)( Allocator*, void* ), void* );

    protected:
      Allocator(
        const char* name );

      virtual ~Allocator();

    private:
      void register_for_memory_usage_statistics(
        const char* name );

      void unregister_from_memory_usage_statistics();

    public:
      // Allocates |num_bytes| and aligns to to the |alignment| bit-boundry.
      virtual void* alloc(
        size_t num_bytes,
        size_t alignment = 4 ) = 0;

      // Reallocates a previsouly allocated (or reallocated) |ptr|, or frees it
      // if the |num_bytes| is zero.
      virtual void* realloc(
        void* ptr,
        size_t num_bytes,
        size_t alignment = 4 ) = 0;

      // Frees a |ptr|, or does nothing if null.
      virtual void free(
        void* ptr ) = 0;

    public:
      // Returns the total number of actively used bytes.
      virtual uint64_t memory_usage() = 0;

      // Determines if this allocator's memory usage contributes toward the
      // total memory usage that Allocators::memory_usage() determines.
      virtual bool memory_usage_counts_towards_total() = 0;

      // Returned by Allocator::memory_usage to indicate memory usage statistics
      // are not available.
      static const uint64_t invalid_memory_usage = 0xFFFFFFFFFFFFFFFFull;

      // Returns the total number of allocations.
      virtual uint64_t num_of_allocations() = 0;

      // Returns the total number of reallocations.
      virtual uint64_t num_of_reallocations() = 0;

      // Returns the total number of frees.
      virtual uint64_t num_of_frees() = 0;

    private:
    #if defined(FOUNDATION_TRACK_MEMORY_USAGE)
      struct _Statistics {
      #if defined(FOUNDATION_MEMORY_USAGE_STATISTICS_ARE_THREAD_SAFE)
        static Mutex& mutex();
      #endif
        static Allocator *head, *tail;
        const char* name;
        Allocator *next, *prev;
      } statistics;
    #endif
  };
} // foundation

#include <new>

#define make_new( _Type, _Allocator ) \
  new ((_Allocator.alloc(sizeof(_Type), foundation::alignment_of<_Type>::value))) _Type

#define make_delete( _Type, _Allocator, _Instance ) \
  do { (_Instance)->~_Type(); _Allocator.free((void*)(_Instance)); } while (0, 0)

#endif // _FOUNDATION_ALLOCATOR_H_
