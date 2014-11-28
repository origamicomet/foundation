//===-- bitbyte/foundation/tier4/uuid.c ------------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier4/uuid.h"

//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier0/system.h"
#include "bitbyte/foundation/tier2/assert.h"

//===----------------------------------------------------------------------===//

#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  #include <objbase.h>
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier4_uuid_generate(
  bitbyte_foundation_tier4_uuid_t *uuid)
{
  bitbyte_foundation_tier2_assert(uuid != NULL);
#if BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_WINDOWS__
  GUID guid;
  CoCreateGuid(&guid);

  // TODO(mwilliams): Take native endianness into account.
  uuid->_raw[0]  = (guid.Data1 >> 24) & 0xff;
  uuid->_raw[1]  = (guid.Data1 >> 16) & 0xff;
  uuid->_raw[2]  = (guid.Data1 >> 8) & 0xff;
  uuid->_raw[3]  = (guid.Data1 >> 0) & 0xff;
  uuid->_raw[4]  = (guid.Data2 >> 8) & 0xff;
  uuid->_raw[5]  = (guid.Data2 >> 0) & 0xff;
  uuid->_raw[6]  = (guid.Data3 >> 8) & 0xff;
  uuid->_raw[7]  = (guid.Data3 >> 0) & 0xff;
  uuid->_raw[8]  = guid.Data4[0];
  uuid->_raw[9]  = guid.Data4[1];
  uuid->_raw[10] = guid.Data4[2];
  uuid->_raw[11] = guid.Data4[3];
  uuid->_raw[12] = guid.Data4[4];
  uuid->_raw[13] = guid.Data4[5];
  uuid->_raw[14] = guid.Data4[6];
  uuid->_raw[15] = guid.Data4[7];
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_MAC_OS_X__
#elif BITBYTE_FOUNDATION_TIER0_SYSTEM == __BITBYTE_FOUNDATION_TIER0_SYSTEM_LINUX__
#endif
}

//===----------------------------------------------------------------------===//

void
bitbyte_foundation_tier4_uuid_to_s(
  const bitbyte_foundation_uuid_t *uuid,
  char buf[37])
{
  bitbyte_foundation_tier2_assert(uuid != NULL);
  // HACK: This is really nasty. There's probably a better way.
  sprintf(&buf[0],
          "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
          uuid->_raw[0], uuid->_raw[1], uuid->_raw[2], uuid->_raw[3],
          uuid->_raw[4], uuid->_raw[5], uuid->_raw[6], uuid->_raw[7],
          uuid->_raw[8], uuid->_raw[9], uuid->_raw[10], uuid->_raw[11],
          uuid->_raw[12], uuid->_raw[13], uuid->_raw[14], uuid->_raw[15]);
}

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

void UUID::generate(UUID *uuid)
{
  ::bitbyte_foundation_tier4_uuid_generate((bitbyte_foundation_tier4_uuid_t *)uuid);
}

//===----------------------------------------------------------------------===//

void UUID::to_s(char buf[37])
{
  ::bitbyte_foundation_tier4_uuid_to_s((const bitbyte_foundation_tier4_uuid_t *)this, buf);
}

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier4

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
