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
  template <typename T>
  class FOUNDATION_EXPORT Hash abstract {
    protected:
      Hash()
      {}

      Hash(
        const Hash& hash )
      {}

      Hash& operator= (
        const Hash& hash )
      { return *this; }

      virtual ~Hash()
      {}

    public:
      FOUNDATION_INLINE bool operator== (
        const Hash<T>& hash ) const
      { return (((T)*this) == ((T)hash)); }

      FOUNDATION_INLINE bool operator!= (
        const Hash<T>& hash ) const
      { return (((T)*this) != ((T)hash)); }

      FOUNDATION_INLINE bool operator< (
        const Hash<T>& hash ) const
      { return (((T)*this) < ((T)hash)); }

      FOUNDATION_INLINE bool operator> (
        const Hash<T>& hash ) const
      { return (((T)*this) > ((T)hash)); }

    public:
      virtual operator T() const = 0;
  };

  template <typename T, T (*_Hash)( const void*, size_t, T )>
  class FOUNDATION_EXPORT ImmutableHash final
    : public Hash<T>
  {
    public:
      ImmutableHash(
        const void* buffer,
        size_t buffer_len
      ) : _hash(_Hash(buffer, buffer_len, 0))
      {}

      ImmutableHash(
        const char* str
      ) : _hash(_Hash((const void*)str, str ? strlen(str) : 0, 0))
      {}

      ImmutableHash(
        const String& str
      ) : _hash(_Hash((const void*)str.raw(), str.size(), 0))
      {}

      ImmutableHash(
        const ImmutableHash<T, _Hash>& hash
      ) : _hash(hash._hash)
      {}

      ImmutableHash& operator= (
        const ImmutableHash<T, _Hash>& hash )
      {
        _hash = hash._hash;
        return *this;
      }

    public:
      operator T() const override
      { return _hash; }

    private:
      T _hash;
  };
} // foundation

#endif // _FOUNDATION_HASH_H_
