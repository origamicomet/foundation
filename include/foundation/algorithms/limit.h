// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ALGORITHMS_LIMIT_H_
#define _FOUNDATION_ALGORITHMS_LIMIT_H_

// Provides generic min, max, and clamp selectors.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#ifdef min
  #undef min
#endif

#ifdef max
  #undef max
#endif

namespace foundation {
  template <typename T>
  FOUNDATION_INLINE T min( const T& a, const T& b )
  { return ((a < b) ? a : b); }

  template <typename T>
  FOUNDATION_INLINE T max( const T& a, const T& b )
  { return ((a > b) ? a : b); }

  template <typename T>
  FOUNDATION_INLINE T clamp( const T& a, const T& b, const T& x )
  { return min(max(a, x), b); }
} // foundation

#endif // _FOUNDATION_ALGORITHMS_LIMIT_H_
