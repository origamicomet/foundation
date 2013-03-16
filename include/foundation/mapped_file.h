// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_MAPPED_FILE_H_
#define _FOUNDATION_MAPPED_FILE_H_

// A cross-platform mmap.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/preprocessor.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#elif 
#endif

namespace foundation {
  class FOUNDATION_EXPORT MappedFile {
    FOUNDATION_NON_COPYABLE(MappedFile);

    private:
      MappedFile();
      ~MappedFile();

    public:
      static MappedFile* map(
        const char* path,
        size_t num_bytes );

      void unmap();

      FOUNDATION_INLINE size_t length()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        return _length;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      FOUNDATION_INLINE void* to_ptr() const
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        return _ptr;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

    private:
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        HANDLE _file_handle;
        HANDLE _mapping;
        size_t _length;
        void*  _ptr;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
  };
} // foundation

#endif // _FOUNDATION_MAPPED_FILE_H_