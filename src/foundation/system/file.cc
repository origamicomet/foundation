// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/file.h>

#include <foundation/assert.h>
#include <foundation/allocator.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif 

namespace foundation {
  namespace File {
    struct Mapping {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      HANDLE f /* file */, m /* mapping */;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    };

    void* map(
      const char* path,
      size_t& num_bytes,
      Mapping*& mapping )
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      wchar_t* native_path; {
        const size_t path_len = strlen(path);
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path, path_len, nullptr, 0);
        native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, path_len, native_path, len);
      }

      HANDLE file_handle = CreateFileW(
        native_path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, /* Don't ask me. */
        NULL);

      if (file_handle == INVALID_HANDLE_VALUE)
        return nullptr;

      HANDLE mapping_ =
        CreateFileMapping(file_handle, NULL, PAGE_READONLY, 0, 0, NULL);

      if (mapping_ == INVALID_HANDLE_VALUE)
        { CloseHandle(file_handle); return nullptr; }

      void* ptr = MapViewOfFile(mapping_, FILE_MAP_READ, 0, 0, num_bytes);

      if (!ptr)
        { CloseHandle(mapping_); CloseHandle(file_handle); return nullptr; }

      mapping = make_new(Mapping, Allocators::heap());
      mapping->f = file_handle;
      mapping->m = mapping;
      num_bytes = (num_bytes == 0) ? (GetFileSize(file_handle, NULL)) : num_bytes;
      return ptr;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
      return nullptr;
    #endif
    }

    void unmap(
      Mapping* mapping )
    {
      assert(mapping != nullptr);
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      if (mapping->f != INVALID_HANDLE_VALUE)
        CloseHandle(mapping->f);
      if (mapping->m != INVALID_HANDLE_VALUE)
        CloseHandle(mapping->m);
      make_delete(Mapping, Allocators::heap(), mapping);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    bool exists(
      const char* path )
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      const wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path, -1, 0, 0);
        native_path = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, (wchar_t*)native_path, len);
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
          CP_UTF8, 0, path, -1, 0, 0);
        native_path = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, (wchar_t*)native_path, len);
      }

      const wchar_t* native_mode; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, mode, -1, 0, 0);
        native_mode = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, mode, -1, (wchar_t*)native_mode, len);
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
          CP_UTF8, 0, path, -1, 0, 0);
        native_path = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, (wchar_t*)native_path, len);
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
          CP_UTF8, 0, src, -1, 0, 0);
        native_src = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, src, -1, (wchar_t*)native_src, len);
      }

      const wchar_t* native_dest; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, dest, -1, 0, 0);
        native_dest = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, dest, -1, (wchar_t*)native_dest, len);
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
          CP_UTF8, 0, src, -1, 0, 0);
        native_src = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, src, -1, (wchar_t*)native_src, len);
      }

      const wchar_t* native_dest; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, dest, -1, 0, 0);
        native_dest = (const wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, dest, -1, (wchar_t*)native_dest, len);
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
          return false; }
      return true;
    }

    void* read_in(
      FILE* file,
      Allocator& allocator,
      size_t* length )
    {
      assert(file != nullptr);
      fseek(file, 0, SEEK_END);
      const long len = ftell(file);
      fseek(file, 0, SEEK_SET);
      if (len <= 0)
        return nullptr;
      if (length) *length = len;
      void* buf = allocator.alloc(len);
      if (fread(buf, 1, len, file) != len) {
        allocator.free(buf);
        return nullptr; }
      return buf;
    }

    bool write_out(
      FILE* file,
      const void* buffer,
      size_t num_bytes )
    {
      assert(file != nullptr);
      uintptr_t iter = (uintptr_t)buffer;
      while (num_bytes > 0) {
        const size_t wrote = fwrite((const void*)buffer, 1, num_bytes, file);
        if (wrote == 0)
          return false;
        num_bytes -= wrote;
        iter += wrote; }
      return true;
    }
  } // File
} // foundation
