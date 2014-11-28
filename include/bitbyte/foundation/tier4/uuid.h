//===-- bitbyte/foundation/tier4/uuid.h -------------------------*- C++ -*-===//
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
/// \brief Provides mechanisims to generate and manipulate UUIDs.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER4_UUID_H_
#define _BITBYTE_FOUNDATION_TIER4_UUID_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdint.h"
#include "bitbyte/foundation/tier4/linkage.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief A Universally Unique Identifier.
///
typedef struct bitbyte_foundation_tier4_uuid {
  uint8_t _raw[16];
} bitbyte_foundation_tier4_uuid_t;

/// \copydoc bitbyte_foundation_tier4_uuid_t
typedef bitbyte_foundation_tier4_uuid_t bitbyte_foundation_uuid_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_uuid_t
  typedef bitbyte_foundation_uuid_t foundation_uuid_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_uuid_generate
/// \copydoc bitbyte_foundation_uuid_generate
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_uuid_generate bitbyte_foundation_uuid_generate
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_uuid_generate
/// \copydoc bitbyte_foundation_tier4_uuid_generate
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_uuid_generate bitbyte_foundation_tier4_uuid_generate
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Generates a UUID.
///
extern
BITBYTE_FOUNDATION_TIER4_EXPORT
void
bitbyte_foundation_tier4_uuid_generate(
  bitbyte_foundation_tier4_uuid_t *uuid);

//===----------------------------------------------------------------------===//

/// \def foundation_uuid_to_s
/// \copydoc bitbyte_foundation_uuid_to_s
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_uuid_to_s bitbyte_foundation_uuid_to_s
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_uuid_to_s
/// \copydoc bitbyte_foundation_tier4_uuid_to_s
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_uuid_to_s bitbyte_foundation_tier4_uuid_to_s
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the number of seconds elapsed since the last reset.
///
extern
BITBYTE_FOUNDATION_TIER4_EXPORT
void
bitbyte_foundation_tier4_uuid_to_s(
  const bitbyte_foundation_uuid_t *uuid,
  char buf[21]);

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier4 {

//===----------------------------------------------------------------------===//

/// \copydoc ::bitbyte_foundation_tier4_uuid_t
class BITBYTE_FOUNDATION_TIER4_EXPORT UUID :
  public bitbyte_foundation_tier4_uuid_t
{
 public:
  /// \copydoc ::bitbyte_foundation_tier4_uuid_generate
  static void generate(UUID *uuid);
 public:
  /// \copydoc ::bitbyte_foundation_tier4_uuid_to_s
  void to_s(char buf[21]);
};

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier4

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER4_UUID_H_

//============================================================================//
