// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_HASH_H_
#define _FOUNDATION_HASH_H_

// Provides a type-safe hash.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>
#include <foundation/string.h>

namespace foundation {
  template <typename T, T (*_Hash)( const void*, size_t, T )>
  class FOUNDATION_EXPORT Hash final
  {
    public:
      Hash()
        : _hash(0)
      {}

      Hash(
        const void* buffer,
        size_t buffer_len
      ) : _hash(_Hash(buffer, buffer_len, 0))
      {}

      Hash(
        const char* str
      ) : _hash(_Hash((const void*)str, str ? (strlen(str) + 1) : 0, 0))
      {}

      Hash(
        const String& str
      ) : _hash(_Hash((const void*)str.raw(), str.size(), 0))
      {}

      Hash(
        const Hash<T, _Hash>& h
      ) : _hash(h._hash)
      {}

      Hash& operator= (
        const Hash<T, _Hash>& h )
      {
        _hash = h._hash;
        return *this;
      }

    public:
      FOUNDATION_INLINE bool operator== (
        const Hash<T, _Hash>& h ) const
      { return (_hash == h._hash); }

      FOUNDATION_INLINE bool operator!= (
        const Hash<T, _Hash>& h ) const
      { return (_hash != h._hash); }

      FOUNDATION_INLINE bool operator< (
        const Hash<T, _Hash>& h ) const
      { return (_hash < h._hash); }

      FOUNDATION_INLINE bool operator> (
        const Hash<T, _Hash>& h ) const
      { return (_hash > h._hash); }

    public:
      operator T() const
      { return _hash; }

    private:
      T _hash;
  };
} // foundation

#endif // _FOUNDATION_HASH_H_
