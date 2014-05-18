//===-- bitbyte/foundation/tier0/system.h -----------------------*- C++ -*-===//
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
/// \brief Defines various systems and detects the target system based on
/// pre-processor definitions.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER0_SYSTEM_H_
#define _BITBYTE_FOUNDATION_TIER0_SYSTEM_H_

//============================================================================//

#include "bitbyte/foundation/tier0/linkage.h"

//============================================================================//

/// \def __FOUNDATION_SYSTEM_UNKNOWN__
/// \copydoc __BITBYTE_FOUNDATION_SYSTEM_UNKNOWN__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_SYSTEM_UNKNOWN__ __BITBYTE_FOUNDATION_SYSTEM_UNKNOWN__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_SYSTEM_UNKNOWN__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_UNKNOWN__
#define __BITBYTE_FOUNDATION_SYSTEM_UNKNOWN__ __BITBYTE_FOUNDATION_TIER0_SYSTEM_UNKNOWN__

/// \def __BITBYTE_FOUNDATION_TIER0_SYSTEM_UNKNOWN__
/// \brief Unknown or unsupported system.
///
#define __BITBYTE_FOUNDATION_TIER0_SYSTEM_UNKNOWN__ 0

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_SYSTEM_WINDOWS__
/// \copydoc __BITBYTE_FOUNDATION_SYSTEM_WINDOWS__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_SYSTEM_WINDOWS__ __BITBYTE_FOUNDATION_SYSTEM_WINDOWS__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_SYSTEM_WINDOWS__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
#define __BITBYTE_FOUNDATION_SYSTEM_WINDOWS__ __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__

/// \def __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
/// \brief Microsoft Windows.
///
#define __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__ 1

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_SYSTEM_MAC_OS_X__
/// \copydoc __BITBYTE_FOUNDATION_SYSTEM_MAC_OS_X__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_SYSTEM_MAC_OS_X__ __BITBYTE_FOUNDATION_SYSTEM_MAC_OS_X__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_SYSTEM_MAC_OS_X__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#define __BITBYTE_FOUNDATION_SYSTEM_MAC_OS_X__ __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__

/// \def __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
/// \brief Mac OS X.
///
#define __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__ 2

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_SYSTEM_LINUX__
/// \copydoc __BITBYTE_FOUNDATION_SYSTEM_LINUX__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_SYSTEM_LINUX__ __BITBYTE_FOUNDATION_SYSTEM_LINUX__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_SYSTEM_LINUX__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#define __BITBYTE_FOUNDATION_SYSTEM_LINUX__ __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__

/// \def __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
/// \brief Linux.
///
#define __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__ 3

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_SYSTEM_ANDROID__
/// \copydoc __BITBYTE_FOUNDATION_SYSTEM_ANDROID__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_SYSTEM_ANDROID__ __BITBYTE_FOUNDATION_SYSTEM_ANDROID__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_SYSTEM_ANDROID__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__
#define __BITBYTE_FOUNDATION_SYSTEM_ANDROID__ __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__

/// \def __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__
/// \brief Android.
///
#define __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__ 4

//===----------------------------------------------------------------------===//

/// \def __FOUNDATION_SYSTEM_IOS__
/// \copydoc __BITBYTE_FOUNDATION_SYSTEM_IOS__
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define __FOUNDATION_SYSTEM_IOS__ __BITBYTE_FOUNDATION_SYSTEM_IOS__
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def __BITBYTE_FOUNDATION_SYSTEM_IOS__
/// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__
#define __BITBYTE_FOUNDATION_SYSTEM_IOS__ __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__

/// \def __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__
/// \brief iOS.
///
#define __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__ 5

//===----------------------------------------------------------------------===//

/// \def FOUNDATION_SYSTEM
/// \copydoc BITBYTE_FOUNDATION_SYSTEM
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define FOUNDATION_SYSTEM BITBYTE_FOUNDATION_SYSTEM
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def BITBYTE_FOUNDATION_SYSTEM
/// \copydoc BITBYTE_FOUNDATION_TIER0_SYSTEM
#define BITBYTE_FOUNDATION_SYSTEM BITBYTE_FOUNDATION_TIER0_SYSTEM

/// \def BITBYTE_FOUNDATION_TIER0_SYSTEM
/// \brief The system Foundation is built for.
///
#if (defined(_WIN32) || defined(_WIN64))
  #define BITBYTE_FOUNDATION_TIER0_SYSTEM __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
#elif defined(__APPLE__)
  #include <TargetConditionals.h>
  #if defined(TARGET_OS_IPHONE)
    #define BITBYTE_FOUNDATION_TIER0_SYSTEM __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__
  #else
    #define BITBYTE_FOUNDATION_TIER0_SYSTEM __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  #endif
#elif defined(__linux__)
  #if defined(ANDROID)
    #define BITBYTE_FOUNDATION_TIER0_SYSTEM __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__
  #else
    #define BITBYTE_FOUNDATION_TIER0_SYSTEM __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  #endif
#else
  #error ("You are building Foundation for an unknown or unsupported system.")
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief Runtime equivalent of BITBYTE_FOUNDATION_TIER0_SYSTEM.
///
typedef enum bitbyte_foundation_tier0_system {
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_UNKNOWN__
  BITBYTE_FOUNDATION_TIER0_SYSTEM_UNKNOWN =
    __BITBYTE_FOUNDATION_TIER0_SYSTEM_UNKNOWN__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS =
    __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
  BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X =
    __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
  BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX =
    __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__
  BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID =
    __BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID__,
  /// \copydoc __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__
  BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS =
    __BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS__
} bitbyte_foundation_tier0_system_t;

/// \copydoc bitbyte_foundation_tier0_system_t
typedef bitbyte_foundation_tier0_system_t bitbyte_foundation_system_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_system_t
  typedef bitbyte_foundation_system_t foundation_system_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_target_system
/// \copydoc foundation_tier0_target_system
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_target_system foundation_tier0_target_system
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def foundation_tier0_target_system
/// \copydoc bitbyte_foundation_tier0_target_system
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_tier0_target_system bitbyte_foundation_tier0_target_system
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the system Foundation is built for.
///
extern
BITBYTE_FOUNDATION_TIER0_EXPORT
bitbyte_foundation_tier0_system_t
bitbyte_foundation_tier0_target_system(void);

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

/// \namespace bitbyte::foundation::tier0::Systems
/// \copydoc bitbyte_foundation_tier0_system_t
namespace Systems {
enum __Enum__ {
  // \copydoc BITBYTE_FOUNDATION_TIER0_SYSTEM_UNKNOWN
  Unknown = BITBYTE_FOUNDATION_TIER0_SYSTEM_UNKNOWN,
  // \copydoc BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS
  Windows = BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS,
  // \copydoc BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X
  MacOSX = BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X,
  // \copydoc BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX
  Linux = BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX,
  // \copydoc BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID
  Android = BITBYTE_FOUNDATION_TIER0_SYSTEM_ANDROID,
  // \copydoc BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS
  iOS = BITBYTE_FOUNDATION_TIER0_SYSTEM_IOS,
};
}

/// \copydoc bitbyte_foundation_tier0_system_t
typedef Systems::__Enum__ System;

//===----------------------------------------------------------------------===//

namespace target {

/// \copydoc bitbyte_foundation_tier0_target_system
extern
BITBYTE_FOUNDATION_TIER0_EXPORT
System
system(void);

} // target

//===----------------------------------------------------------------------===//

} // tier0
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER0_SYSTEM_H_

//============================================================================//
