//=== bitbyte/foundation/tier2/thread.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier2/thread.h
/// @brief Provides thread management.
///

#ifndef _BITBYTE_FOUNDATION_TIER2_THREAD_H_
#define _BITBYTE_FOUNDATION_TIER2_THREAD_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/export.h>

namespace bitbyte {
namespace foundation {
namespace tier2 {

class BITBYTE_FOUNDATION_TIER2_EXPORT Thread {
  public: // types:
    ///
    typedef uint32_t Affinity;

    ///
    typedef void (*EntryPoint)(void *up);

  private: // constructor:
    Thread();

  private: // copy-constructor:
    Thread(const Thread &thread);

  private: // assignment operator:
    Thread &operator=(const Thread &thread);

  private: // destructor:
    ~Thread();

  public: // accessors:
    /// ...
    Thread::Affinity affinity() const;

    /// ...
    Thread &set_affinity(const Thread::Affinity affinity);

  public: // static methods:
    /// ...
    static Thread &create(Thread::EntryPoint entry_point, void *up = NULL);

  public: // methods:
    /// ...
    Thread &start();

    /// ...
    Thread &suspend();

    /// ...
    Thread &resume();

    /// ...
    void terminate();

    /// ...
    void detach();

    /// ...
    void join();
};

} // tier2
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER2_THREAD_H_
