// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/string.h>
#include <foundation/native_string.h>
#include <foundation/memory.h>

namespace foundation {
  // Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
  // See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.
  namespace {
    static const uint32_t UTF8_ACCEPT = 0;
    static const uint32_t UTF8_REJECT = 1;

    static const uint8_t  utf8d[] = {
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 00..1f
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 20..3f
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 40..5f
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 60..7f
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9, // 80..9f
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, // a0..bf
      8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, // c0..df
      0xa,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x4,0x3,0x3, // e0..ef
      0xb,0x6,0x6,0x6,0x5,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8, // f0..ff
      0x0,0x1,0x2,0x3,0x5,0x8,0x7,0x1,0x1,0x1,0x4,0x6,0x1,0x1,0x1,0x1, // s0..s0
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1, // s1..s2
      1,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1, // s3..s4
      1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1,1,1, // s5..s6
      1,3,1,1,1,1,1,3,1,3,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // s7..s8
    };

    FOUNDATION_INLINE uint32_t decode(
      uint32_t* state,
      uint32_t* codep,
      uint32_t byte )
    {
      uint32_t type = utf8d[byte];

      *codep = (*state != UTF8_ACCEPT) ?
        (byte & 0x3fu) | (*codep << 6) :
        (0xff >> type) & (byte);

      *state = utf8d[256 + *state * 16 + type];
      return *state;
    }

    bool count_code_points(
      uint8_t* str,
      size_t* count )
    {
      uint32_t cp;
      uint32_t state = UTF8_ACCEPT;

      for (*count = 0; *str; ++str)
        if (!decode(&state, &cp, *str))
          *count += 1;

      return (state != UTF8_ACCEPT);
    }
  }

  String::String( Allocator& allocator, size_t len )
    : _allocator(allocator)
    , _length(len)
    , _str((char*)allocator.alloc(len, alignof(char)))
  {
  }

  String::String( Allocator& allocator, const char* format, ... )
    : _allocator(allocator)
  {
    va_list va;
    va_start(va, format);
    _length = vsnprintf(nullptr, 0, format, va) + 1;
    _str = (char*)_allocator.alloc(_length, alignof(char));
    vsnprintf(_str, _length - 1, format, va);
    va_end(va);
  }

  String::~String()
  {
    _allocator.free((void*)_str);
    _str = nullptr;
  }

  String::String( const String& str )
    : _allocator(str._allocator)
    , _length(str._length)
    , _str((char*)str._allocator.alloc(str._length))
  {
    copy((void*)_str, (const void*)str._str, str._length);
  }

  String& String::operator= ( const String& str )
  {
    if (this == &str)
      return *this;

    _length = str._length;
    _str = (char*)_allocator.realloc((void*)_str, str._length);
    copy((void*)_str, (const void*)str._str, str._length);

    return *this;
  }

  void String::operator+= ( char ch )
  {
    _length += 1;
    _str = (char*)_allocator.realloc((void*)_str, _length, alignof(char));
    _str[_length - 1] = ch;
    _str[_length]     = '\0';
  }

  void String::operator+= ( const char* str )
  {
    const size_t ofs = _length;
    const size_t len = strlen(str);

    _length = ofs + len;
    _str = (char*)_allocator.realloc((void*)_str, _length, alignof(char));
    copy((void*)&_str[ofs - 1], (const void*)str, len + 1);
  }

  size_t String::length() const
  {
    size_t code_points = 0;
    count_code_points((uint8_t*)_str, &code_points);
    return code_points;
  }
} // foundation