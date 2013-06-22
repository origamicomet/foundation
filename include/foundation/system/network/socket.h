// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_NETWORK_SOCKET_H_
#define _FOUNDATION_SYSTEM_NETWORK_SOCKET_H_

// Provides a cross-platform wrapper around BSD-style sockets.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>

#include <foundation/system/network/address.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #include <WinSock2.h>
  #include <Ws2TcpIp.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  namespace Network {
    class FOUNDATION_EXPORT Socket final {
      private:
        static const unsigned invalid = ~0u;

      public:
        Socket();

        Socket(
          const Socket& s );

        Socket& operator= (
          const Socket& s );

        ~Socket();

      public:
        bool connect(
          const Address& addr,
          const int timeout = -1 );

        void disconnect();

        bool bind(
          const Address& addr,
          const bool tcp = false );

        static const int unlimited = -1;

        bool listen(
          const int backlog = unlimited );

        bool accept(
          Socket& socket,
          Address& addr );

        bool shutdown(
          const bool send = true,
          const bool receive = true );

        int send(
          const void* buffer,
          size_t num_of_bytes );

        bool send_all(
          const void* buffer,
          size_t num_of_bytes );

        int send(
          const Address& to,
          const void* buffer,
          size_t num_of_bytes );

        int receive(
          void* buffer,
          size_t num_of_bytes );

        bool receive_all(
          void* buffer,
          size_t num_of_bytes );

        int receive(
          const Address& from,
          void* buffer,
          size_t num_of_bytes );

      public:
        bool set_non_blocking(
          const bool non_blocking );

        bool set_broadcasting(
          const bool broadcasting );

        bool set_reusing_address(
          const bool reuse );

        bool set_send_buffering(
          const size_t num_of_bytes );

        bool set_receive_buffering(
          const size_t num_of_bytes );

        bool set_sending_timeout(
          const size_t miliseconds );

        bool set_receiving_timeout(
          const size_t miliseconds );

      private:
        SOCKET _s;
        int32_t* _refs;
        bool _ipv6;
    };
  } // Network
} // foundation

#endif // _FOUNDATION_SYSTEM_NETWORK_SOCKET_H_
