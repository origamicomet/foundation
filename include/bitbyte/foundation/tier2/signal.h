//===-- bitbyte/foundation/tier2/signal.h -----------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@bitbyte.ca>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Signal information and handler.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER2_SIGNAL_H_
#define _BITBYTE_FOUNDATION_TIER2_SIGNAL_H_

//============================================================================//

#include <stddef.h>
#include "bitbyte/foundation/tier1/stdbool.h"
#include "bitbyte/foundation/tier2/linkage.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief Signal.
///
typedef enum bitbyte_foundation_tier2_signal {
  /// Raised when graceful termination is requested.
  BITBYTE_FOUNDATION_TIER2_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED = 1,
  /// Raised when abnormal termination is requested.
  BITBYTE_FOUNDATION_TIER2_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED = 2,
  /// Raised when graceful termination is requested by the user.
  BITBYTE_FOUNDATION_TIER2_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER = 3,
} bitbyte_foundation_tier2_signal_t;

/// \copydoc bitbyte_foundation_tier2_signal_t
typedef bitbyte_foundation_tier2_signal_t bitbyte_foundation_signal_t;

/// \def BITBYTE_FOUNDATION_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED
/// \copydoc BITBYTE_FOUNDATION_TIER2_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED
#define BITBYTE_FOUNDATION_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED \
  BITBYTE_FOUNDATION_TIER2_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED
/// \def BITBYTE_FOUNDATION_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED
/// \copydoc BITBYTE_FOUNDATION_TIER2_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED
#define BITBYTE_FOUNDATION_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED \
  BITBYTE_FOUNDATION_TIER2_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED
/// \def BITBYTE_FOUNDATION_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER
/// \copydoc BITBYTE_FOUNDATION_TIER2_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER
#define BITBYTE_FOUNDATION_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER \
  BITBYTE_FOUNDATION_TIER2_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_signal_t
  typedef bitbyte_foundation_signal_t foundation_signal_t;

  /// \def BITBYTE_FOUNDATION_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED
  /// \copydoc BITBYTE_FOUNDATION_TIER2_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED
  #define FOUNDATION_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED \
    BITBYTE_FOUNDATION_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED
  /// \def BITBYTE_FOUNDATION_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED
  /// \copydoc BITBYTE_FOUNDATION_TIER2_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED
  #define FOUNDATION_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED \
    BITBYTE_FOUNDATION_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED
  /// \def BITBYTE_FOUNDATION_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER
  /// \copydoc BITBYTE_FOUNDATION_TIER2_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER
  #define FOUNDATION_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER \
    BITBYTE_FOUNDATION_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_signal_desc
/// \copydoc bitbyte_foundation_signal_desc
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_signal_desc bitbyte_foundation_signal_desc
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_signal_desc
/// \copydoc bitbyte_foundation_tier2_signal_desc
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_signal_desc bitbyte_foundation_tier2_signal_desc
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns a user-presentable string that describes `signal`.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
const char *
bitbyte_foundation_tier2_signal_desc(
  bitbyte_foundation_tier2_signal_t signal);

//===----------------------------------------------------------------------===//

/// \brief Signals handler.
///
typedef void (*bitbyte_foundation_tier2_signal_handler_t)(
  bitbyte_foundation_tier2_signal_t signal,
  void *ctx);

/// \copydoc bitbyte_foundation_tier2_signal_handler_t
typedef bitbyte_foundation_tier2_signal_handler_t bitbyte_foundation_signal_handler_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_signal_handler_t
  typedef bitbyte_foundation_signal_handler_t foundation_signal_handler_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_signal_handler
/// \copydoc bitbyte_foundation_signal_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_signal_handler bitbyte_foundation_signal_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_signal_handler
/// \copydoc bitbyte_foundation_tier2_signal_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_signal_handler bitbyte_foundation_tier2_signal_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Retrieves the user-specified global signal handler.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
bitbyte_foundation_tier2_signal_handler(
  bitbyte_foundation_tier2_signal_handler_t *handler,
  void **ctx);

//===----------------------------------------------------------------------===//

/// \def foundation_set_signal_handler
/// \copydoc bitbyte_foundation_set_signal_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_set_signal_handler bitbyte_foundation_set_signal_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_set_signal_handler
/// \copydoc bitbyte_foundation_tier2_set_signal_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_set_signal_handler bitbyte_foundation_tier2_set_signal_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Sets the user-specified global signal handler.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
bitbyte_foundation_tier2_set_signal_handler(
  bitbyte_foundation_tier2_signal_handler_t handler,
  void *ctx);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier2 {

//===----------------------------------------------------------------------===//

/// \namespace bitbyte::foundation::tier2::Signals
/// \copydoc ::bitbyte_foundation_tier2_signal_t
namespace Signals {
  enum __Enum__ {
    /// \copydoc BITBYTE_FOUNDATION_TIER2_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED
    GracefulProgramTerminationRequested =
      BITBYTE_FOUNDATION_TIER2_SIGNAL_GRACEFUL_PROGRAM_TERMINATION_REQUESTED,
    /// \copydoc BITBYTE_FOUNDATION_TIER2_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED
    AbnormalProgramTerminationRequested =
      BITBYTE_FOUNDATION_TIER2_SIGNAL_ABNORMAL_PROGRAM_TERMINATION_REQUESTED,
    /// \copydoc BITBYTE_FOUNDATION_TIER2_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER
    ProgramTerminationRequestedByUser =
      BITBYTE_FOUNDATION_TIER2_SIGNAL_PROGRAM_TERMINATION_REQUESTED_BY_USER,
  };
}

/// \copydoc ::bitbyte_foundation_tier2_signal_t
class BITBYTE_FOUNDATION_TIER2_EXPORT Signal {
 //===---------------------------------------------------------------------===//

 public:
  /// \copydoc ::bitbyte_foundation_tier2_signal_handler_t
  typedef ::bitbyte_foundation_tier2_signal_handler_t Handler;

 public:
  /// \copydoc ::bitbyte_foundation_tier2_get_signal_handler
  static bool handler(Signal::Handler *handler, void **ctx);

  /// \copydoc ::bitbyte_foundation_tier2_set_signal_handler
  static bool set_handler(Signal::Handler handler, void *ctx);

 public:
  /// \copydoc ::bitbyte_foundation_tier2_signal_desc
  const char *desc(void) const;

 //===---------------------------------------------------------------------===//

 private:
  typedef Signals::__Enum__ __Enum__;

 public:
  Signal(__Enum__ E) {
    this->E = E;
  }

  Signal(const Signal &signal) {
    this->E = signal.E;
  }

  Signal &operator=(const __Enum__ E) {
    this->E = E;
    return *this;
  }

  Signal &operator=(const Signal &signal) {
    this->E = signal.E;
    return *this;
  }

 public:
  operator __Enum__(void) const {
    return this->E;
  }

 private:
  __Enum__ E;

 //===---------------------------------------------------------------------===//
};

//===----------------------------------------------------------------------===//

} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER2_SIGNAL_H_

//============================================================================//
