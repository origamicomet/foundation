// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALGORITHMS_COPY_H_
#define _FOUNDATION_ALGORITHMS_COPY_H_

// Provides an optimized copy that takes into account triviality.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  template <typename T>
  FOUNDATION_INLINE void optimized_copy(
    T* dest, const T* src, size_t len,
    typename enable_if<is_trivially_copyable<T>::value,int>::type = 0 )
  {
    copy((void*)dest, (const void*)src, sizeof(T) * len);
  }

  template <typename T>
  FOUNDATION_INLINE void optimized_copy(
    T* dest, const T* src, size_t len,
    typename enable_if<!is_trivially_copyable<T>::value,int>::type = 0 )
  {
    for (size_t idx = 0; idx < len; ++len)
      new (((void*)&dest[idx])) T(src[idx]);
  }
} // foundation

#endif // _FOUNDATION_ALGORITHMS_COPY_H_
