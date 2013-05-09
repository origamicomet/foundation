// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/string.h>

namespace foundation {
  namespace {
    static const uint32_t UTF8_ACCEPT = 0;
    static const uint32_t UTF8_REJECT = 12;

    static const uint8_t _utf8_transition_table[] = {
      // The first part of the table maps bytes to character classes that
      // to reduce the size of the transition table and create bitmasks.
       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
       7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
       8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
      10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

      // The second part is a transition table that maps a combination
      // of a state of the automaton and a character class to a state.
       0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
      12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
      12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
      12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
      12,36,12,12,12,12,12,12,12,12,12,12,
    };

    uint32_t utf8_decode(
      uint32_t* state,
      uint32_t* code_point,
      uint32_t byte )
    {
      uint32_t type = _utf8_transition_table[byte];
      *code_point = (*state != UTF8_ACCEPT) ?
        (byte & 0x3fu) | (*code_point << 6) :
        (0xff >> type) & (byte);
      *state = _utf8_transition_table[256 + *state + type];
      return *state;
    }

    uint32_t utf8_decode(
      const char*& str )
    {
      uint32_t state = 0;
      uint32_t code_point = 0;
      uint32_t result = 0;
      while (*str++) {
        result = utf8_decode(&state, &code_point, ((const uint8_t*)str)[-1]);
        if (result == UTF8_REJECT)
          return 0;
        if (result == UTF8_ACCEPT)
          return code_point; }
      return 0;
    }

    uint32_t utf8_encode(
      uint32_t code_point,
      const char* str )
    {
      uint8_t* u_str = (uint8_t*)str;
      if (code_point <= 0x7f) {
        u_str[0] = (uint8_t)code_point;
        return 1; }
      else if (code_point <= 0x7ff ) {
        u_str[0] = (uint8_t)(0xc0 + (code_point >> 6));
        u_str[1] = (uint8_t)(0x80 + (code_point & 0x3f));
        return 2; }
      else if (code_point <= 0xffff) {
        u_str[0] = (uint8_t)(0xe0 + (code_point >> 12));
        u_str[1] = (uint8_t)(0x80 + ((code_point >> 6) & 63));
        u_str[2] = (uint8_t)(0x80 + (code_point & 63));
        return 3; }
      else if (code_point <= 0x1ffff) {
        u_str[0] = (uint8_t)(0xf0 + (code_point >> 18));
        u_str[1] = (uint8_t)(0x80 + ((code_point >> 12) & 0x3f));
        u_str[2] = (uint8_t)(0x80 + ((code_point >> 6) & 0x3f));
        u_str[3] = (uint8_t)(0x80 + (code_point & 0x3f));
        return 4; }
      __builtin_unreachable();
    }

    size_t utf8_strlen(
      const char* str )
    {
      const uint8_t* iter = (const uint8_t*)str;
      uint32_t state = 0;
      size_t len = 0;
      if (!str) return 0;
      while (*iter != 0) {
        uint32_t code_point = 0;
        uint32_t r = utf8_decode(&state, &code_point, *iter);
        ++iter;
        if ((r == UTF8_ACCEPT) || (r == UTF8_REJECT))
          ++len; }
      return len;
    }

    size_t utf8_strnlen(
      const char* str,
      size_t len_ )
    {
      const uint8_t* iter = (const uint8_t*)str;
      uint32_t state = 0;
      size_t len = 0;
      if (!str) return 0;
      while ((*iter != 0) && (len--)) {
        uint32_t code_point = 0;
        uint32_t r = utf8_decode(&state, &code_point, *iter);
        ++iter;
        if ((r == UTF8_ACCEPT) || (r == UTF8_REJECT))
          ++len_; }
      return len_;
    }

    FOUNDATION_INLINE bool utf8_is_continuation_byte(
      uint8_t byte )
    { return ((byte & 0xc0) == 0x80); }

    FOUNDATION_INLINE bool utf8_is_initial_byte(
      uint8_t byte )
    { return ((byte & 0x80) == 0 || (byte & 0xc0) == 0xc0); }
  }
} // foundation

namespace foundation {
  String::Iterator String::Iterator::operator++ ()
  {
    size_t idx = min(_idx + 1, _str._raw.size());
    while ((_str._raw[idx] != 0) && (!utf8_is_initial_byte(_str._raw[idx])))
      ++idx;
    _idx = idx;
    return *this;
  }

  String::Iterator String::Iterator::operator++ () const
  {
    size_t idx = min(_idx + 1, _str._raw.size());
    while ((_str._raw[idx] != 0) && (!utf8_is_initial_byte(_str._raw[idx])))
      ++idx;
    return Iterator(_str, idx);
  }

  String::Iterator String::Iterator::operator-- ()
  {
    size_t idx = max(_idx, (size_t)1) - 1;
    while ((idx > 0) && (!utf8_is_initial_byte(_str._raw[idx])))
      --idx;
    _idx = idx;
    return *this;
  }

  String::Iterator String::Iterator::operator-- () const
  {
    size_t idx = max(_idx, (size_t)1) - 1;
    while ((idx > 0) && (!utf8_is_initial_byte(_str._raw[idx])))
      --idx;
    return Iterator(_str, idx);
  }

  uint32_t String::Iterator::to_code_point() const
  {
    uint32_t idx = _idx;
    uint32_t state = 0;
    uint32_t code_point = 0;
    uint32_t result = 0;
    while (idx < _str._raw.size()) {
      result = utf8_decode(&state, &code_point, _str._raw[idx]);
      if (result == UTF8_REJECT)
        return 0;
      if (result == UTF8_ACCEPT)
        return code_point;
      ++idx; }
    return 0;
  }

} // foundation

namespace foundation {
  String::String(
    Allocator& allocator,
    size_t size
  ) : _raw(allocator, size)
  {
    if (size > 0)
      zero((void*)&_raw[0], size);
  }

  String::String(
    const String& str
  ) : _raw(str._raw)
  {
  }

  String::String(
    Allocator& allocator,
    const char* str
  ) : _raw(allocator, str, str ? strlen(str) + 1 : 0)
  {
  }

  String::String(
    const Iterator& min_iter,
    const Iterator& max_iter
  ) : _raw(min_iter._str._raw.allocator(), (size_t)(max(min_iter._idx, max_iter._idx) - min(min_iter._idx, max_iter._idx)))
  {
  }

  String::String(
    Allocator& allocator,
    const Iterator& min_iter,
    const Iterator& max_iter
  ) : _raw(allocator, (size_t)(max(min_iter._idx, max_iter._idx) - min(min_iter._idx, max_iter._idx)))
  {
  }

  String& String::operator= (
    const char* str )
  {
    _raw.resize(strlen(str) + 1);
    copy((void*)&_raw[0], (const void*)str, _raw.size());
    return *this;
  }

  String& String::operator= (
    const String& str )
  {
    _raw.resize(str.size());
    copy((void*)&_raw[0], (const void*)&str._raw[0], _raw.size());
    return *this;
  }

  String String::operator+ (
    const char ch )
  {
    String str_(*this);
    str_._raw[str_._raw.size() - 1] = ch;
    str_._raw += '\0';
    return str_;
  }

  void String::operator+= (
    const char ch )
  {
    _raw[_raw.size() - 1] = ch;
    _raw += '\0';
  }

  String String::operator+ (
    const char* str )
  {
    String str_(*this);
    const size_t len = str ? strlen(str) + 1 : 0;
    const size_t offset = max(str_._raw.size(), (size_t)1) - 1;
    str_._raw.resize(offset + len);
    copy((void*)&str_._raw[offset], (const void*)str, len);
    return str_;
  }

  void String::operator+= (
    const char* str )
  {
    const size_t len = str ? strlen(str) + 1 : 0;
    const size_t offset = max(_raw.size(), (size_t)1) - 1;
    _raw.resize(offset + len);
    copy((void*)&_raw[offset], (const void*)str, len);
  }

  String String::operator+ (
    const String& str )
  {
    String str_(*this);
    str_ += str;
    return str_;
  }

  void String::operator+= (
    const String& str )
  {
    const size_t len = str._raw.size();
    const size_t offset = max(_raw.size(), (size_t)1) - 1;
    _raw.resize(offset + len);
    copy((void*)&_raw[offset], (const void*)&str._raw[0], len);
  }

  String String::format(
    Allocator& allocator,
    const char* fmt, ... )
  {
    va_list ap;
    va_start(ap, fmt);
    const size_t len = vsnprintf(nullptr, 0, fmt, ap) + 1;
    String str_(allocator, len);
    vsnprintf(&str_._raw[0], len, fmt, ap);
    va_end(ap);
    return str_;
  }

  String::Iterator String::find(
    const char* needle,
    const String::Iterator& offset )
  {
    return find(String(Allocators::scratch(), needle), offset);
  }

  String::Iterator String::find(
    const String& needle,
    const String::Iterator& offset )
  {
    assert(&offset._str == this);

    Iterator iter_h = offset;
    while (iter_h != end()) {
      Iterator iter_n = needle.begin();
      Iterator iter_h_ = iter_h;
      while (iter_h != end()) {
        const uint32_t cp_h = iter_h.to_code_point();
        const uint32_t cp_n = iter_n.to_code_point();
        if (cp_h != cp_n)
          break;
        if (iter_n == needle.end())
          return iter_h_;
        ++iter_h;
        ++iter_n;
      }
    }

    return end();
  }

  String String::replace(
    const char* needle,
    const char* with )
  {
    return replace(
      String(Allocators::scratch(), needle),
      String(Allocators::scratch(), with));
  }

  String String::replace(
    const String& needle,
    const String& with )
  {
    String str_(*this);

    const size_t len_n = needle._raw.size() - 1;
    const size_t len_w = with._raw.size() - 1;

    Iterator offset = str_.find(needle, begin());
    while (offset != str_.end()) {
      if (len_w > len_n) {
        const size_t diff = len_w - len_n;
        const size_t offset_ = offset._idx + len_n;
        str_._raw.resize(str_._raw.size() + diff);
        copy_safe(
          (void*)&str_._raw[offset_ + diff],
          (const void*)&str_._raw[offset_],
          str_._raw.size() - offset_); }
      else if (len_w < len_n) {
        const size_t diff = len_n - len_w;
        const size_t offset_ = offset._idx + len_n;
        copy_safe(
          (void*)&str_._raw[offset_ - diff],
          (const void*)&str_._raw[offset_],
          str_._raw.size() - offset_);
        str_._raw.resize(str_._raw.size() - diff); }
      copy((void*)&str_._raw[offset._idx], (const void*)&with._raw[0], len_w);
      offset = str_.find(needle, ++offset); }
      
    return str_;
  }

  String String::chomp(
    const char* what )
  {
    return chomp(String(Allocators::scratch(), what));
  }

  String String::chomp(
    const String& what )
  {
    Iterator iter_s = begin();
    Iterator iter_w = what.begin();

    while (iter_s.to_code_point() == iter_w.to_code_point()) {
      if ((iter_s == end()) || (iter_w == what.end()))
        break;
      ++iter_s;
      ++iter_w; }

    return String(Allocators::heap(), iter_s, end());
  }

  size_t String::length() const
  {
    return utf8_strnlen(&_raw[0], _raw.size());
  }
} // foundation

namespace foundation {
  const char* next(
    const char* str )
  {
    assert(str != nullptr);
    const uint8_t* iter = (const uint8_t*)str;
    if (!*iter++)
      return nullptr;
    while (*iter) {
      if (utf8_is_initial_byte(*iter))
        return (const char*)iter;
      ++iter; }
    return nullptr;
  }

  const char* prev(
    const char* str )
  {
    assert(str != nullptr);
    const uint8_t* iter = (const uint8_t*)str - 1;
    while (*iter) {
      if (utf8_is_initial_byte(*iter))
        return (const char*)iter;
      --iter; }
    return nullptr;
  }

  const char* find(
    const char* haystack,
    const char* needle )
  {
    assert(needle != nullptr);
    assert(haystack != nullptr);

    const char* iter_h = haystack;
    while (*iter_h) {
      const char* iter_n = needle;
      const char* iter_h_ = iter_h;
      while (*iter_h) {
        const uint32_t cp_h = utf8_decode(iter_h);
        const uint32_t cp_n = utf8_decode(iter_n);
        if (cp_h != cp_n)
          break;
        if (!*iter_n)
          return iter_h_;
      }
    }

    return nullptr;
  }
} // foundation
