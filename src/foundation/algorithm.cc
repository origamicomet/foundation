// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/algorithm.h>

namespace foundation {
  uint32_t round_to_prime( uint32_t n )
  {
    static const uint32_t primes[] =  {
      8 + 3,
      16 + 3,
      32 + 5,
      64 + 3,
      128 + 3,
      256 + 27,
      512 + 9,
      1024 + 9,
      2048 + 5,
      4096 + 3,
      8192 + 27,
      16384 + 43,
      32768 + 3,
      65536 + 45,
      131072 + 29,
      262144 + 3,
      524288 + 21,
      1048576 + 7,
      2097152 + 17,
      4194304 + 15,
      8388608 + 9,
      16777216 + 43,
      33554432 + 35,
      67108864 + 15,
      134217728 + 29,
      268435456 + 3,
      536870912 + 11,
      1073741824 + 85,
    };

    static const uint32_t num_primes = sizeof(primes) / sizeof(uint32_t);

    for (uint32_t i = 0, new_n = 8; i < num_primes; i++, new_n <<= 1)
      if (new_n > n)
        return primes[i];
      
    return 0xFFFFFFFFu;
  }
} // foundation