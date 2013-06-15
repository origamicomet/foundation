// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_POINTERS_RELATIVE_H_
#define _FOUNDATION_POINTERS_RELATIVE_H_

// Stores pointers relative to itself (useful for mmaping and blobs).

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  template <typename T>
  class FOUNDATION_EXPORT relative_ptr final {
    public:
      FOUNDATION_INLINE relative_ptr()
        : _offs(0)
      {}

      FOUNDATION_INLINE relative_ptr( const void* ptr )
        : _offs(((int64_t)ptr) - ((int64_t)this))
      {}

      explicit FOUNDATION_INLINE relative_ptr( const int64_t offset )
        : _offs(offset)
      {}

      FOUNDATION_INLINE ~relative_ptr()
      {}

      FOUNDATION_INLINE relative_ptr( const relative_ptr<T>& ptr )
        : _offs((int64_t)((T)ptr) - ((int64_t)this))
      {}

      FOUNDATION_INLINE relative_ptr<T>& operator= ( const relative_ptr<T>& ptr )
      { _offs = ptr._offs; return *this; }

    public:
      FOUNDATION_INLINE operator T() const
      { return (_offs == 0) ? nullptr : (T)(((uintptr_t)this) + _offs); }

    private:
      int64_t _offs;
  };
} // foundation

#endif // _FOUNDATION_POINTERS_RELATIVE_H_
