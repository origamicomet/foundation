//=== bitbyte/foundation/tier0/architecture.h ================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier0/architecture.h
/// @brief Defines various architectures and convenient pre-processor values,
///  and also provides compile- and run- time utilities related to processor
///  architecture.
///

#ifndef _BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_H_
#define _BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_H_

#include <bitbyte/foundation/tier0/export.h>

//===----------------------------------------------------------------------===//
// Pre-processor defines
//

/// @def BITBYTE_FOUNDATION_HOST_ARCHITECTURE
/// @brief ...
///
#ifndef BITBYTE_FOUNDATION_HOST_ARCHITECTURE
  #error ("Please specify which architecture you are building Foundation on by defining `BITBYTE_FOUNDATION_HOST_ARCHITECTURE`.")
#else
  #if (BITBYTE_FOUNDATION_HOST_ARCHITECTURE < 0) || (BITBYTE_FOUNDATION_HOST_ARCHITECTURE > 1)
    #error ("You specified an unknown or unsupported architecture. Did you define `BITBYTE_FOUNDATION_HOST_ARCHITECTURE` correctly?")
  #endif
#endif

/// @def BITBYTE_FOUNDATION_DONT_AUTODETECT_TARGET_ARCHITECTURE
/// @brief If defined, Foundation won't attempt to detect the target
///  architecture based on pre-processor defines.
///

/// @def BITBYTE_FOUNDATION_TARGET_ARCHITECTURE
/// @brief ...
///
#ifdef BITBYTE_FOUNDATION_DONT_AUTODETECT_TARGET_ARCHITECTURE
  #ifndef BITBYTE_FOUNDATION_TARGET_ARCHITECTURE
    #error ("Please specify which architecture you are building Foundation for by defining `BITBYTE_FOUNDATION_TARGET_ARCHITECTURE`.")
  #else
    #if (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE < 0) || (BITBYTE_FOUNDATION_TARGET_ARCHITECTURE > 1)
      #error ("You specified an unknown or unsupported architecture. Did you define `BITBYTE_FOUNDATION_TARGET_ARCHITECTURE` correctly?")
    #endif
  #endif
#else
  #if (defined(_M_IX86) || defined(__i386__))
    #define BITBYTE_FOUNDATION_TARGET_ARCHITECTURE 0
  #elif (defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__))
    #define BITBYTE_FOUNDATION_TARGET_ARCHITECTURE 1
  #else
    #error ("You are building Foundation for an unknown or unsupported architecture.")
  #endif
#endif

//===----------------------------------------------------------------------===//
// Compile- and run- time utilities
//

namespace bitbyte {
namespace foundation {
namespace tier0 {

/// @namespace ::bitbyte::foundation::tier0::Architectures
/// @brief ...
///
namespace Architectures {
  enum _ {
    /// Unknown.
    Unknown = -1,
    /// Intel x86.
    x86 = 0,
    /// AMD64.
    x86_64 = 1
  };
}

///
class BITBYTE_FOUNDATION_TIER0_EXPORT Architecture {
  public: // globals:
    /// ...
    static const Architecture host() {
      static const Architecture host =
        (Architectures::_)BITBYTE_FOUNDATION_HOST_ARCHITECTURE;
      return host;
    }

    /// ...
    static const Architecture &target() {
      static const Architecture target =
        (Architectures::_)BITBYTE_FOUNDATION_TARGET_ARCHITECTURE;
      return target;
    }

  public: // constructors:
    Architecture(Architectures::_ architecture = Architectures::Unknown)
      : _(architecture) {
    }

  public: // copy-constructors:
    Architecture(const Architecture &architecture)
      : _(architecture._) {
    }

  public: // assignment operators:
    Architecture &operator=(const Architecture &architecture) {
      _ = architecture._;
      return *this;
    }

    Architecture &operator=(const Architectures::_ architecture) {
      _ = architecture;
      return *this;
    }

  public: // destructor:
    // ~Architecture() {}

  public: // conversion operators:
    operator Architectures::_() {
      return _;
    }

  public: // comparison operators:
    bool operator==(const Architectures::_ rhs) const {
      return (_ == rhs);
    }

    bool operator==(const Architecture &rhs) const {
      return (_ == rhs._);
    }

    bool operator!=(const Architectures::_ rhs) const {
      return (_ != rhs);
    }

    bool operator!=(const Architecture &rhs) const {
      return (_ != rhs._);
    }

  public: // properties
    /// ...
    template <Architectures::_ _Architecture>
    bool compatible() {
      return false;
    }

  private:
    Architectures::_ _;
};

} // tier0
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_H_
