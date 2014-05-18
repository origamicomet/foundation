//===-- bitbyte/foundation/tier0/architecture.h -----------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mwilliams@bitbyte.ca>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Defines various architectures and detects the target architecture
/// based on pre-processor definitions.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_H_
#define _BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_H_

//============================================================================//

#include "bitbyte/foundation/tier0/linkage.h"

//============================================================================//

/// \def __FOUNDATION_ARCHITECTURE_UNKNOWN__
/// \copydoc __BITBYTE_FOUNDATION_ARCHITECTURE_UNKNOWN__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_ARCHITECTURE_UNKNOWN__ __BITBYTE_FOUNDATION_ARCHITECTURE_UNKNOWN__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_ARCHITECTURE_UNKNOWN__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_UNKNOWN__
#define __BITBYTE_FOUNDATION_ARCHITECTURE_UNKNOWN__ __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_UNKNOWN__

/// \def __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_UNKNOWN__
/// \brief Unknown or unsupported architecture.
///
#define __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_UNKNOWN__ 0

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_ARCHITECTURE_X86__
/// \copydoc __BITBYTE_FOUNDATION_ARCHITECTURE_X86__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_ARCHITECTURE_X86__ __BITBYTE_FOUNDATION_ARCHITECTURE_X86__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_ARCHITECTURE_X86__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
#define __BITBYTE_FOUNDATION_ARCHITECTURE_X86__ __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__

/// \def __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
/// \brief Intel/AMD x86.
///
#define __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__ 1

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_ARCHITECTURE_X86_64__
/// \copydoc __BITBYTE_FOUNDATION_ARCHITECTURE_X86_64__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_ARCHITECTURE_X86_64__ __BITBYTE_FOUNDATION_ARCHITECTURE_X86_64__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_ARCHITECTURE_X86_64__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
#define __BITBYTE_FOUNDATION_ARCHITECTURE_X86_64__ __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__

/// \def __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
/// \brief Intel/AMD x86-64.
///
#define __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__ 2

//===----------------------------------------------------------------------===//

/// \def FOUNDATION_ARCHITECTURE
/// \copydoc BITBYTE_FOUNDATION_ARCHITECTURE
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define FOUNDATION_ARCHITECTURE BITBYTE_FOUNDATION_ARCHITECTURE
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def BITBYTE_FOUNDATION_ARCHITECTURE
/// \copydoc BITBYTE_FOUNDATION_TIER0_ARCHITECTURE
#define BITBYTE_FOUNDATION_ARCHITECTURE BITBYTE_FOUNDATION_TIER0_ARCHITECTURE

/// \def BITBYTE_FOUNDATION_TIER0_ARCHITECTURE
/// \brief The architecture Foundation is built for.
///
#if defined(_M_IX86) || defined(__i386__)
  #define BITBYTE_FOUNDATION_TIER0_ARCHITECTURE __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__)
  #define BITBYTE_FOUNDATION_TIER0_ARCHITECTURE __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
#else
  #error ("You are building Foundation for an unknown or unsupported architecture.")
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief Runtime equivalent of BITBYTE_FOUNDATION_TIER0_ARCHITECTURE.
///
typedef enum bitbyte_foundation_tier0_architecture {
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_UNKNOWN__
  BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_UNKNOWN =
    __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_UNKNOWN__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__
  BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86 =
    __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__
  BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64 =
    __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__,
} bitbyte_foundation_tier0_architecture_t;

/// \copydoc bitbyte_foundation_tier0_architecture_t
typedef bitbyte_foundation_tier0_architecture_t bitbyte_foundation_architecture_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_architecture_t
  typedef bitbyte_foundation_architecture_t foundation_architecture_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_target_architecture
/// \copydoc foundation_tier0_target_architecture
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_target_architecture foundation_tier0_target_architecture
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def foundation_tier0_target_architecture
/// \copydoc bitbyte_foundation_tier0_target_architecture
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_tier0_target_architecture bitbyte_foundation_tier0_target_architecture
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the architecture Foundation is built for.
///
extern
BITBYTE_FOUNDATION_TIER0_EXPORT
bitbyte_foundation_tier0_architecture_t
bitbyte_foundation_tier0_target_architecture(void);

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

/// \namespace bitbyte::foundation::tier0::Architectures
/// \copydoc bitbyte_foundation_tier0_architecture_t
namespace Architectures {
enum __Enum__ {
  // \copydoc BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_UNKNOWN
  Unknown = BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_UNKNOWN,
  // \copydoc BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86
  x86 = BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86,
  // \copydoc BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64
  x86_64 = BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64,
};
}

/// \copydoc bitbyte_foundation_tier0_architecture_t
typedef Architectures::__Enum__ Architecture;

//===----------------------------------------------------------------------===//

namespace target {

/// \copydoc bitbyte_foundation_tier0_target_architecture
extern
BITBYTE_FOUNDATION_TIER0_EXPORT
Architecture
architecture(void);

} // target

//===----------------------------------------------------------------------===//

} // tier0
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_H_

//============================================================================//
