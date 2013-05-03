// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/digest/murmur_hash.h>

namespace foundation {
  uint32_t murmur_hash(
    const void* key,
    size_t key_len,
    uint32_t seed )
  {
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    uint32_t h = seed ^ key_len;
    const unsigned char* data = (const unsigned char*)key;

    while (key_len >= 4) {
      uint32_t k = *(uint32_t*)data;
      k *= m;
      k ^= k >> r;
      k *= m;
      h *= m;
      h ^= k;
      data += 4;
      key_len -= 4; }

    switch (key_len) {
      case 3: h ^= data[2] << 16;
      case 2: h ^= data[1] << 8;
      case 1: h ^= data[0];
          h *= m; };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
  }

  uint64_t murmur_hash_64(
    const void* key,
    size_t key_len,
    uint64_t seed )
  {
    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    const int r = 47;
    uint64_t h = seed ^ (key_len * m);
    const uint64_t* data = (const uint64_t*)key;
    const uint64_t* end = data + (key_len/8);

    while (data != end) {
      uint64_t k = *data++;
      k *= m; 
      k ^= k >> r; 
      k *= m; 
      h ^= k;
      h *= m; }

    const unsigned char* data2 = (const unsigned char*)data;
    switch (key_len & 7) {
      case 7: h ^= uint64_t(data2[6]) << 48;
      case 6: h ^= uint64_t(data2[5]) << 40;
      case 5: h ^= uint64_t(data2[4]) << 32;
      case 4: h ^= uint64_t(data2[3]) << 24;
      case 3: h ^= uint64_t(data2[2]) << 16;
      case 2: h ^= uint64_t(data2[1]) << 8;
      case 1: h ^= uint64_t(data2[0]);
              h *= m; };
   
    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
  }
} // foundation
