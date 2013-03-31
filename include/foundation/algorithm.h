// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALGORITHM_H_
#define _FOUNDATION_ALGORITHM_H_

// A collection of utility functions like min, max, clamp, sort, search, etc.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>

#include <stdlib.h>

// Windows.h #defines min/max.
#ifdef min
  #undef min
#endif
#ifdef max
  #undef max
#endif

namespace foundation {
  // Returns the lesser of two values.
  template <typename T>
  FOUNDATION_INLINE T min( T a, T b ) {
    return (( a < b ) ? a : b);
  }

  // Returns the greater of two values.
  template <typename T>
  FOUNDATION_INLINE T max( T a, T b ) {
    return (( a > b ) ? a : b);
  }

  // Returns a value such that a <= x <= b.
  template <typename T>
  FOUNDATION_INLINE T clamp( T a, T b, T x ) {
    return ((x < a) ? a : (x > b ? b : x));
  }

  template <typename T>
  FOUNDATION_INLINE int _sort_comparator( const void* a_, const void* b_ ) {
    const T& a = *((const T*)a_);
    const T& b = *((const T*)b_);

    if (a > b)
      return 1;

    if (a < b)
      return -1;

    return 0;
  }

  // Sorts a given array into ascending order.
  template <typename T>
  FOUNDATION_INLINE void sort(
    T* array,
    size_t num_items )
  {
    qsort(
      (const void*)array,
      num_items,
      sizeof(T),
      &_sort_comparator<T>
    );
  }

  template <typename _Key, typename _Value>
  FOUNDATION_INLINE int _search_comparator( const void* k, const void* v ) {
    const _Key& key = *((const _Key*)k);
    const _Value& value = *((const _Value*)v);

    if (key > value)
      return 1;

    if (key < value)
      return -1;

    return 0;
  }

  // Performs an O(1) to O(log n) search on a foundation::sort'd array.
  template <typename _Key, typename _Value>
  FOUNDATION_INLINE const _Value* search(
    const _Key& key,
    const _Value* array,
    size_t num_items )
  {
    return bsearch(
      (const void*)&key,
      (const void*)array,
      num_items,
      sizeof(_Value),
      &_search_comparator<_Key, _Value>
    );
  }

  // Performs an O(1) to O(log n) search on a foundation::sort'd array.
  template <typename T>
  FOUNDATION_INLINE const T* search(
    const T& key,
    const T* array,
    size_t num_items )
  {
    return bsearch(
      (const void*)&key,
      (const void*)array,
      num_items,
      sizeof(T),
      &_search_comparator<T, T>
    );
  }

  // Rounds an uint32_t up to the next prime number.
  extern FOUNDATION_EXPORT uint32_t round_to_prime( uint32_t n );
} // foundation

#endif // _FOUNDATION_ALGORITHM_H_