// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DEBUG_SYMBOLS_H_
#define _FOUNDATION_DEBUG_SYMBOLS_H_

// Provides a cross-platform interface to query symbol information.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/string.h>

namespace foundation {
  namespace Symbols {
    extern FOUNDATION_EXPORT bool load(
      const char** search_directories,
      size_t num_search_directories );
  } // Symbols
} // foundation

namespace foundation {
  class FOUNDATION_EXPORT Symbol final {
    public:
      class Location final {
        private:
          friend class Symbol;

        private:
          Location();

        public:
          Location( const Location& location );
          Location& operator=( const Location& location );

        private:
          ~Location();

        public:
          FOUNDATION_INLINE const String& path() const
          { return _path; }

          // Returned by Location::line to signify that line information is not
          // available.
          static const uint32_t line_information_unavailable = 0xFFFFFFFFu;

          FOUNDATION_INLINE uint32_t line() const
          { return _line; }

        private:
          String _path;
          uint32_t _line;
      };

    private:
      Symbol();

    public:
      Symbol(
        const Symbol& symbol );

      Symbol& operator= (
        const Symbol& symbol );

      ~Symbol();

    public:
      static Symbol from_address(
        void* address );

    public:
      FOUNDATION_INLINE void* address() const
      { return _address; }

      FOUNDATION_INLINE const String& name() const
      { return _name; }

      FOUNDATION_INLINE const Location& location() const
      { return _location; }

    private:
      void* _address;
      String _name;
      Location _location;
  };
} // foundation

#endif // _FOUNDATION_DEBUG_SYMBOLS_H_
