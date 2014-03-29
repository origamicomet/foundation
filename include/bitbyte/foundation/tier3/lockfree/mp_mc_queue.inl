//=== bitbyte/foundation/tier3/lockfree/mp_mc_queue.inl ======================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier3/lockfree/mp_mc_queue.inl
/// @brief ...
///

#ifndef _BITBYTE_FOUNDATION_TIER3_LOCKFREE_MP_MC_QUEUE_INL_
#define _BITBYTE_FOUNDATION_TIER3_LOCKFREE_MP_MC_QUEUE_INL_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/tier2.h>
#include <bitbyte/foundation/tier3/export.h>

namespace bitbyte {
namespace foundation {
namespace tier3 {
namespace lockfree {

//===----------------------------------------------------------------------===//
// Constructors:
//

template <typename T>
MpMcQueue<T>::MpMcQueue(uint32_t sz, foundation::tier1::Allocator &allocator)
  : allocator_(allocator)
  , buffer_((MpMcQueue<T>::Sequenced *)allocator.alloc(sizeof(MpMcQueue<T>::Sequenced), alignof(MpMcQueue<T>::Sequenced)))
  , buffer_mask_(sz - 1)
{
  bitbyte_foundation_assert(debug, sz >= 2);
  bitbyte_foundation_assert(debug, (sz & (sz - 1)) == 0);
  for (uint32_t i = 0; i < sz; ++i)
    foundation::tier2::atomic::relaxed::store(&buffer_[i].sequence, i);
  foundation::tier2::atomic::relaxed::store(&enqueue_, 0);
  foundation::tier2::atomic::relaxed::store(&dequeue_, 0);
}

//===----------------------------------------------------------------------===//
// Copy constructors:
//

#if 0
template <typename T>
MpMcQueue<T>::MpMcQueue(const MpMcQueue<T> &queue) {}
#endif

//===----------------------------------------------------------------------===//
// Assignment operators:
//

#if 0
template <typename T>
MpMcQueue<T> &MpMcQueue<T>::operator=(const MpMcQueue<T> &queue) {}
#endif

//===----------------------------------------------------------------------===//
// Destructor:
//

template <typename T>
MpMcQueue<T>::~MpMcQueue()
{
  allocator_.free((void *)buffer_);
}

//===----------------------------------------------------------------------===//
// MpMcQueue<T>::try_enqueue
//

template <typename T>
bool MpMcQueue<T>::try_enqueue(const T &E)
{
  MpMcQueue<T>::Sequenced *SE;
  uint32_t P = foundation::tier2::atomic::relaxed::load(&enqueue_);
  while (true) {
    SE = &buffer_[P & buffer_mask_];
    uint32_t seq = foundation::tier2::atomic::relaxed::load(&SE->sequence);
    intptr_t diff = (intptr_t)seq - (intptr_t)P;
    if (diff == 0) {
      if (foundation::tier2::atomic::relaxed::compare_and_swap(&enqueue_, P, P + 1) == P)
        break;
    } else if (diff < 0) {
      return false;
    } else {
      P = foundation::tier2::atomic::relaxed::load(&enqueue_);
    }
  }
  SE->element = E;
  foundation::tier2::atomic::relaxed::store(&SE->sequence, P + 1);
  return true;
}

//===----------------------------------------------------------------------===//
// MpMcQueue<T>::enqueue
//

template <typename T>
void MpMcQueue<T>::enqueue(const T &E)
{
  while (!try_enqueue(E));
}

//===----------------------------------------------------------------------===//
// MpMcQueue<T>::try_dequeue
//

template <typename T>
bool MpMcQueue<T>::try_dequeue(T *E)
{
  MpMcQueue<T>::Sequenced *SE;
  uint32_t P = foundation::tier2::atomic::relaxed::load(&dequeue_);
  while (true) {
    SE = &buffer_[P & buffer_mask_];
    uint32_t seq = foundation::tier2::atomic::relaxed::load(&SE->sequence);
    intptr_t diff = (intptr_t)seq - (intptr_t)(P + 1);
    if (diff == 0) {
      if (foundation::tier2::atomic::relaxed::compare_and_swap(&dequeue_, P, P + 1) == P)
        break;
    } else if (diff < 0) {
      return false;
    } else {
      P = foundation::tier2::atomic::relaxed::load(&dequeue_);
    }
  }
  *E = SE->element;
  foundation::tier2::atomic::relaxed::store(&SE->sequence, P + buffer_mask_ + 1);
  return true;
}

//===----------------------------------------------------------------------===//
// MpMcQueue<T>::dequeue
//

template <typename T>
void MpMcQueue<T>::dequeue(T *E)
{
  while (!try_dequeue(E));
}

} // lockfree
} // tier3
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER3_LOCKFREE_MP_MC_QUEUE_INL_
