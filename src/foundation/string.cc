// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/string.h>
#include <foundation/memory.h>

namespace foundation {
  String::String( Allocator& allocator, size_t len )
    : _raw(allocator, 0)
  {
    _raw.resize(len);
  }

  String::String( const char* format, ... )
    : _raw(Allocator::heap(), 0)
  {
    va_list va;
    va_start(va, format);
    _raw.resize(vsnprintf(nullptr, 0, format, va) + 1);
    vsnprintf((char*)_raw.to_ptr(), _raw.size() - 1, format, va);
    _raw[_raw.size() - 1] = '\0';
    va_end(va);
  }

  String::String( Allocator& allocator, const char* format, ... )
    : _raw(allocator, 0)
  {
    va_list va;
    va_start(va, format);
    _raw.resize(vsnprintf(nullptr, 0, format, va) + 1);
    vsnprintf((char*)_raw.to_ptr(), _raw.size() - 1, format, va);
    _raw[_raw.size() - 1] = '\0';
    va_end(va);
  }

  String::String( Allocator& allocator, const Iterator& min, const Iterator& max )
    : _raw(allocator, 0)
  {
    assert(&min._string == &max._string);
    assert(min._byte <= max._byte);

    size_t len = 0;
    
    // Inclusive:
    const auto past_max = ++max;
    if (past_max.is_valid()) len = (past_max._byte - min._byte);
    else len = max._byte - min._byte;

    _raw.resize(len + 1);
    copy((void*)_raw.to_ptr(), (const void*)&min._string._raw[min._byte], len);
    _raw[len] = '\0';
  }

  String::String( const String& str )
    : _raw(str._raw)
  {
  }

  String& String::operator= ( const char* str )
  {
    assert(str != nullptr);
    _raw.resize(strlen(str) + 1);
    copy((void*)_raw.to_ptr(), (const void*)str, _raw.size());
    return *this;
  }

  String& String::operator= ( const String& str )
  {
    if (&str == this)
      return *this;

    _raw = str._raw;
    return *this;
  }

  String String::operator+ ( char ch ) const
  {
    String str_ = *this;
    str_._raw.push_back((uint8_t)ch);
    return str_;
  }

  String String::operator+ ( const char* str ) const
  {
    String str_ = *this;
    const size_t offset = max((size_t)1, str_._raw.size()) - 1;
    const size_t len = strlen(str);
    str_._raw.resize(str_._raw.size() + len + 1);
    copy((void*)&str_._raw[offset], (const void*)str, len + 1);
    return str_;
  }

  String String::operator+ ( const String& str ) const
  {
    String str_ = *this;
    const size_t offset = max((size_t)1, str_._raw.size()) - 1;
    const size_t len = str.size();
    str_._raw.resize(str_._raw.size() + len + 1);
    copy((void*)&str_._raw[offset], (const void*)str.to_ptr(), len + 1);
    return str_;
  }

  void String::operator+= ( char ch )
  {
    _raw.push_back((uint8_t)ch);
  }

  void String::operator+= ( const char* str )
  {
    const size_t offset = max((size_t)1, _raw.size()) - 1;
    const size_t len = strlen(str);
    _raw.resize(_raw.size() + len + 1);
    copy((void*)&_raw[offset], (const void*)str, len + 1);
  }

  void String::operator+= ( const String& str )
  {
    const size_t offset = max((size_t)1, str._raw.size() - 1);
    const size_t len = str._raw.size();
    _raw.resize(_raw.size() + len + 1);
    copy((void*)&_raw[offset], (const void*)str.to_ptr(), len + 1);
  }

  String String::chomp( const String& prefix )
  {
    auto iter_s = begin();
    auto iter_p = prefix.begin();

    while (iter_s.to_code_point() == iter_p.to_code_point()) {
      ++iter_s;
      ++iter_p;
    }

    return String(Allocator::scratch(), begin(), iter_s);
  }
} // foundation