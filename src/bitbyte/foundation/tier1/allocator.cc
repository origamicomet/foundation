//=== bitbyte/foundation/tier1/allocator.cc ==================================//
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

namespace bitbyte {
namespace foundation {
namespace tier1 {

namespace {

struct RegisteredAllocator_ {
  RegisteredAllocator_ *next;
  const Allocator *allocator;
};

static RegisteredAllocator_ *registered_allocators_ = NULL;

}

//===----------------------------------------------------------------------===//
// Constructors:
//

Allocator::Allocator() {}

//===----------------------------------------------------------------------===//
// Copy constructors:
//

Allocator::Allocator(const Allocator &/*allocator*/) {}

//===----------------------------------------------------------------------===//
// Assignment operators:
//

Allocator &Allocator::operator=(const Allocator &/*allocator*/) { return *this; }

//===----------------------------------------------------------------------===//
// Destructor:
//

Allocator::~Allocator() {}

//===----------------------------------------------------------------------===//
// Allocator::register_for_inspection
//

void Allocator::register_for_inspection() const {
  RegisteredAllocator_ *registered_allocator = new RegisteredAllocator_;
  registered_allocator->next = registered_allocators_;
  registered_allocator->allocator = this;
  registered_allocators_ = registered_allocator;
}

//===----------------------------------------------------------------------===//
// Allocator::unregister_from_inspection
//

void Allocator::unregister_from_inspection() const {
  RegisteredAllocator_ **iter = &registered_allocators_;
  while (*iter) {
    RegisteredAllocator_ *registered_allocator = *iter;
    if (registered_allocator->allocator != this)
      goto next;
    *iter = registered_allocator->next;
    delete registered_allocator;
    break;
  next:
    iter = &registered_allocator->next;
  }
}

//===----------------------------------------------------------------------===//
// Inspection
//

namespace allocators {

void for_each(
  bool (*callback)(const Allocator *allocator, void *up),
  void *up)
{
  RegisteredAllocator_ *iter = registered_allocators_;
  while (iter) {
    if (!callback(iter->allocator, up))
      break;
    iter = iter->next;
  }
}

void stats(
  size_t &memory_usage,
  size_t &allocations,
  size_t &reallocations,
  size_t &frees)
{
  RegisteredAllocator_ *iter = registered_allocators_;
  while (iter) {
    memory_usage += iter->allocator->memory_usage();
    allocations += iter->allocator->allocations();
    reallocations += iter->allocator->reallocations();
    frees += iter->allocator->frees();
    iter = iter->next;
  }
}

} // allocators

} // tier1
} // foundation
} // bitbyte
