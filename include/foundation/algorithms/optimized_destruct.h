// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALGORITHMS_OPTIMIZED_DESTRUCT_H_
#define _FOUNDATION_ALGORITHMS_OPTIMIZED_DESTRUCT_H_

// Provides an optimized destructor that takes into account triviality.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  template <typename T>
  FOUNDATION_INLINE void optimized_destruct(
    T* objs, size_t len,
    typename enable_if<is_trivially_destructable<T>::value,int>::type = 0 )
  {
    (void)objs;
    (void)len;
  }

  template <typename T>
  FOUNDATION_INLINE void optimized_destruct(
    T* objs, size_t len,
    typename enable_if<!is_trivially_destructable<T>::value,int>::type = 0 )
  {
    for (size_t idx = 0; idx < len; ++idx)
      objs[idx].~T();
  }
} // foundation

#endif // _FOUNDATION_ALGORITHMS_OPTIMIZED_DESTRUCT_H_
