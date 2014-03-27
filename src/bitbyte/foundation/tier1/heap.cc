//=== bitbyte/foundation/tier1/heap.cc =======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier1/allocator.h>

// Use nedmalloc instead of the system allocator.
#include "nedmalloc.c.h"

namespace bitbyte {
namespace foundation {
namespace tier1 {

namespace {

class BITBYTE_FOUNDATION_TIER1_EXPORT Heap : public Allocator {
  public: // constructors:
    Heap();

  private: // copy-constructors:
    Heap(const Heap &heap);

  private: // assignment operators:
    Heap &operator=(const Heap &heap);

  public: // destructor:
    ~Heap();

  public: // accessors:
    const char *name() const;
    size_t memory_usage() const;
    size_t allocations() const;
    size_t reallocations() const;
    size_t frees() const;

  public: // methods:
    void *alloc(size_t sz, size_t alignment);
    void *realloc(void *ptr, size_t sz, size_t alignment);
    void free(void *ptr);

  private:
    size_t num_allocations_;
    size_t num_reallocations_;
    size_t num_frees_;
};

Heap::Heap()
  : Allocator()
  , num_allocations_(0)
  , num_reallocations_(0)
  , num_frees_(0)
{
  this->register_for_inspection();
}

Heap::~Heap()
{
  this->unregister_from_inspection();
}

const char *Heap::name() const {
  return "heap";
}

size_t Heap::memory_usage() const {
  return ::nedmallinfo().uordblks;
}

size_t Heap::allocations() const {
  return num_allocations_;
}

size_t Heap::reallocations() const {
  return num_reallocations_;
}

size_t Heap::frees() const {
  return num_frees_;
}

void *Heap::alloc(size_t sz, size_t alignment) {
  num_allocations_++;
  return ::nedmalloc2(sz, alignment, 0);
}

void *Heap::realloc(void *ptr, size_t sz, size_t alignment) {
  num_reallocations_++;
  return ::nedrealloc2(ptr, sz, alignment, 0);
}

void Heap::free(void *ptr) {
  num_frees_++;
  ::nedfree2(ptr, 0);
}

}

static Heap heap_;
Allocator &heap() {
  return heap_;
}

} // tier1
} // foundation
} // bitbyte
