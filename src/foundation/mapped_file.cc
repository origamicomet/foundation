// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/mapped_file.h>
#include <foundation/allocator.h>
#include <foundation/string.h>
#include <foundation/native_string.h>

namespace foundation {
  MappedFile::MappedFile()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    _file_handle = INVALID_HANDLE_VALUE;
    _mapping = INVALID_HANDLE_VALUE;
    _length = 0;
    _ptr = nullptr;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  MappedFile::~MappedFile()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    if (_file_handle != INVALID_HANDLE_VALUE)
      CloseHandle(_file_handle);

    if (_mapping != INVALID_HANDLE_VALUE)
      CloseHandle(_mapping);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  MappedFile* MappedFile::map(
    const char* path,
    size_t num_bytes )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    NativeString native_path(String(Allocator::scratch(), path));

    HANDLE file_handle = CreateFileW(
      native_path.to_ptr(),
      GENERIC_READ,
      FILE_SHARE_READ,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL, /* Don't ask me. */
      NULL );

    if (file_handle == INVALID_HANDLE_VALUE)
      return nullptr;

    HANDLE mapping =
      CreateFileMapping(file_handle, NULL, PAGE_READONLY, 0, 0, NULL);

    if (mapping == INVALID_HANDLE_VALUE) {
      CloseHandle(file_handle);
      return nullptr;
    }

    void* ptr = MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, num_bytes);

    if (!ptr) {
      CloseHandle(mapping);
      CloseHandle(file_handle);
      return nullptr;
    }

    MappedFile* mfile = make_new(MappedFile, Allocator::heap())();
    mfile->_file_handle = file_handle;
    mfile->_mapping = mapping;
    mfile->_length =
      (num_bytes == 0) ? (GetFileSize(file_handle, NULL)) : num_bytes;
    mfile->_ptr = ptr;
    return mfile;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
    return nullptr;
  #endif
  }

  void MappedFile::unmap()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    make_delete(MappedFile, Allocator::heap(), this);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }
} // foundation