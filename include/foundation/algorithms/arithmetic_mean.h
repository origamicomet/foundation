// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALGORITHMS_ARITHMETIC_MEAN_H_
#define _FOUNDATION_ALGORITHMS_ARITHMETIC_MEAN_H_

// Provides an O(n) arithmetic mean calculation.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  template <typename T>
  FOUNDATION_INLINE T arithmetic_mean(
    const T* array,
    size_t array_len )
  {
    if (array_len == 0)
      return T(0);
    T sum = T(0);
    for (size_t i = 0; i < array_len; ++i)
      sum += array[i];
    return (sum / T(array_len));
  }
} // foundation

#endif // _FOUNDATION_ALGORITHMS_ARITHMETIC_MEAN_H_
