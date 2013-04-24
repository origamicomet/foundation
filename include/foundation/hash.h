// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_HASH_H_
#define _FOUNDATION_HASH_H_

// A class that forces all hashes of a type to use the same hashing function.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/digest.h>
#include <foundation/string.h>

namespace foundation {
  template <typename T, T (*_HashingFunc)( const void*, size_t, T seed )>
  class Hash {
    public:
      Hash( const char* str )
        : _value(_HashingFunc((const void*)str, str ? strlen(str) : 0, 0))
      {}

      Hash( const String& str )
        : _value(_HashingFunc((const void*)str.to_ptr(), str.size(), 0))
      {}

      Hash( const Hash<T, _HashingFunc>& hash )
        : _value(hash._value)
      {}

      Hash& operator= ( const Hash<T, _HashingFunc>& hash )
      { _value = hash._value; return *this; }

    public:
      FOUNDATION_INLINE bool operator< ( const Hash<T, _HashingFunc>& hash ) const
      { return _value < hash._value; }

      FOUNDATION_INLINE bool operator> ( const Hash<T, _HashingFunc>& hash ) const
      { return _value > hash._value; }

      FOUNDATION_INLINE bool operator== ( const Hash<T, _HashingFunc>& hash ) const
      { return _value == hash._value; }

      FOUNDATION_INLINE bool operator!= ( const Hash<T, _HashingFunc>& hash ) const
      { return _value != hash._value; }

    public:
      operator T()
      { return _value; }

    private:
      T _value;
  };
} // foundation

#endif // _FOUNDATION_HASH_H_