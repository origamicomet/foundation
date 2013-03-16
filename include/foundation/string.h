// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_STRING_H_
#define _FOUNDATION_STRING_H_

// A flexibly sized UTF-8 string.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/assert.h>
#include <foundation/allocator.h>

#include <stdarg.h>

namespace foundation {
  class NativeString;
  class FOUNDATION_EXPORT String {
    private:
      friend class NativeString;

    public:
      explicit String( Allocator& allocator = Allocator::heap(), size_t len = 0 );
      String( Allocator& allocator, const char* format, ... );
      ~String();

    public:
      String( const String& str );
      String( const NativeString& str );
      String& operator= ( const String& str );

    public:
      void operator+= ( char ch );
      void operator+= ( const char* str );

      FOUNDATION_INLINE char& operator[] ( size_t index )
      {
        assert(index <= _length);
        return _str[index];
      }

      FOUNDATION_INLINE const char& operator[] ( size_t index ) const
      {
        assert(index <= _length);
        return _str[index];
      }

    public:
      FOUNDATION_INLINE Allocator& allocator() const { return _allocator; }

      size_t length() const;

      FOUNDATION_INLINE size_t length_in_bytes() const
      { return _length; }

      FOUNDATION_INLINE bool empty() const
      { return (_length != 0); }

      FOUNDATION_EXPORT char* to_ptr()
      { return _str; }

      FOUNDATION_INLINE const char* to_ptr() const
      { return (const char*)_str; }

    private:
      Allocator& _allocator;
      size_t _length;
      char* _str;
  };
} // foundation

#endif // _FOUNDATION_STRING_H_