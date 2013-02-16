// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_NATIVE_STRING_H_
#define _FOUNDATION_NATIVE_STRING_H_

// A flexibly sized platform specific string (hence native).
// On Windows this is a UTF-16 string.
// On Mac OSX, Linux, and BSDs this is a UTF-8 string.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/assert.h>
#include <foundation/allocator.h>

#include <stdarg.h>
#include <wchar.h>

namespace foundation {
#if defined(FOUNDATION_PLATFORM_WINDOWS)
  class String;
  class FOUNDATION_EXPORT NativeString {
    private:
      friend class String;

    public:
      explicit NativeString( Allocator& allocator = Allocator::default() );
      NativeString( Allocator& allocator, const wchar_t* format, ... );
      ~NativeString();

    public:
      NativeString( const String& str );
      NativeString( const NativeString& str );
      NativeString& operator= ( const NativeString& str );

    public:
      void operator+= ( char ch );
      void operator+= ( wchar_t ch );
      void operator+= ( const char* str );
      void operator+= ( const wchar_t* str );

      FOUNDATION_INLINE wchar_t& operator[] ( size_t index )
      {
        assert(index <= _length);
        return _str[index];
      }

      FOUNDATION_INLINE const wchar_t& operator[] ( size_t index ) const
      {
        assert(index <= _length);
        return _str[index];
      }

    public:
      FOUNDATION_INLINE bool is_empty() const
      { return (_length != 0); }

      FOUNDATION_INLINE size_t length() const
      { return _length; }

      FOUNDATION_INLINE size_t length_in_bytes() const
      { return _length * sizeof(wchar_t); }

      FOUNDATION_EXPORT wchar_t* to_ptr()
      { return _str; }

      FOUNDATION_INLINE const wchar_t* to_ptr() const
      { return (const wchar_t*)_str; }

    private:
      Allocator& _allocator;
      size_t _length;
      wchar_t* _str;
  };
#elif defined(FOUNDATION_PLATFORM_MACOSX)
#elif defined(FOUNDATION_PLATFORM_LINUX)
#endif
} // foundation

#endif // _FOUNDATION_NATIVE_STRING_H_