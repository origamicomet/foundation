//===-- bitbyte/foundation/tier0/compiler.h ---------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Defines various compilers and detects the host compiler based on
/// pre-processor definitions.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER0_COMPILER_H_
#define _BITBYTE_FOUNDATION_TIER0_COMPILER_H_

//============================================================================//

#include "bitbyte/foundation/tier0/linkage.h"

//============================================================================//

/// \def __FOUNDATION_COMPILER_UNKNOWN__
/// \copydoc __BITBYTE_FOUNDATION_COMPILER_UNKNOWN__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_COMPILER_UNKNOWN__ __BITBYTE_FOUNDATION_COMPILER_UNKNOWN__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_COMPILER_UNKNOWN__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN__
#define __BITBYTE_FOUNDATION_COMPILER_UNKNOWN__ __BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN__

/// \def __BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN__
/// \brief Unknown or unsupported compiler.
///
#define __BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN__ 0

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_COMPILER_MSVC__
/// \copydoc __BITBYTE_FOUNDATION_COMPILER_MSVC__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_COMPILER_MSVC__ __BITBYTE_FOUNDATION_COMPILER_MSVC__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_COMPILER_MSVC__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
#define __BITBYTE_FOUNDATION_COMPILER_MSVC__ __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__

/// \def __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
/// \brief Microsoft Visual C/C++ Compiler.
///
#define __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__ 1

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_COMPILER_GCC__
/// \copydoc __BITBYTE_FOUNDATION_COMPILER_GCC__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_COMPILER_GCC__ __BITBYTE_FOUNDATION_COMPILER_GCC__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_COMPILER_GCC__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__
#define __BITBYTE_FOUNDATION_COMPILER_GCC__ __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__

/// \def __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__
/// \brief GNU Compiler Collection.
///
#define __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__ 2

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_COMPILER_CLANG__
/// \copydoc __BITBYTE_FOUNDATION_COMPILER_CLANG__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_COMPILER_CLANG__ __BITBYTE_FOUNDATION_COMPILER_CLANG__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_COMPILER_CLANG__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__
#define __BITBYTE_FOUNDATION_COMPILER_CLANG__ __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__

/// \def __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__
/// \brief LLVM/Clang.
///
#define __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__ 3

//===----------------------------------------------------------------------===//

/// \def FOUNDATION_COMPILER
/// \copydoc BITBYTE_FOUNDATION_COMPILER
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define FOUNDATION_COMPILER BITBYTE_FOUNDATION_COMPILER
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def BITBYTE_FOUNDATION_COMPILER
/// \copydoc BITBYTE_FOUNDATION_TIER0_COMPILER
#define BITBYTE_FOUNDATION_COMPILER BITBYTE_FOUNDATION_TIER0_COMPILER

/// \def BITBYTE_FOUNDATION_TIER0_COMPILER
/// \brief The compiler used to build Foundation.
///
#if defined(_MSC_VER)
  #define BITBYTE_FOUNDATION_TIER0_COMPILER __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
#elif defined(__GNUC__)
  #define BITBYTE_FOUNDATION_TIER0_COMPILER __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__
#elif defined(__clang__)
  #define BITBYTE_FOUNDATION_TIER0_COMPILER __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__
#else
  #error ("You are building Foundation with an unknown or unsupported compiler.")
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief Runtime equivalent of BITBYTE_FOUNDATION_TIER0_COMPILER.
///
typedef enum bitbyte_foundation_tier0_compiler {
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN__
  BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN =
    __BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC =
    __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__
  BITBYTE_FOUNDATION_TIER0_COMPILER_GCC =
    __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__
  BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG =
    __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__
} bitbyte_foundation_tier0_compiler_t;

/// \copydoc bitbyte_foundation_tier0_compiler_t
typedef bitbyte_foundation_tier0_compiler_t bitbyte_foundation_compiler_t;

/// \def BITBYTE_FOUNDATION_COMPILER_UNKNOWN
/// \copydoc BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN
#define BITBYTE_FOUNDATION_COMPILER_UNKNOWN \
  BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN
/// \def BITBYTE_FOUNDATION_COMPILER_MSVC
/// \copydoc BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC
#define BITBYTE_FOUNDATION_COMPILER_MSVC \
  BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC
/// \def BITBYTE_FOUNDATION_COMPILER_GCC
/// \copydoc BITBYTE_FOUNDATION_TIER0_COMPILER_GCC
#define BITBYTE_FOUNDATION_COMPILER_GCC \
  BITBYTE_FOUNDATION_TIER0_COMPILER_GCC
/// \def BITBYTE_FOUNDATION_COMPILER_CLANG
/// \copydoc BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG
#define BITBYTE_FOUNDATION_COMPILER_CLANG \
  BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_compiler_t
  typedef bitbyte_foundation_compiler_t foundation_compiler_t;

  /// \def FOUNDATION_COMPILER_UNKNOWN
  /// \copydoc BITBYTE_FOUNDATION_COMPILER_UNKNOWN
  #define FOUNDATION_COMPILER_UNKNOWN \
    BITBYTE_FOUNDATION_COMPILER_UNKNOWN
  /// \def FOUNDATION_COMPILER_MSVC
  /// \copydoc BITBYTE_FOUNDATION_COMPILER_MSVC
  #define FOUNDATION_COMPILER_MSVC \
    BITBYTE_FOUNDATION_COMPILER_MSVC
  /// \def FOUNDATION_COMPILER_GCC
  /// \copydoc BITBYTE_FOUNDATION_COMPILER_GCC
  #define FOUNDATION_COMPILER_GCC \
    BITBYTE_FOUNDATION_COMPILER_GCC
  /// \def FOUNDATION_COMPILER_CLANG
  /// \copydoc BITBYTE_FOUNDATION_COMPILER_CLANG
  #define FOUNDATION_COMPILER_CLANG \
    BITBYTE_FOUNDATION_COMPILER_CLANG
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_host_compiler
/// \copydoc foundation_tier0_host_compiler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_host_compiler foundation_tier0_host_compiler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def foundation_tier0_host_compiler
/// \copydoc bitbyte_foundation_tier0_host_compiler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_tier0_host_compiler bitbyte_foundation_tier0_host_compiler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the compiler used to build Foundation.
///
extern
BITBYTE_FOUNDATION_TIER0_EXPORT
bitbyte_foundation_tier0_compiler_t
bitbyte_foundation_tier0_host_compiler(void);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier0 {

//===----------------------------------------------------------------------===//

/// \namespace bitbyte::foundation::tier0::Compilers
/// \copydoc bitbyte_foundation_tier0_compiler_t
namespace Compilers {
enum __Enum__ {
  /// \copydoc BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN
  Unknown = BITBYTE_FOUNDATION_TIER0_COMPILER_UNKNOWN,
  /// \copydoc BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC
  MSVC = BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC,
  /// \copydoc BITBYTE_FOUNDATION_TIER0_COMPILER_GCC
  GCC = BITBYTE_FOUNDATION_TIER0_COMPILER_GCC,
  /// \copydoc BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG
  Clang = BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG
};
}

/// \copydoc bitbyte_foundation_tier0_compiler_t
typedef Compilers::__Enum__ Compiler;

//===----------------------------------------------------------------------===//

namespace host {

/// \copydoc bitbyte_foundation_tier0_host_compiler
extern
BITBYTE_FOUNDATION_TIER0_EXPORT
Compiler
compiler(void);

} // host

//===----------------------------------------------------------------------===//

} // tier0
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER0_COMPILER_H_

//============================================================================//
