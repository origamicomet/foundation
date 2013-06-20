// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/network/socket.h>

namespace foundation {
  namespace Network {
    Socket::Socket()
      : _s(Socket::invalid)
      , _owns(false)
      , _ipv6(false)
    {
    }

    Socket::Socket(
      const Socket& s
    ) : _s(s._s)
      , _owns(false)
      , _ipv6(s._ipv6)
    {
    }

    Socket& Socket::operator= (
      const Socket& s )
    {
      if (&s == this)
        return *this;
      if (_s != Socket::invalid)
        if (_owns)
          ::closesocket(_s);
      _s = s._s;
      _owns = false;
      _ipv6 = s._ipv6;
      return *this;
    }

    Socket::~Socket()
    {
      if (_s != Socket::invalid)
        if (_owns)
          ::closesocket(_s);
    }

    bool Socket::connect(
      const Address& addr )
    {
      if (_s != Socket::invalid)
        return false;
      _s = ::socket(addr.ipv4() ? AF_INET : AF_INET6, SOCK_STREAM, IPPROTO_TCP);
      if (_s == Socket::invalid)
        return false;
      _owns = true;
      _ipv6 = addr.is_ipv6();

      if (addr.is_ipv4()) {
        struct sockaddr_in sa;
        zero((void*)&sa, sizeof(struct sockaddr_in));
        sa.sin_family = AF_INET;
        sa.sin_port = htons(addr.port());
        copy((void*)&sa.sin_addr, (const void*)&addr.ipv4(), 4);
        if (::connect(_s, (struct sockaddr*)&sa, sizeof(struct sockaddr_in)))
          return true;
      } else {
        struct sockaddr_in6 sa;
        zero((void*)&sa, sizeof(struct sockaddr_in6));
        sa.sin6_family = AF_INET6;
        sa.sin6_port = htons(addr.port());
        copy((void*)&sa.sin6_addr, (const void*)&addr.ipv6(), 16);
        if (::connect(_s, (struct sockaddr*)&sa, sizeof(struct sockaddr_in6)))
          return true;
      }

      ::closesocket(_s);
      _s = Socket::invalid;
      _owns = false;
      return false;
    }

    bool Socket::bind(
      const Address& addr,
      const bool tcp )
    {
      if (_s != Socket::invalid)
        return false;
      _s = ::socket(
        addr.ipv4() ? AF_INET : AF_INET6,
        tcp ? SOCK_STREAM : SOCK_DGRAM,
        tcp ? IPPROTO_TCP : IPPROTO_UDP);
      if (_s == Socket::invalid)
        return false;
      _owns = true;
      _ipv6 = addr.is_ipv6();

      if (addr.is_ipv4()) {
        struct sockaddr_in sa;
        zero((void*)&sa, sizeof(struct sockaddr_in));
        sa.sin_family = AF_INET;
        sa.sin_port = htons(addr.port());
        copy((void*)&sa.sin_addr, (const void*)&addr.ipv4(), 4);
        if (::bind(_s, (struct sockaddr*)&sa, sizeof(struct sockaddr_in)))
          return true;
      } else {
        struct sockaddr_in6 sa;
        zero((void*)&sa, sizeof(struct sockaddr_in6));
        sa.sin6_family = AF_INET6;
        sa.sin6_port = htons(addr.port());
        copy((void*)&sa.sin6_addr, (const void*)&addr.ipv6(), 16);
        if (::bind(_s, (struct sockaddr*)&sa, sizeof(struct sockaddr_in6)))
          return true;
      }

      ::closesocket(_s);
      _s = Socket::invalid;
      _owns = false;
      return false;
    }

    bool Socket::listen(
      const int backlog )
    {
      if (_s == Socket::invalid)
        return false;
      if (::listen(_s, (backlog < 0) ? SOMAXCONN : backlog) != 0)
        return false;
      return true;
    }

    bool Socket::accept(
      Socket& socket,
      Address& addr )
    {
      if (socket._s != Socket::invalid)
        return false;
      if (_s == Socket::invalid)
        return false;

      if (!_ipv6) {
        struct sockaddr_in sa;
        int sa_len = sizeof(struct sockaddr_in);
        SOCKET accepted = ::accept(_s, (struct sockaddr*)&sa, &sa_len);
        if (accepted == Socket::invalid)
          return false;
        addr._ipv6 = false;
        addr._port = ntohs(sa.sin_port);
        copy((void*)&addr._addr.ipv4, (const void*&)sa.sin_addr, 4);
        socket._s = accepted;
        socket._owns = true;
        socket._ipv6 = false;
        return true;
      } else {
        struct sockaddr_in6 sa;
        int sa_len = sizeof(struct sockaddr_in6);
        SOCKET accepted = ::accept(_s, (struct sockaddr*)&sa, &sa_len);
        if (accepted == Socket::invalid)
          return false;
        addr._ipv6 = true;
        addr._port = ntohs(sa.sin6_port);
        copy((void*)&addr._addr.ipv6, (const void*)&sa.sin6_addr, 16);
        socket._s = accepted;
        socket._owns = true;
        socket._ipv6 = true;
        return true;
      }

      __builtin_unreachable();
    }

    bool Socket::shutdown(
      const bool send,
      const bool receive )
    {
      if (_s == Socket::invalid)
        return false;
      if (send)
        if (shutdown(_s, SD_SEND) != 0)
          return false;
      if (receive)
        if (shutdown(_s, SD_RECEIVE) != 0)
          return false;
      return (send | receive);
    }

    int Socket::send(
      const void* buffer,
      size_t num_of_bytes )
    {
      assert(buffer != nullptr);
      if (_s == Socket::invalid)
        return -1;
      return ::send(_s, (const char*)buffer, num_of_bytes, 0);
    }

    int Socket::send(
      const Address& to,
      const void* buffer,
      size_t num_of_bytes )
    {
      if (_s == Socket::invalid)
        return -1;
      return -1;
    }

    int Socket::receive(
      void* buffer,
      size_t num_of_bytes )
    {
      assert(buffer != nullptr);
      if (_s == Socket::invalid)
        return -1;
      return ::recv(_s, (char*)buffer, num_of_bytes, 0);
    }

    int Socket::receive(
      const Address& from,
      void* buffer,
      size_t num_of_bytes )
    {
      if (_s == Socket::invalid)
        return -1;
      return -1;
    }

    bool Socket::set_non_blocking(
      const bool non_blocking )
    {
      return false;
    }

    bool Socket::set_broadcasting(
      const bool broadcasting )
    {
      if (_s == Socket::invalid)
        return false;
      const int v = broadcasting ? 1 : 0;
      return (setsockopt(_s, SOL_SOCKET, SO_BROADCAST, (char*)&v, sizeof(int)) == 0);
    }

    bool Socket::set_reusing_address(
      const bool reuse )
    {
      if (_s == Socket::invalid)
        return false;
      const int v = reuse ? 1 : 0;
      return (setsockopt(_s, SOL_SOCKET, SO_REUSEADDR, (char*)&v, sizeof(int)) == 0);
    }

    bool Socket::set_send_buffering(
      const size_t num_of_bytes )
    {
      if (_s == Socket::invalid)
        return false;
      const int v = num_of_bytes;
      return (setsockopt(_s, SOL_SOCKET, SO_SNDBUF, (char*)&v, sizeof(int)) == 0);
    }

    bool Socket::set_receive_buffering(
      const size_t num_of_bytes )
    {
      if (_s == Socket::invalid)
        return false;
      const int v = num_of_bytes;
      return (setsockopt(_s, SOL_SOCKET, SO_RCVBUF, (char*)&v, sizeof(int)) == 0);
    }

    bool Socket::set_sending_timeout(
      const size_t miliseconds )
    {
      if (_s == Socket::invalid)
        return false;
      const int v = miliseconds;
      return (setsockopt(_s, SOL_SOCKET, SO_SNDTIMEO, (char*)&v, sizeof(int)) == 0);
    }

    bool Socket::set_receiving_timeout(
      const size_t miliseconds )
    {
      if (_s == Socket::invalid)
        return false;
      const int v = miliseconds;
      return (setsockopt(_s, SOL_SOCKET, SO_RCVTIMEO, (char*)&v, sizeof(int)) == 0);
    }
  } // Network
} // foundation

