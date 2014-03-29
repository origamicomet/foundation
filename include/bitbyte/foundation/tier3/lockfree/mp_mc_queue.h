//=== bitbyte/foundation/tier3/lockfree/mp_mc_queue.h ========================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier3/lockfree/mp_mc_queue.h
/// @brief Provides a fixed-size, multi-producer, and multi-consumer queue.
///

#ifndef _BITBYTE_FOUNDATION_TIER3_LOCKFREE_MP_MC_QUEUE_H_
#define _BITBYTE_FOUNDATION_TIER3_LOCKFREE_MP_MC_QUEUE_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/tier2.h>
#include <bitbyte/foundation/tier3/export.h>

namespace bitbyte {
namespace foundation {
namespace tier3 {
namespace lockfree {

/// @brief
///
template <typename T>
class BITBYTE_FOUNDATION_TIER3_EXPORT MpMcQueue {
  private: // types:
    struct Sequenced {
      foundation::tier2::atomic::u32 sequence;
      T element;
    };

  public: // constructor:
    /// ...
    MpMcQueue(uint32_t sz, foundation::tier1::Allocator &allocator = foundation::tier1::heap());

  private: // copy-constructors:
    MpMcQueue(const MpMcQueue<T> &queue);

  private: // assignment operators:
    MpMcQueue<T> &operator=(const MpMcQueue<T> &queue);

  public: // destructor:
    ~MpMcQueue();

  public: // methods:
    /// ...
    bool try_enqueue(const T &E);

    /// ...
    void enqueue(const T &E);

    /// ...
    bool try_dequeue(T *E);

    /// ...
    void dequeue(T *E);

  private: // members:
    foundation::tier1::Allocator &allocator_;
    Sequenced *buffer_;
    uint32_t buffer_mask_;
    foundation::tier2::atomic::u32 enqueue_;
    foundation::tier2::atomic::u32 dequeue_;
};

} // lockfree
} // tier3
} // foundation
} // bitbyte

#include <bitbyte/foundation/tier3/lockfree/mp_mc_queue.inl>

#endif // _BITBYTE_FOUNDATION_TIER3_LOCKFREE_MP_MC_QUEUE_H_
