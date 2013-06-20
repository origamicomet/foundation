// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_NETWORK_ADDRESS_H_
#define _FOUNDATION_SYSTEM_NETWORK_ADDRESS_H_

// Represents an internet IPv4 or IPv6 address.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>

namespace foundation {
  namespace Network {
    class Socket;
    class FOUNDATION_EXPORT Address final {
      private:
        friend class Socket;

      public:
        Address()
        {
          _ipv6 = false;
          zero((void*)&_addr, sizeof(_addr));
          _port = 0;
        }

        Address(
          const Address& addr )
        {
          _ipv6 = addr._ipv6;
          copy((void*)&_addr, (const void*)&addr._addr, sizeof(_addr));
          _port = addr._port;
        }

        Address& operator= (
          const Address& addr )
        {
          _ipv6 = addr._ipv6;
          copy_safe((void*)&_addr, (const void*)&addr._addr, sizeof(_addr));
          _port = addr._port;
          return *this;
        }

      public:
        static bool from_string(
          const char* str,
          Address& addr );

        static bool from_host_name(
          const char* hostname,
          Address& addr );

      public:
        typedef uint8_t IPv4[4];
        typedef uint8_t IPv6[16];

        FOUNDATION_INLINE bool is_ipv4() const
        { return !_ipv6; }

        FOUNDATION_INLINE bool is_ipv6() const
        { return _ipv6; }

        FOUNDATION_INLINE IPv4& ipv4()
        { return _addr.ipv4; }

        FOUNDATION_INLINE const IPv4& ipv4() const
        { return _addr.ipv4; }

        FOUNDATION_INLINE IPv6& ipv6()
        { return _addr.ipv6; }

        FOUNDATION_INLINE const IPv6& ipv6() const
        { return _addr.ipv6; }

        FOUNDATION_INLINE uint16_t& port()
        { return _port; }

        FOUNDATION_INLINE const uint16_t& port() const
        { return _port; }

      private:
        bool _ipv6;

        union {
          IPv4 ipv4;
          IPv6 ipv6;
        } _addr;

        uint16_t _port;
    };
  } // Network
} // foundation

#endif // _FOUNDATION_SYSTEM_NETWORK_ADDRESS_H_
