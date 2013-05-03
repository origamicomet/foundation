// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DIGEST_CRC_H_
#define _FOUNDATION_DIGEST_CRC_H_

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  extern FOUNDATION_EXPORT uint32_t crc32(
    uint32_t crc,
    const void* buffer,
    size_t buffer_len );

  FOUNDATION_INLINE uint32_t crc32(
    const void* buffer,
    size_t buffer_len )
  { return crc32(0, buffer, buffer_len); }
} // foundation

#endif // _FOUNDATION_DIGEST_CRC_H_
