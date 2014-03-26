//=== bitbyte/foundation/tier1/allocator.h ===================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier1/allocator.h
/// @brief Provides an inspectable allocator interface.
///

#ifndef _BITBYTE_FOUNDATION_TIER1_ALLOCATOR_H_
#define _BITBYTE_FOUNDATION_TIER1_ALLOCATOR_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/export.h>

namespace bitbyte {
namespace foundation {
namespace tier1 {

class BITBYTE_FOUNDATION_TIER1_EXPORT Allocator {
  private: // constructors:
    Allocator();

  private: // copy-constructors:
    Allocator(const Allocator &allocator);

  private: // assignment operators:
    Allocator &operator=(const Allocator &allocator);

  public: // destructor:
    virtual ~Allocator();

  protected: // tracking:
    /// ...
    void register_for_inspection() const;

    /// ...
    void unregister_from_inspection() const;

  public: // accessors:
    /// ...
    virtual const char *name() const;

    /// ...
    virtual size_t memory_usage() const = 0;

    /// ...
    virtual size_t allocations() const = 0;

    /// ...
    virtual size_t reallocations() const = 0;

    /// ...
    virtual size_t frees() const = 0;

  public: // methods:
    /// ...
    virtual void *alloc(size_t sz, size_t alignment = bitbyte_foundation_alignof(int)) = 0;

    /// ...
    virtual void *realloc(void *ptr, size_t sz, size_t alignment = bitbyte_foundation_alignof(int)) = 0;

    /// ...
    virtual void free(void *ptr) = 0;
};

namespace allocators {

/// ...
extern BITBYTE_FOUNDATION_TIER1_EXPORT void for_each(
  bool (*callback)(const Allocator *allocator, void *up),
  void *up = NULL);

/// ...
extern BITBYTE_FOUNDATION_TIER1_EXPORT void stats(
  size_t &memory_usage,
  size_t &allocations,
  size_t &reallocations,
  size_t &frees);

} // allocators

} // tier1
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER1_ALLOCATOR_H_
