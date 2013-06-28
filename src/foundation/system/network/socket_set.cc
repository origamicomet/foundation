// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/network/socket_set.h>

namespace foundation {
  namespace Network {
    SocketSet::SocketSet()
    {
      FD_ZERO(&_fds);
    }

    SocketSet::~SocketSet()
    {
    }

    void SocketSet::clear(
      Socket& socket )
    {
      if (socket.fd() != Socket::invalid)
        FD_CLR(socket.fd(), &_fds);
    }

    bool SocketSet::is_set(
      Socket& socket ) const
    {
      if (socket.fd() != Socket::invalid)
        return (FD_ISSET(socket.fd(), &_fds) != 0);
      return false;
    }

    void SocketSet::set(
      Socket& socket )
    {
      if (socket.fd() != Socket::invalid)
        FD_SET(socket.fd(), &_fds);
    }

    void SocketSet::zero()
    {
      FD_ZERO(&_fds);
    }

    int select(
      SocketSet* read,
      SocketSet* write,
      SocketSet* error,
      unsigned timeout )
    {
      if (!read && !write && !error)
        return EINVAL;
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      TIMEVAL tov;
      tov.tv_sec = timeout / 1000;
      tov.tv_usec = (timeout % 1000) * 1000;
      return select(
        0, (read ? &read->_fds : NULL),
        (write ? &write->_fds : NULL),
        (error ? &error->_fds : NULL),
        (timeout > 0) ? &tov : NULL);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }
  } // Network
} // foundation

