// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DIGEST_MURMUR_HASH_H_
#define _FOUNDATION_DIGEST_MURMUR_HASH_H_

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  extern FOUNDATION_EXPORT uint32_t murmur_hash(
    const void* key,
    size_t key_len,
    uint32_t seed );

  extern FOUNDATION_EXPORT uint64_t murmur_hash_64(
    const void* key,
    size_t key_len,
    uint64_t seed );
} // foundation

#endif // _FOUNDATION_DIGEST_MURMUR_HASH_H_
