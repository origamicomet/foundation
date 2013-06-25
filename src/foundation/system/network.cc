// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/network.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #include <WinSock2.h>
  #include <Ws2TcpIp.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  namespace Network {
    bool initialize()
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      WSADATA wd;
      if (WSAStartup(MAKEWORD(1, 1), &wd))
        return false;
      if ((LOBYTE(wd.wVersion) != 1) && (HIBYTE(wd.wVersion) != 1)) {
        WSACleanup();
        return false; }
      return true;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    int get_last_error()
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      int err = WSAGetLastError();
      switch (err) {
        case WSAEWOULDBLOCK:
          return EWOULDBLOCK;
        default:
          return err; }
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }
  } // Network
} // foundation
