// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/shared_library.h>

namespace foundation {
  bool SharedLibrary::open(
    const char* path,
    SharedLibrary& shared_lib )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
   if (shared_lib._module)
      FreeLibrary(shared_lib._module);
    return ((shared_lib._module = LoadLibraryExA(path, NULL, 0)) != nullptr);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  void SharedLibrary::close()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    if (_module)
      FreeLibrary(_module);
    _module = nullptr;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  void* SharedLibrary::find(
    const char* sym_name )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    if (!_module)
      return nullptr;
    return (void*)GetProcAddress(_module, sym_name);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }
} // foundation
