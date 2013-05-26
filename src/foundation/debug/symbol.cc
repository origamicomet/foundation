// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/debug/symbol.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #include <dbghelp.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  namespace Symbols {
    bool load(
      const char** search_directories,
      size_t num_search_directories )
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      SymCleanup(GetCurrentProcess());
      SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_OMAP_FIND_NEAREST);

      if (num_search_directories > 0) {
        String search_path(Allocators::scratch());
        for (size_t idx = 0; idx < num_search_directories; ++idx) {
          search_path += search_directories[idx];
          if (idx != (num_search_directories - 1))
            search_path += ':';
        }

        return (SymInitialize(GetCurrentProcess(), search_path.raw(), TRUE) == TRUE);
      }

      return (SymInitialize(GetCurrentProcess(), NULL, TRUE) == TRUE);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
      return false;
    #endif
    }
  } // Symbols
} // foundation

namespace foundation {
  Symbol::Location::Location()
    : _path(Allocators::heap())
    , _line(Symbol::Location::line_information_unavailable)
  {}

  Symbol::Location::Location( const Symbol::Location& location )
    : _path(location._path)
    , _line(location._line)
  {}

  Symbol::Location& Symbol::Location::operator= (
    const Symbol::Location& location )
  {
    if (&location == this)
      return *this;
    _path = location._path;
    _line = location._line;
    return *this;
  }

  Symbol::Location::~Location()
  {}
} // foundation

namespace foundation {
  Symbol::Symbol()
    : _address(nullptr)
    , _name(Allocators::heap())
  {
  }

  Symbol::Symbol(
    const Symbol& symbol
  ) : _address(symbol._address)
    , _name(symbol._name)
    , _location(symbol._location)
  {
  }

  Symbol& Symbol::operator= (
    const Symbol& symbol )
  {
    if (&symbol == this)
      return *this;
    _address = symbol._address;
    _name = symbol._name;
    _location = symbol._location;
    return *this;
  }

  Symbol::~Symbol()
  {
  }

  Symbol Symbol::from_address(
    void* address )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    Symbol symbol;

    SYMBOL_INFO* si = (SYMBOL_INFO*)alloca(sizeof(SYMBOL_INFO) + (255 - 1));
    zero((void*)si, sizeof(SYMBOL_INFO) + (255 - 1));
    si->SizeOfStruct = sizeof(SYMBOL_INFO);
    si->MaxNameLen = 255;

    if (SymFromAddr(GetCurrentProcess(), (DWORD64)address, 0, si))
      symbol._name = String(Allocators::heap(), si->Name);
    else
      symbol._name = String::format(Allocators::heap(), "%016" PRIx64, (uint64_t)address);

    IMAGEHLP_LINE64 ihl;
    zero((void*)&ihl, sizeof(IMAGEHLP_LINE64));
    ihl.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    DWORD dp /* displacement */ = 0;
    if (SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)address, &dp, &ihl)) {
      symbol._location._path = String(Allocators::heap(), ihl.FileName);
      symbol._location._line = ihl.LineNumber;
    }

    return symbol;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }
} // foundation
