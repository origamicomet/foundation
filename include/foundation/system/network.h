// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_NETWORK_H_
#define _FOUNDATION_SYSTEM_NETWORK_H_

// Provides a low-overhead cross-platform around network.

#include <foundation/system/network/address.h>
#include <foundation/system/network/socket.h>

namespace foundation {
  namespace Network {
    extern FOUNDATION_EXPORT bool initialize();
  } // Network
} // foundation

#endif // _FOUNDATION_SYSTEM_NETWORK_H_
