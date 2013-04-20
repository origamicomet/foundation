// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_STRING_H_
#define _FOUNDATION_STRING_H_

// A flexibly sized UTF-8 std::string equivalent.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>
#include <foundation/allocator.h>
#include <foundation/utf8.h>
#include <foundation/array.h>

#include <string.h>
#include <stdarg.h>

namespace foundation {
  class FOUNDATION_EXPORT String {
    friend class Iterator;

    public:
      class Iterator {
        friend class String;

        private:
          Iterator( const String& string, size_t byte )
            : _string(const_cast<String&>(string))
            , _byte(byte)
          {}

          Iterator( String& string, size_t byte )
            : _string(string)
            , _byte(byte)
          {}

        public:
          Iterator( const Iterator& iter )
            : _string(iter._string)
            , _byte(iter._byte)
          {}

          Iterator& operator= ( const Iterator& iter )
          {
            _string = iter._string;
            _byte = iter._byte;
            return *this;
          }

        public:
          FOUNDATION_INLINE bool operator== ( const Iterator& iter )
          { return ((&_string == &iter._string) && (_byte == iter._byte)); }

          FOUNDATION_INLINE bool operator!= ( const Iterator& iter )
          { return ((&_string != &iter._string) || (_byte != iter._byte)); }

          Iterator operator++ () const
          {
            size_t byte = min(_byte + 1, max((size_t)1, _string._raw.size()) - 1);
            while ((_string._raw[byte] != 0) && (!utf8::is_initial_byte(_string._raw[byte])))
              ++byte;
            return Iterator(_string, byte);
          }

          Iterator operator++ ()
          {
            size_t byte = min(_byte + 1, max((size_t)1, _string._raw.size()) - 1);
            while ((_string._raw[byte] != 0) && (!utf8::is_initial_byte(_string._raw[byte])))
              ++byte;
            _byte = byte;
            return *this;
          }

          FOUNDATION_INLINE Iterator operator++ ( int )
          { Iterator iter(*this); ++(*this); return iter; }

          Iterator operator-- () const
          {
            size_t byte = max(_byte, (size_t)1) - 1;
            while ((byte > 0) && (!utf8::is_initial_byte(_string._raw[byte])))
              --byte;
            return Iterator(_string, byte);
          }

          Iterator operator-- ()
          {
            size_t byte = max(_byte, (size_t)1) - 1;
            while ((byte > 0) && (!utf8::is_initial_byte(_string._raw[byte])))
              --byte;
            _byte = byte;
            return *this;
          }

          FOUNDATION_INLINE Iterator operator-- ( int )
          { Iterator iter(*this); --(*this); return iter; }

        public:
          FOUNDATION_INLINE char& to_ref()
          { return _string.to_ptr()[_byte]; }

          FOUNDATION_INLINE const char& to_ref() const
          { return _string.to_ptr()[_byte]; }

          uint32_t to_code_point() const
          {
            uint32_t byte = _byte;
            uint32_t state = 0;
            uint32_t code_point = 0;
            uint32_t result = 0;

            while (byte < _string._raw.size()) {
              result = utf8::decode(&state, &code_point, _string._raw[byte]);
              if (result == utf8::REJECT)
                return 0;
              if (result == utf8::ACCEPT)
                return code_point;
              ++byte;
            }

            return 0;
          }
        
          FOUNDATION_INLINE bool is_valid() const
          { return ((_byte > 0) && (_byte <= _string.size())); }

        private:
          String& _string;
          size_t _byte;
      };

    public:
      String( Allocator& allocator = Allocator::heap(), size_t len = 0 );
      String( Allocator& allocator, const Iterator& min, const Iterator& max );
      explicit String( const char* format, ... );
      String( Allocator& allocator, const char* format, ... );

    public:
      String( const String& str );
      String& operator= ( const char* str );
      String& operator= ( const String& str );

    public:
      String operator+ ( char ch ) const;
      String operator+ ( const char* str ) const;
      String operator+ ( const String& str ) const;

      void operator+= ( char ch );
      void operator+= ( const char* str );
      void operator+= ( const String& str );

    public:
      String chomp( const String& prefix );

    public:
      FOUNDATION_INLINE Iterator begin() const
      { const String& self = *this; return Iterator(self, (size_t)0); }

      FOUNDATION_INLINE Iterator end() const
      { const String& self = *this; return Iterator(self, _raw.size() - 1); }

    public:
      FOUNDATION_INLINE Allocator& allocator() const
      { return _raw.allocator(); }

      FOUNDATION_INLINE bool empty() const
      { return (_raw.size() == 0); }

      // Returns the length of the string in bytes.
      FOUNDATION_INLINE size_t size() const
      { return (_raw.size() * sizeof(char)); }

      // Returns the length of the string in code points.
      FOUNDATION_INLINE size_t length() const
      { return utf8::strnlen(_raw.to_ptr(), _raw.size()); }

      FOUNDATION_INLINE char* to_ptr()
      { return (char*)_raw.to_ptr(); }

      FOUNDATION_INLINE const char* to_ptr() const
      { return (const char*)_raw.to_ptr(); }

    private:
      Array<uint8_t> _raw;
  };
} // foundation

#endif // _FOUNDATION_STRING_H_