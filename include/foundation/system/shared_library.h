// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_PROCESS_H_
#define _FOUNDATION_SYSTEM_PROCESS_H_

// Provides a cross-platform wrapper around shared libraries.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  class FOUNDATION_EXPORT SharedLibrary final {
    __foundation_trait(SharedLibrary, non_copyable);

    public:
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      SharedLibrary()
        : _module(nullptr)
      {}
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif

    private:
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      SharedLibrary( HMODULE module )
        : _module(module)
      {}

      ~SharedLibrary()
      { close(); }
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
      
    public:
      static bool open(
        const char* path,
        SharedLibrary& shared_lib );

      void close();

    public:
      void* find(
        const char* sym_name );

    private:
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      HMODULE _module;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
  };
} // foundation

#endif // _FOUNDATION_SYSTEM_PROCESS_H_
