// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/file.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif 

namespace foundation {
  namespace File {
    bool exists(
      const char* path )
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      const wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path, -1, 0, 0
        );

        native_path = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, (wchar_t*)native_path, len
        );
      }

      const DWORD attrib = GetFileAttributesW(native_path);
      return ((attrib != INVALID_FILE_ATTRIBUTES) && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    FILE* open(
      const char* path,
      const char* mode )
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      const wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path, -1, 0, 0
        );

        native_path = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, (wchar_t*)native_path, len
        );
      }

      const wchar_t* native_mode; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, mode, -1, 0, 0
        );

        native_mode = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, mode, -1, (wchar_t*)native_mode, len
        );
      }

      return _wfopen(native_path, native_mode);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    bool destroy(
      const char* path )
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      const wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path, -1, 0, 0
        );

        native_path = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, (wchar_t*)native_path, len
        );
      }

      return (DeleteFileW(native_path) == 0);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    bool move(
      const char* src,
      const char* dest )
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      const wchar_t* native_src; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, src, -1, 0, 0
        );

        native_src = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, src, -1, (wchar_t*)native_src, len
        );
      }

      const wchar_t* native_dest; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, dest, -1, 0, 0
        );

        native_dest = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, dest, -1, (wchar_t*)native_dest, len
        );
      }

      return (MoveFileW(native_src, native_dest) != 0);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    bool copy(
      const char* src,
      const char* dest,
      bool overwrite )
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      const wchar_t* native_src; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, src, -1, 0, 0
        );

        native_src = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, src, -1, (wchar_t*)native_src, len
        );
      }

      const wchar_t* native_dest; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, dest, -1, 0, 0
        );

        native_dest = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, dest, -1, (wchar_t*)native_dest, len
        );
      }

      return (CopyFileW(native_src, native_dest, overwrite ? TRUE : FALSE) != 0);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    bool copy(
      FILE* src,
      FILE* dest,
      size_t chunk_size )
    {
      assert(src != nullptr);
      assert(dest != nullptr);

      void* chunk = alloca(chunk_size);
      size_t num_bytes = 0;

      while ((num_bytes = fread(chunk, 1, chunk_size, src))) {
        if (!fwrite(chunk, 1, num_bytes, dest))
          return false;
      }

      return true;
    }
  } // File
} // foundation