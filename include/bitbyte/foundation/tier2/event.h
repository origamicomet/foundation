//=== bitbyte/foundation/tier2/event.h =======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier2/event.h
/// @brief Provides a manually rest event.
///

#ifndef _BITBYTE_FOUNDATION_TIER2_EVENT_H_
#define _BITBYTE_FOUNDATION_TIER2_EVENT_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/export.h>

namespace bitbyte {
namespace foundation {
namespace tier2 {

/// @brief
///
class BITBYTE_FOUNDATION_TIER2_EXPORT Event {
  private: // constructors:
    Event();

  private: // copy-constructors:
    Event(const Event &event);

  private: // assignment operators:
    Event &operator=(const Event &event);

  private: // destructor:
    ~Event();

  public: // management:
    /// ...
    static Event &create();

    /// ...
    void destroy();

  public: // methods:
    /// ...
    void signal();

    /// ...
    void reset();

  public: // properties:
    /// ...
    bool is_signaled();

    /// ...
    bool is_not_signaled();
};

} // tier2
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER2_EVENT_H_
