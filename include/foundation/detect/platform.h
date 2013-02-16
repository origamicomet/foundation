#ifndef _FOUNDATION_DETECT_PLATFORM_H_
#define _FOUNDATION_DETECT_PLATFORM_H_

#if defined(_WIN32) || defined(_WIN64)
  #define FOUNDATION_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
  #include <TargetConditionals.h>
  #if defined(TARGET_OS_IPHONE)
    #define FOUNDATION_PLATFORM_IOS 1
    #define FOUNDATION_PLATFORM_POSIX 1
  #else
    #define FOUNDATION_PLATFORM_MACOSX 1
    #define FOUNDATION_PLATFORM_POSIX 1
  #endif
#elif defined(ANDROID)
  #define FOUNDATION_PLATFORM_ANDROID 1
    #define FOUNDATION_PLATFORM_POSIX 1
#elif defined(__native_client__)
  #define FOUNDATION_PLATFORM_NATIVE_CLIENT 1
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
  #define FOUNDATION_PLATFORM_BSD 1
  #define FOUNDATION_PLATFORM_POSIX 1
#elif defined(__linux__)
  #define FOUNDATION_PLATFORM_LINUX 1
  #define FOUNDATION_PLATFORM_POSIX 1
#else
  #error Unknown or unsupported platform.
#endif

#endif // _FOUNDATION_DETECT_PLATFORM_H_