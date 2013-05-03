// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALGORITHMS_SEARCH_H_
#define _FOUNDATION_ALGORITHMS_SEARCH_H_

// Provides an O(log n) search algorithm.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  template <typename _Key, typename _Value>
  FOUNDATION_INLINE int __search_comparator(
    const void* key_,
    const void* value_ )
  {
    const _Key& key = *((const T*)key_);
    const _Value& value = *((const T*)value_);
    if (key > value)
      return 1;
    if (key < value)
      return - 1;
    return 0;
  }

  template <typename _Key, typename _Value>
  FOUNDATION_INLINE const _Value* search(
    const _Key& key,
    const _Value* array,
    size_t array_len )
  {
    return (_Value*)(
      (const void*)&key, (const void*)array, array_len,
      sizeof(_Value), &__search_comparator<_Key, _Value>);
  }

  template <typename T>
  FOUNDATION_INLINE const T* search(
    const T& key,
    const T* array,
    size_t array_len )
  {
    return search<T, T>(key, array, array_len);
  }
} // foundation

#endif // _FOUNDATION_ALGORITHMS_SEARCH_H_
