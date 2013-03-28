// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_MATH_H_
#define _FOUNDATION_MATH_H_

// Provides various optimized math utilities.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  // Determines if an integer is a power of two.
  FOUNDATION_INLINE bool is_power_of_two( unsigned x ) {
    return (((x) & (x - 1)) == 0);
  }

  // Returns the log base two of a power of two.
  FOUNDATION_INLINE uint32_t log2( uint32_t x ) {
    return __builtin_clz(x);
  }
} // foundation

#endif // _FOUNDATION_MATH_H_