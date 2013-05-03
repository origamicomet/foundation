// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALGORITHMS_SORT_H_
#define _FOUNDATION_ALGORITHMS_SORT_H_

// Provides an in-place unstable O(n log n) sorting algorithm.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  template <typename T>
  FOUNDATION_INLINE int __sort_comparator(
    const void* a_,
    const void* b_ )
  {
    const T& a = *((const T*)a_);
    const T& b = *((const T*)b_);
    if (a > b)
      return 1;
    if (a < b)
      return - 1;
    return 0;
  }

  template <typename T>
  FOUNDATION_INLINE void sort(
    T* array,
    size_t array_len )
  {
    qsort((const void*)array, array_len, sizeof(T), &__sort_comparator<T>);
  }
} // foundation

#endif // _FOUNDATION_ALGORITHMS_SORT_H_
