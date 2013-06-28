// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_NETWORK_SOCKET_SET_H_
#define _FOUNDATION_SYSTEM_NETWORK_SOCKET_SET_H_

// Provides a cross-platform wrapper around BSD-style socket/fd sets.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>

#include <foundation/system/network/socket.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #include <WinSock2.h>
  #include <Ws2TcpIp.h>
  #include <WinError.h>
  #include <errno.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  namespace Network {
    class FOUNDATION_EXPORT SocketSet final {
      public:
        static const size_t limit = FD_SETSIZE;

      public:
        SocketSet();
        ~SocketSet();

      public:
        void clear(
          Socket& socket );

        bool is_set(
          Socket& socket ) const;

        void set(
          Socket& socket );

        void zero();

      public: /* private */
        fd_set _fds;
    };

    extern FOUNDATION_EXPORT int select(
      SocketSet* read,
      SocketSet* write,
      SocketSet* error,
      unsigned timeout = 0 );
  } // Network
} // foundation

#endif // _FOUNDATION_SYSTEM_NETWORK_SOCKET_SET_H_
