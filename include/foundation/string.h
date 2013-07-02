// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_STRING_H_
#define _FOUNDATION_STRING_H_

// Provides a flexibly sized string.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/allocator.h>
#include <foundation/containers/array.h>

namespace foundation {
  class FOUNDATION_EXPORT String final {
    public:
      class Iterator final {
        private:
          friend class String;

        private:
          FOUNDATION_INLINE Iterator(
            String& str,
            size_t idx
          ) : _str(str)
            , _idx(idx)
          {}

        public:
          FOUNDATION_INLINE Iterator(
            const Iterator& iter
          ) : _str(iter._str)
            , _idx(iter._idx)
          {}

          FOUNDATION_INLINE Iterator& operator= (
            const Iterator& iter )
          { _str = iter._str; _idx = iter._idx; return *this; }

        public:
          FOUNDATION_INLINE bool operator== ( const Iterator& iter )
          { return ((&_str == &iter._str) && (_idx == iter._idx)); }

          FOUNDATION_INLINE bool operator!= ( const Iterator& iter )
          { return ((&_str != &iter._str) || (_idx != iter._idx)); }

        public:
          Iterator operator++ ();
          Iterator operator++ () const;

          FOUNDATION_INLINE Iterator operator++ ( int )
          { Iterator iter(*this); ++(*this); return iter; }

          Iterator operator-- ();
          Iterator operator-- () const;

          FOUNDATION_INLINE Iterator operator-- ( int )
          { Iterator iter(*this); --(*this); return iter; }

        public:
          FOUNDATION_INLINE char& to_ref()
          { return _str._raw[_idx]; }

          FOUNDATION_INLINE char& operator* ()
          { return to_ref(); }

          FOUNDATION_INLINE const char& to_ref() const
          { return _str._raw[_idx]; }

          FOUNDATION_INLINE const char& operator* () const
          { return to_ref(); }

          uint32_t to_code_point() const;

        private:
          String& _str;
          size_t _idx;
      };

    private:
      friend class Iterator;

    public:
      explicit String(
        Allocator& allocator,
        size_t size = 0 );

    public:
      String(
        const String& str );

      String(
        Allocator& allocator,
        const char* str );

      String(
        const Iterator& min,
        const Iterator& max );

      String(
        Allocator& allocator,
        const Iterator& min,
        const Iterator& max );

      String& operator= (
        const char* str );

      String& operator= (
        const String& str );

    public:
      String operator+ (
        const char ch );

      void operator+= (
        const char ch );

      String operator+ (
        const char* str );

      void operator+= (
        const char* str );

      String operator+ (
        const String& str );

      void operator+= (
        const String& str );

    public:
      FOUNDATION_INLINE Iterator begin() const
      { return Iterator((String&)*this, (size_t)0); }

      FOUNDATION_INLINE Iterator end() const
      { return Iterator((String&)*this, _raw.size()); }

    public:
      static String format(
        Allocator& allocator,
        const char* fmt, ... );

    public:
      FOUNDATION_INLINE Iterator find(
        const char* needle )
      { return find(needle, begin()); }

      Iterator find(
        const char* needle,
        const Iterator& offset );

      FOUNDATION_INLINE Iterator find(
        const String& needle )
      { return find(needle, begin()); }

      Iterator find(
        const String& needle,
        const Iterator& offset );

      String replace(
        const char* needle,
        const char* with );

      String replace(
        const String& needle,
        const String& with );

      String chomp(
        const char* what );

      String chomp(
        const String& what );

    public:
      FOUNDATION_INLINE Allocator& allocator() const
      { return _raw.allocator(); }

    public:
      FOUNDATION_INLINE bool empty() const
      { return (_raw.size() == 0) || (_raw[0] == '\0'); }

      FOUNDATION_INLINE size_t size() const
      { return _raw.size(); }

      size_t length() const;

    public:
      FOUNDATION_INLINE char* raw()
      { return _raw.raw(); }

      FOUNDATION_INLINE const char* raw() const
      { return _raw.raw(); }

    protected:
      Array<char> _raw;
  };
} // foundation

namespace foundation {
  extern FOUNDATION_EXPORT const char* next(
    const char* str );

  extern FOUNDATION_EXPORT const char* prev(
    const char* str );

  extern FOUNDATION_EXPORT uint32_t to_code_point(
    const char* str );

  extern FOUNDATION_EXPORT const char* find(
    const char* haystack,
    const char* needle );

  extern FOUNDATION_EXPORT const char* chomp(
    const char* prefix,
    const char* str );

  extern FOUNDATION_EXPORT char* replace_all(
    char* str,
    char a,
    char b );

  extern FOUNDATION_EXPORT const char* replace_all(
    Allocator& allocator,
    const char* str,
    char a,
    char b );
} // foundation

#endif // _FOUNDATION_STRING_H_
