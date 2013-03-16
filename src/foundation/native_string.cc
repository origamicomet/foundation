// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/native_string.h>
#include <foundation/string.h>
#include <foundation/memory.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_MACOSX)
#elif defined(FOUNDATION_PLATFORM_LINUX)
#endif

namespace foundation {
#if defined(FOUNDATION_PLATFORM_WINDOWS)
  NativeString::NativeString( Allocator& allocator, size_t len )
    : _allocator(allocator)
    , _length(len)
    , _str((wchar_t*)allocator.alloc(len, alignof(wchar_t)))
  {
  }

  NativeString::NativeString( Allocator& allocator, const wchar_t* format, ... )
    : _allocator(allocator)
  {
    va_list va;
    va_start(va, format);

    _length = vswprintf(nullptr, 0, format, va) + 1;
    _str = (wchar_t*)_allocator.alloc(
      _length * sizeof(wchar_t),
      alignof(wchar_t));
    vswprintf(_str, _length - 1, format, va);

    va_end(va);
  }

  NativeString::~NativeString()
  {
    _allocator.free((void*)_str);
    _str = nullptr;
  }

  String::String( const NativeString& str )
    : _allocator(str._allocator)
    , _length(WideCharToMultiByte(CP_UTF8, 0, str.to_ptr(), str.length(), nullptr, 0, 0, 0))
    , _str((char*)str._allocator.alloc(_length))
  {
    WideCharToMultiByte(CP_UTF8, 0, str.to_ptr(), str.length(), _str, _length, 0, 0);
  }

  NativeString::NativeString( const String& str )
    : _allocator(str._allocator)
    , _length(MultiByteToWideChar(CP_UTF8, 0, str.to_ptr(), str.length(), nullptr, 0))
    , _str((wchar_t*)str._allocator.alloc(_length * sizeof(wchar_t)))
  {
    MultiByteToWideChar(CP_UTF8, 0, str.to_ptr(), str.length(), _str, _length);
  }

  NativeString::NativeString( const NativeString& str )
    : _allocator(str._allocator)
    , _length(str._length)
    , _str((wchar_t*)str._allocator.alloc(str._length * sizeof(wchar_t)))
  {
    copy((void*)_str, (const void*)str._str, str._length);
  }

  NativeString& NativeString::operator= ( const NativeString& str )
  {
    if (this == &str)
      return *this;

    _length = str._length;
    _str = (wchar_t*)_allocator.realloc((void*)_str, str._length);
    copy((void*)_str, (const void*)str._str, str._length);

    return *this;
  }

  void NativeString::operator+= ( wchar_t ch )
  {
    _length += 1;
    _str = (wchar_t*)_allocator.realloc(
      (void*)_str,
      _length * sizeof(wchar_t),
      alignof(wchar_t));
    _str[_length - 1] = ch;
    _str[_length]     = (wchar_t)'\0';
  }

  void NativeString::operator+= ( const char* str )
  {
    // TODO: WideCharToMultiByte() w/ alloca()
    NativeString native_str(String(Allocator::scratch(), str));
    (*this) += native_str.to_ptr();
  }

  void NativeString::operator+= ( const wchar_t* str )
  {
    const size_t ofs = _length;
    const size_t len = wcslen(str);

    _length = ofs + len;
    _str = (wchar_t*)_allocator.realloc(
      (void*)_str,
      _length * sizeof(wchar_t),
      alignof(wchar_t));
    copy((void*)&_str[ofs - 1], (const void*)str, (len + 1) * sizeof(wchar_t));
  }
#elif defined(FOUNDATION_PLATFORM_MACOSX)
#elif defined(FOUNDATION_PLATFORM_LINUX)
#endif
} // foundation