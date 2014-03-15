//=== bitbyte/foundation/tier0/compiler.h ====================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier0/compiler.h
/// @brief Defines various compilers and convenient pre-processor values,
///  and also provides compile- and run- time utilities related to compilers.
///

#ifndef _BITBYTE_FOUNDATION_TIER0_COMPILER_H_
#define _BITBYTE_FOUNDATION_TIER0_COMPILER_H_

#include <bitbyte/foundation/tier0/export.h>

//===----------------------------------------------------------------------===//
// Pre-processor defines
//

/// @def BITBYTE_FOUNDATION_DONT_AUTODETECT_COMPILER
/// @brief If defined, Foundation won't attempt to detect the current compiler
///  based on pre-processor defines.
///

/// @def BITBYTE_FOUNDATION_COMPILER
/// @brief ...
///
#ifdef BITBYTE_FOUNDATION_DONT_AUTODETECT_COMPILER
  #ifndef BITBYTE_FOUNDATION_COMPILER
    #error ("Please specify which compiler you are building Foundation with by defining `BITBYTE_FOUNDATION_COMPILER`.")
  #else
    #if (BITBYTE_FOUNDATION_COMPILER < 0) || (BITBYTE_FOUNDATION_COMPILER > 2)
      #error ("You specified an unknown or unsupported compiler. Did you define `BITBYTE_FOUNDATION_COMPILER` correctly?")
    #endif
  #endif
#else
  #if defined(_MSC_VER)
    #define BITBYTE_FOUNDATION_COMPILER_MSVC 0
    #define BITBYTE_FOUNDATION_COMPILER 0
  #elif defined(__GNUC__)
    #define BITBYTE_FOUNDATION_COMPILER_GCC 1
    #define BITBYTE_FOUNDATION_COMPILER 1
  #elif defined(__clang__)
    #define BITBYTE_FOUNDATION_COMPILER_CLANG 2
    #define BITBYTE_FOUNDATION_COMPILER 2
  #else
    #error ("You are building Foundation with an unknown or unsupported compiler.")
  #endif
#endif

//===----------------------------------------------------------------------===//
// Compile- and run- time utilities
//

namespace bitbyte {
namespace foundation {
namespace tier0 {

/// @namespace ::bitbyte::foundation::tier0::Compilers
/// @brief ...
///
namespace Compilers {
  enum _ {
    /// Unknown.
    Unknown = -1,
    /// Microsoft Visual C/C++.
    MSVC = 0,
    /// GNU Compiler Collection.
    GCC = 1,
    /// LLVM/Clang.
    Clang = 2
  };
}

///
class BITBYTE_FOUNDATION_TIER0_EXPORT Compiler {
  public: // constructors:
    Compiler(Compilers::_ compiler = Compilers::Unknown)
      : _(compiler) {
    }

  public: // copy-constructors:
    Compiler(const Compiler &compiler)
      : _(compiler._) {
    }

  public: // assignment operators:
    Compiler &operator=(const Compiler &compiler) {
      _ = compiler._;
      return *this;
    }

    Compiler &operator=(const Compilers::_ compiler) {
      _ = compiler;
      return *this;
    }

  public: // destructor:
    // ~Compiler() {}

  public: // conversion operators:
    operator Compilers::_() {
      return _;
    }

  public: // comparison operators:
    bool operator==(const Compilers::_ rhs) const {
      return (_ == rhs);
    }

    bool operator==(const Compiler &rhs) const {
      return (_ == rhs._);
    }

    bool operator!=(const Compilers::_ rhs) const {
      return (_ != rhs);
    }

    bool operator!=(const Compiler &rhs) const {
      return (_ != rhs._);
    }

  private:
    Compilers::_ _;
};

/// ...
extern BITBYTE_FOUNDATION_TIER0_EXPORT const Compiler compiler();

} // tier0
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER0_COMPILER_H_
