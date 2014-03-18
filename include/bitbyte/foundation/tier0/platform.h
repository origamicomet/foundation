//=== bitbyte/foundation/tier0/platform.h ====================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier0/platform.h
/// @brief Defines various platforms and convenient pre-processor values,
///  and also provides compile- and run- time utilities related to platforms.
///

#ifndef _BITBYTE_FOUNDATION_TIER0_PLATFORM_H_
#define _BITBYTE_FOUNDATION_TIER0_PLATFORM_H_

#include <bitbyte/foundation/tier0/export.h>

//===----------------------------------------------------------------------===//
// Pre-processor defines
//

/// @def BITBYTE_FOUNDATION_PLATFORM_WINDOWS
/// @brief Microsoft Windows.
///
#define BITBYTE_FOUNDATION_PLATFORM_WINDOWS 0

/// @def BITBYTE_FOUNDATION_PLATFORM_MACOSX
/// @brief Mac OS X.
///
#define BITBYTE_FOUNDATION_PLATFORM_MACOSX 1

/// @def BITBYTE_FOUNDATION_PLATFORM_LINUX
/// @brief Linux.
///
#define BITBYTE_FOUNDATION_PLATFORM_LINUX 2

/// @def BITBYTE_FOUNDATION_PLATFORM_IOS
/// @brief Apple iOS.
///
#define BITBYTE_FOUNDATION_PLATFORM_IOS 3

/// @def BITBYTE_FOUNDATION_PLATFORM_ANDROID
/// @brief Google Android.
///
#define BITBYTE_FOUNDATION_PLATFORM_ANDROID 4

/// @def BITBYTE_FOUNDATION_HOST_PLATFORM
/// @brief ...
///
#ifndef BITBYTE_FOUNDATION_HOST_PLATFORM
  #error ("Please specify which platform you are building Foundation on by defining `BITBYTE_FOUNDATION_HOST_PLATFORM`.")
#else
  #if (BITBYTE_FOUNDATION_HOST_PLATFORM < 0) || (BITBYTE_FOUNDATION_HOST_PLATFORM > 5)
    #error ("You specified an unknown or unsupported platform. Did you define `BITBYTE_FOUNDATION_HOST_PLATFORM` correctly?")
  #endif
#endif

/// @def BITBYTE_FOUNDATION_DONT_AUTODETECT_TARGET_PLATFORM
/// @brief If defined, Foundation won't attempt to detect the target platform
///  based on pre-processor defines.
///

/// @def BITBYTE_FOUNDATION_TARGET_PLATFORM
/// @brief ...
///
#ifdef BITBYTE_FOUNDATION_DONT_AUTODETECT_TARGET_PLATFORM
  #ifndef BITBYTE_FOUNDATION_TARGET_PLATFORM
    #error ("Please specify which platform you are building Foundation for by defining `BITBYTE_FOUNDATION_TARGET_PLATFORM`.")
  #else
    #if (BITBYTE_FOUNDATION_TARGET_PLATFORM < 0) || (BITBYTE_FOUNDATION_TARGET_PLATFORM > 5)
      #error ("You specified an unknown or unsupported platform. Did you define `BITBYTE_FOUNDATION_TARGET_PLATFORM` correctly?")
    #endif
  #endif
#else
  #if (defined(_WIN32) || defined(_WIN64))
    #define BITBYTE_FOUNDATION_TARGET_PLATFORM 0
  #elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if defined(TARGET_OS_IPHONE)
      #define BITBYTE_FOUNDATION_TARGET_PLATFORM 3
    #else
      #define BITBYTE_FOUNDATION_TARGET_PLATFORM 1
    #endif
  #elif defined(__linux__)
    #if defined(ANDROID)
      #define BITBYTE_FOUNDATION_TARGET_PLATFORM 4
    #else
      #define BITBYTE_FOUNDATION_TARGET_PLATFORM 2
    #endif
  #else
    #error ("You are building Foundation for an unknown or unsupported platform.")
  #endif
#endif

//===----------------------------------------------------------------------===//
// Compile- and run- time utilities
//

namespace bitbyte {
namespace foundation {
namespace tier0 {

/// @namespace ::bitbyte::foundation::tier0::Platforms
/// @brief ...
///
namespace Platforms {
  enum _ {
    /// Unknown.
    Unknown = -1,
    /// Microsoft Windows.
    Windows = 0,
    /// Mac OS X.
    MacOSX = 1,
    /// Linux.
    Linux = 2,
    /// Apple iOS.
    iOS = 3,
    /// Google Android.
    Android = 4,
    /// Native Client.
    NaCl = 5
  };
}

///
class BITBYTE_FOUNDATION_TIER0_EXPORT Platform {
  public: // globals:
    /// ...
    static const Platform host() {
      static const Platform host =
        (Platforms::_)BITBYTE_FOUNDATION_HOST_PLATFORM;
      return host;
    }

    /// ...
    static const Platform &target() {
      static const Platform target =
        (Platforms::_)BITBYTE_FOUNDATION_TARGET_PLATFORM;
      return target;
    }

  public: // constructors:
    Platform(Platforms::_ platform = Platforms::Unknown)
      : _(platform) {
    }

  public: // copy-constructors:
    Platform(const Platform &platform)
      : _(platform._) {
    }

  public: // assignment operators:
    Platform &operator=(const Platform &platform) {
      _ = platform._;
      return *this;
    }

    Platform &operator=(const Platforms::_ platform) {
      _ = platform;
      return *this;
    }

  public: // destructor:
    // ~Platform() {}

  public: // conversion operators:
    operator Platforms::_() {
      return _;
    }

  public: // comparison operators:
    bool operator==(const Platforms::_ rhs) const {
      return (_ == rhs);
    }

    bool operator==(const Platform &rhs) const {
      return (_ == rhs._);
    }

    bool operator!=(const Platforms::_ rhs) const {
      return (_ != rhs);
    }

    bool operator!=(const Platform &rhs) const {
      return (_ != rhs._);
    }

  public: // properties
    /// ...
    bool posix() {
      return (_ == Platforms::MacOSX) ||
             (_ == Platforms::Linux) ||
             (_ == Platforms::iOS) ||
             (_ == Platforms::Android);
    }

  private:
    Platforms::_ _;
};

} // tier0
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER0_PLATFORM_H_
