//===-- bitbyte/foundation/tier2/exception.h -------------------*- C++ -*-===//
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
/// \brief Exception information and handler.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER2_EXCEPTION_H_
#define _BITBYTE_FOUNDATION_TIER2_EXCEPTION_H_

//============================================================================//

#include <stddef.h>
#include "bitbyte/foundation/tier1/stdbool.h"
#include "bitbyte/foundation/tier2/linkage.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief Exceptions.
///
typedef enum bitbyte_foundation_tier2_exception_type {
  /// Raised when an unknown error occurs.
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_UNKNOWN = 0,
  /// Raised when trying to access unaccessable memory.
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_ACCESS_VIOLATION = 1,
  /// Raised when trying to perform a misaligned read or write.
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_MISALIGNED_READ_OR_WRITE = 2,
  /// Raised when trying to execute an illegal or privileged instruction.
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_INSTRUCTION = 3,
  /// Raised when performing erroneous arithmetic.
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_ARITHMETIC = 4,
  /// Raised when failing to allocate memory.
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_OUT_OF_MEMORY = 5,
  /// Raised when the stack is exhausted.
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_STACK_OVERFLOW = 6
} bitbyte_foundation_tier2_exception_type_t;

/// \copydoc bitbyte_foundation_tier2_exception_type_t
typedef bitbyte_foundation_tier2_exception_type_t bitbyte_foundation_exception_type_t;

/// \def BITBYTE_FOUNDATION_EXCEPTION_UNKNOWN
/// \copdoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_UNKNOWN
#define BITBYTE_FOUNDATION_EXCEPTION_UNKNOWN \
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_UNKNOWN
/// \def BITBYTE_FOUNDATION_EXCEPTION_ACCESS_VIOLATION
/// \copdoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_ACCESS_VIOLATION
#define BITBYTE_FOUNDATION_EXCEPTION_ACCESS_VIOLATION \
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_ACCESS_VIOLATION
/// \def BITBYTE_FOUNDATION_EXCEPTION_MISALIGNED_READ_OR_WRITE
/// \copdoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_MISALIGNED_READ_OR_WRITE
#define BITBYTE_FOUNDATION_EXCEPTION_MISALIGNED_READ_OR_WRITE \
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_MISALIGNED_READ_OR_WRITE
/// \def BITBYTE_FOUNDATION_EXCEPTION_INVALID_INSTRUCTION
/// \copdoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_INSTRUCTION
#define BITBYTE_FOUNDATION_EXCEPTION_INVALID_INSTRUCTION \
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_INSTRUCTION
/// \def BITBYTE_FOUNDATION_EXCEPTION_INVALID_ARITHMETIC
/// \copdoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_ARITHMETIC
#define BITBYTE_FOUNDATION_EXCEPTION_INVALID_ARITHMETIC \
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_ARITHMETIC
/// \def BITBYTE_FOUNDATION_EXCEPTION_OUT_OF_MEMORY
/// \copdoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_OUT_OF_MEMORY
#define BITBYTE_FOUNDATION_EXCEPTION_OUT_OF_MEMORY \
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_OUT_OF_MEMORY
/// \def BITBYTE_FOUNDATION_EXCEPTION_STACK_OVERFLOW
/// \copdoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_STACK_OVERFLOW
#define BITBYTE_FOUNDATION_EXCEPTION_STACK_OVERFLOW \
  BITBYTE_FOUNDATION_TIER2_EXCEPTION_STACK_OVERFLOW

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_exception_type_t
  typedef bitbyte_foundation_exception_type_t foundation_exception_type_t;

  /// \def FOUNDATION_EXCEPTION_UNKNOWN
  /// \copdoc BITBYTE_FOUNDATION_EXCEPTION_UNKNOWN
  #define FOUNDATION_EXCEPTION_UNKNOWN \
    BITBYTE_FOUNDATION_EXCEPTION_UNKNOWN
  /// \def FOUNDATION_EXCEPTION_ACCESS_VIOLATION
  /// \copdoc BITBYTE_FOUNDATION_EXCEPTION_ACCESS_VIOLATION
  #define FOUNDATION_EXCEPTION_ACCESS_VIOLATION \
    BITBYTE_FOUNDATION_EXCEPTION_ACCESS_VIOLATION
  /// \def FOUNDATION_EXCEPTION_MISALIGNED_READ_OR_WRITE
  /// \copdoc BITBYTE_FOUNDATION_EXCEPTION_MISALIGNED_READ_OR_WRITE
  #define FOUNDATION_EXCEPTION_MISALIGNED_READ_OR_WRITE \
    BITBYTE_FOUNDATION_EXCEPTION_MISALIGNED_READ_OR_WRITE
  /// \def FOUNDATION_EXCEPTION_INVALID_INSTRUCTION
  /// \copdoc BITBYTE_FOUNDATION_EXCEPTION_INVALID_INSTRUCTION
  #define FOUNDATION_EXCEPTION_INVALID_INSTRUCTION \
    BITBYTE_FOUNDATION_EXCEPTION_INVALID_INSTRUCTION
  /// \def FOUNDATION_EXCEPTION_INVALID_ARITHMETIC
  /// \copdoc BITBYTE_FOUNDATION_EXCEPTION_INVALID_ARITHMETIC
  #define FOUNDATION_EXCEPTION_INVALID_ARITHMETIC \
    BITBYTE_FOUNDATION_EXCEPTION_INVALID_ARITHMETIC
  /// \def FOUNDATION_EXCEPTION_OUT_OF_MEMORY
  /// \copdoc BITBYTE_FOUNDATION_EXCEPTION_OUT_OF_MEMORY
  #define FOUNDATION_EXCEPTION_OUT_OF_MEMORY \
    BITBYTE_FOUNDATION_EXCEPTION_OUT_OF_MEMORY
  /// \def FOUNDATION_EXCEPTION_STACK_OVERFLOW
  /// \copdoc BITBYTE_FOUNDATION_EXCEPTION_STACK_OVERFLOW
  #define FOUNDATION_EXCEPTION_STACK_OVERFLOW \
    BITBYTE_FOUNDATION_EXCEPTION_STACK_OVERFLOW
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \brief Exception information.
///
typedef struct bitbyte_foundation_tier2_exception {
  bitbyte_foundation_tier2_exception_type_t type;
  // bitbyte_foundation_tier2_execution_context_t context;
  union {
    struct {
      void *address;
      bool read : 1;
      bool write : 1;
      bool execute : 1;
    } access_violation;
    struct {
    } misaligned_read_or_write;
    struct {
    } invalid_instruction;
    struct {
    } invalid_arithmetic;
    struct {
    } out_of_memory;
    struct {
    } stack_overflow;
  } info;
} bitbyte_foundation_tier2_exception_t;

/// \copydoc bitbyte_foundation_tier2_exception_t
typedef bitbyte_foundation_tier2_exception_t bitbyte_foundation_exception_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_exception_t
  typedef bitbyte_foundation_exception_t foundation_exception_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \brief Exception handler.
///
typedef void (*bitbyte_foundation_tier2_exception_handler_t)(
  const bitbyte_foundation_tier2_exception_t *exception,
  void *ctx);

/// \copydoc bitbyte_foundation_tier2_exception_handler_t
typedef bitbyte_foundation_tier2_exception_handler_t bitbyte_foundation_exception_handler_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_exception_handler_t
  typedef bitbyte_foundation_exception_handler_t foundation_exception_handler_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_exception_handler
/// \copydoc bitbyte_foundation_exception_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_exception_handler bitbyte_foundation_exception_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_exception_handler
/// \copydoc bitbyte_foundation_tier2_exception_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_exception_handler bitbyte_foundation_tier2_exception_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Retrieves the user-specified global exception handler.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
bitbyte_foundation_tier2_exception_handler(
  bitbyte_foundation_tier2_exception_handler_t *handler,
  void **ctx);

//===----------------------------------------------------------------------===//

/// \def foundation_set_exception_handler
/// \copydoc bitbyte_foundation_set_exception_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_set_exception_handler bitbyte_foundation_set_exception_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_set_exception_handler
/// \copydoc bitbyte_foundation_tier2_set_exception_handler
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_set_exception_handler bitbyte_foundation_tier2_set_exception_handler
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Sets the user-specified global exception handler.
///
extern
BITBYTE_FOUNDATION_TIER2_EXPORT
bool
bitbyte_foundation_tier2_set_exception_handler(
  bitbyte_foundation_tier2_exception_handler_t handler,
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

/// \namespace bitbyte::foundation::tier2::Exceptions
/// \copydoc ::bitbyte_foundation_tier2_exception_type_t
namespace Exceptions {
  enum __Enum__ {
    /// \copydoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_UNKNOWN
    Unknown =
      BITBYTE_FOUNDATION_TIER2_EXCEPTION_UNKNOWN,
    /// \copydoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_ACCESS_VIOLATION
    AccessViolation =
      BITBYTE_FOUNDATION_TIER2_EXCEPTION_ACCESS_VIOLATION,
    /// \copydoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_MISALIGNED_READ_OR_WRITE
    MisalignedReadOrWrite =
      BITBYTE_FOUNDATION_TIER2_EXCEPTION_MISALIGNED_READ_OR_WRITE,
    /// \copydoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_INSTRUCTION
    InvalidInstruction =
      BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_INSTRUCTION,
    /// \copydoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_ARITHMETIC
    InvalidArithmetic =
      BITBYTE_FOUNDATION_TIER2_EXCEPTION_INVALID_ARITHMETIC,
    /// \copydoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_OUT_OF_MEMORY
    OutOfMemory =
      BITBYTE_FOUNDATION_TIER2_EXCEPTION_OUT_OF_MEMORY,
    /// \copydoc BITBYTE_FOUNDATION_TIER2_EXCEPTION_STACK_OVERFLOW
    StackOverflow =
      BITBYTE_FOUNDATION_TIER2_EXCEPTION_STACK_OVERFLOW,
  };
}

//===----------------------------------------------------------------------===//

/// \copydoc ::bitbyte_foundation_tier2_exception_t
class BITBYTE_FOUNDATION_TIER2_EXPORT Exception :
  public bitbyte_foundation_tier2_exception_t
{
 public:
  // \copydoc ::bitbyte_foundation_tier2_exception_type_t
  typedef ::bitbyte_foundation_tier2_exception_type_t Type;

  /// \copydoc ::bitbyte_foundation_tier2_exception_handler_t
  typedef ::bitbyte_foundation_tier2_exception_handler_t Handler;

 public:
  /// \copydoc ::bitbyte_foundation_tier2_get_exception_handler
  static bool handler(Exception::Handler *handler, void **ctx);

  /// \copydoc ::bitbyte_foundation_tier2_set_exception_handler
  static bool set_handler(Exception::Handler handler, void *ctx);
};

//===----------------------------------------------------------------------===//

} // tier2
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER2_EXCEPTION_H_

//============================================================================//
