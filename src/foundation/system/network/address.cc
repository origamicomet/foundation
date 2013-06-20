// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

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
    bool Address::from_string(
      const char* str,
      Address& addr )
    {
      assert(str != nullptr);

      try_ipv6: {
        struct sockaddr_in6 sa;
        if (!inet_pton(AF_INET6, str, &sa.sin6_addr))
          goto try_ipv4;
        copy((void*)&addr._addr.ipv6, (const void*)&sa.sin6_addr, sizeof(IPv6));
        addr._port = sa.sin6_port;
        addr._ipv6 = true;
        return true;
      }

      try_ipv4: {
        struct sockaddr_in sa;
        if (!inet_pton(AF_INET, str, &(sa.sin_addr)))
          goto failed;
        copy((void*)&addr._addr.ipv4, (const void*)&sa.sin_addr, sizeof(IPv4));
        addr._port = sa.sin_port;
        addr._ipv6 = false;
        return true;
      }

    failed:
      return false;
    }

    bool Address::from_host_name(
      const char* hostname,
      Address& addr )
    {
      assert(hostname != nullptr);

      struct addrinfo* ai;
      zero((void*)&ai, sizeof(struct addrinfo));
      if (getaddrinfo(hostname, NULL, NULL, &ai) != 0)
        goto failed;
      if (ai->ai_family == AF_INET6)
        goto ipv6;

    ipv4:
      copy((void*)&addr._addr.ipv4, (const void*)&((struct sockaddr_in*)ai->ai_addr)->sin_addr, sizeof(IPv4));
      addr._port = ((struct sockaddr_in*)ai->ai_addr)->sin_port;
      freeaddrinfo(ai);
      addr._ipv6 = false;
      return true;

    ipv6:
      copy((void*)&addr._addr.ipv6, (const void*)&((struct sockaddr_in6*)ai->ai_addr)->sin6_addr, sizeof(IPv6));
      addr._port = ((struct sockaddr_in6*)ai->ai_addr)->sin6_port;
      freeaddrinfo(ai);
      addr._ipv6 = true;
      return true;

    failed:
      return false;
    }
  } // Network
} // foundation
