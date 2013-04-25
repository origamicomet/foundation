// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/directory.h>
#include <foundation/memory.h>
#include <foundation/path.h>

namespace foundation {
  Directory::Directory()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    _sys_handle = INVALID_HANDLE_VALUE;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
    _sys_handle = nullptr;
  #endif
  }

  Directory::~Directory()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    if (_sys_handle != INVALID_HANDLE_VALUE)
      CloseHandle(_sys_handle);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  Directory* Directory::open(
    const char* path )
  {
    assert(path != NULL);

  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    wchar_t* native_path; {
      const size_t path_len = strlen(path) + 1;
      const size_t len = MultiByteToWideChar(
        CP_UTF8, 0, path, path_len, nullptr, 0
      );

      native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
      MultiByteToWideChar(
        CP_UTF8, 0, path, path_len, native_path, len
      );
    }

    HANDLE sys_handle = CreateFileW(
      native_path,
      GENERIC_READ,
      FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL,
      OPEN_EXISTING,
      FILE_FLAG_BACKUP_SEMANTICS, /* Don't ask me. */
      NULL);

    if (sys_handle == INVALID_HANDLE_VALUE)
      return nullptr;

    Directory* dir = make_new(Directory, Allocator::heap())();
    dir->_sys_handle = sys_handle;
    return dir;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
    return nullptr;
  #endif
  }

  Directory* Directory::create(
    const char* path )
  {
    assert(path != NULL);

  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    wchar_t* native_path; {
      const size_t path_len = strlen(path) + 1;
      const size_t len = MultiByteToWideChar(
        CP_UTF8, 0, path, path_len, nullptr, 0
      );

      native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
      MultiByteToWideChar(
        CP_UTF8, 0, path, path_len, native_path, len
      );
    }

    if (!CreateDirectoryW(native_path, NULL))
      return nullptr;

    HANDLE sys_handle = CreateFileW(
      native_path,
      GENERIC_READ,
      FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL,
      OPEN_EXISTING,
      FILE_FLAG_BACKUP_SEMANTICS, /* Don't ask me. */
      NULL);

    if (sys_handle == INVALID_HANDLE_VALUE)
      return nullptr;

    Directory* dir = make_new(Directory, Allocator::heap())();
    dir->_sys_handle = sys_handle;
    return dir;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
    return nullptr;
  #endif
  }

  bool Directory::exists(
    const char* path )
  {
    assert(path != nullptr);
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    wchar_t* native_path; {
      const size_t path_len = strlen(path) + 1;
      const size_t len = MultiByteToWideChar(
        CP_UTF8, 0, path, path_len, nullptr, 0
      );

      native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
      MultiByteToWideChar(
        CP_UTF8, 0, path, path_len, native_path, len
      );
    }

    const DWORD attrib = GetFileAttributesW(native_path);
    return ((attrib != INVALID_FILE_ATTRIBUTES) && (attrib & FILE_ATTRIBUTE_DIRECTORY));
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  void Directory::remove()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    // TODO: remove.
    make_delete(Directory, Allocator::heap(), this);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  void Directory::close()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    make_delete(Directory, Allocator::heap(), this);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  namespace {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    bool win32_scan_directory(
      const wchar_t* pattern,
      Array<Directory::Entry>& entries,
      bool recursively )
    {
      WIN32_FIND_DATAW find_data;
      HANDLE sys_handle = FindFirstFileW(pattern, &find_data);

      if (sys_handle == INVALID_HANDLE_VALUE)
        return false;

      do {
        Directory::Entry entry;
        
        entry.type = (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ?
          Directory::Entry::DIRECTORY : Directory::Entry::FILE;

        /* entry.path = */ {
          const size_t offset = WideCharToMultiByte(
            CP_UTF8, 0, pattern, wcslen(pattern) - 2, &entry.path[0], 255, 0, 0);
          WideCharToMultiByte(
            CP_UTF8, 0, &find_data.cFileName[0], -1, &entry.path[offset], 255 - offset, 0, 0
          );
        }

        /* entry.last_modified = */ {
          const FILETIME ft = find_data.ftLastWriteTime;
          const uint64_t epoch =
            (((uint64_t)ft.dwHighDateTime) << 32) | ((uint64_t)ft.dwLowDateTime);
          entry.last_modified = TimeStamp(epoch / 10000000LL - 11644473600LL);
        }

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
          // Ignore `.` and `..`
          if ((find_data.cFileName[0] == '.') &&
              (find_data.cFileName[1] == '\0'))
          {
            continue;
          }

          if ((find_data.cFileName[0] == '.') &&
              (find_data.cFileName[1] == '.') &&
              (find_data.cFileName[2] == '\0'))
          {
            continue;
          }

          if (!recursively) {
            entries.push_back(entry);
            continue;
          }

          const size_t len_p = wcslen(pattern);
          const size_t len_rp = wcslen(&find_data.cFileName[0]);
          wchar_t* recursive_pattern =
            (wchar_t*)Allocator::scratch().alloc((len_p + len_rp + 2) * sizeof(wchar_t));

          copy(
            (void*)&recursive_pattern[0],
            (const void*)pattern,
            (len_p - 2) * sizeof(wchar_t));

          copy(
            (void*)&recursive_pattern[len_p - 2],
            (const void*)&find_data.cFileName[0],
            (len_rp) * sizeof(wchar_t));

          recursive_pattern[(len_p - 2 + len_rp) + 0] = '/';
          recursive_pattern[(len_p - 2 + len_rp) + 1] = '*';
          recursive_pattern[(len_p - 2 + len_rp) + 2] = '*';
          recursive_pattern[(len_p - 2 + len_rp) + 3] = '\0';

          if (!win32_scan_directory(recursive_pattern, entries, recursively))
            return false;

          Allocator::scratch().free((void*)recursive_pattern);
        }

        entries.push_back(entry);
      } while (FindNextFileW(sys_handle, &find_data));

      FindClose(sys_handle);
      return true;
    }
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  bool Directory::scan(
    const char* path,
    Array<Directory::Entry>& entries,
    bool recursively )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    wchar_t* pattern; {
      const String pattern_("%s/**", path); 

      const size_t len = MultiByteToWideChar(
        CP_UTF8, 0, pattern_.to_ptr(), pattern_.size(), nullptr, 0
      );

      pattern = (wchar_t*)alloca(len * sizeof(wchar_t));
      MultiByteToWideChar(
        CP_UTF8, 0, pattern_.to_ptr(), pattern_.size(), pattern, len
      );
    }

    return win32_scan_directory(pattern, entries, recursively);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
    return false;
  #endif
  }

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  namespace {
    static const DWORD _notify_filter =
      FILE_NOTIFY_CHANGE_CREATION |
      FILE_NOTIFY_CHANGE_SIZE |
      FILE_NOTIFY_CHANGE_FILE_NAME;
  }
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

  WatchedDirectory* Directory::watch(
    const char* path,
    void* user_ptr,
    Directory::OnEventCallback on_event_callback,
    bool recursively )
  {
    assert(path != nullptr);

  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    wchar_t* native_path; {
      const size_t path_len = strlen(path) + 1;
      const size_t len = MultiByteToWideChar(
        CP_UTF8, 0, path, path_len, nullptr, 0
      );

      native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
      MultiByteToWideChar(
        CP_UTF8, 0, path, path_len, native_path, len
      );
    }

    HANDLE sys_handle = CreateFileW(
      native_path,
      GENERIC_READ | GENERIC_WRITE,
      FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL,
      OPEN_EXISTING,
      FILE_FLAG_BACKUP_SEMANTICS, /* Don't ask me. */
      NULL);

    if (sys_handle == INVALID_HANDLE_VALUE)
      return nullptr;

    HANDLE event = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (!event) {
      CloseHandle(sys_handle);
      return nullptr;
    }

    WatchedDirectory* dir = make_new(WatchedDirectory, Allocator::heap())();
    dir->_sys_handle = sys_handle;
    dir->_overlapped.hEvent = event;
    dir->_user_ptr = user_ptr;
    dir->_on_event_callback = on_event_callback;
    dir->_recursively = recursively;

    if (!ReadDirectoryChangesW(
        sys_handle, &dir->_buf[0], sizeof(dir->_buf),
        recursively, _notify_filter, NULL, &dir->_overlapped,
        &WatchedDirectory::_read_directory_changes_callback
       ))
    {
      make_delete(WatchedDirectory, Allocator::heap(), dir);
      return nullptr;
    }

    return dir;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
    return nullptr;
  #endif
  }

  WatchedDirectory::WatchedDirectory()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    _sys_handle = INVALID_HANDLE_VALUE;
    zero((void*)&_overlapped, sizeof(OVERLAPPED));
    zero((void*)&_buf[0], sizeof(_buf));
    _user_ptr = nullptr;
    _on_event_callback = nullptr;
    _stopping = false;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  WatchedDirectory::~WatchedDirectory()
  {
    if (_sys_handle != INVALID_HANDLE_VALUE)
      CloseHandle(_sys_handle);

    if (_overlapped.hEvent != INVALID_HANDLE_VALUE)
      CloseHandle(_overlapped.hEvent);
  }

  void WatchedDirectory::poll()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    MsgWaitForMultipleObjectsEx(0, NULL, 0, QS_ALLINPUT, MWMO_ALERTABLE);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  void WatchedDirectory::unwatch()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    _stopping = true;
    CancelIo(_sys_handle);
    ReadDirectoryChangesW(
      _sys_handle, &_buf[0], sizeof(_buf),
      FALSE, _notify_filter, NULL, &_overlapped, NULL
    );

    if (!HasOverlappedIoCompleted(&_overlapped))
      WaitForSingleObjectEx(_overlapped.hEvent, INFINITE, TRUE);

    make_delete(WatchedDirectory, Allocator::heap(), this);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  void CALLBACK WatchedDirectory::_read_directory_changes_callback(
    DWORD error_code,
    DWORD num_bytes_transfered,
    LPOVERLAPPED overlapped )
  {
    WatchedDirectory* dir = (WatchedDirectory*)overlapped;

    if (num_bytes_transfered == 0)
      return;

    if (error_code == ERROR_SUCCESS) {
      size_t offset = 0;
      FILE_NOTIFY_INFORMATION* notify;

      do {
        notify = (FILE_NOTIFY_INFORMATION*)&dir->_buf[offset];
        offset += notify->NextEntryOffset;

        Directory::Entry entry;
        entry.type = Directory::Entry::FILE;

        /* entry.path = */ {
          const size_t len = WideCharToMultiByte(
            CP_UTF8, 0, &notify->FileName[0], -1, 0, 0, 0, 0
          );

          String path(Allocator::scratch(), dir->_path.size() + len + 1);
          
          copy(
            (void*)path.to_ptr(),
            (const void*)dir->_path.to_ptr(),
            dir->_path.size() - 1
          );

          path.to_ptr()[dir->_path.size()] = '/';

          WideCharToMultiByte(
            CP_UTF8, 0, &notify->FileName[0], -1, &path.to_ptr()[dir->_path.size() + 1], len, 0, 0
          );

          path.to_ptr()[path.size() - 1] = '\0';

          copy(
            (void*)&entry.path[0],
            (const void*)path.to_ptr(),
            min(path.size(), (size_t)255)
          );
        }

        entry.last_modified = TimeStamp::now();

        Directory::Event event;
        switch( notify->Action ) {
          case FILE_ACTION_RENAMED_NEW_NAME:
          case FILE_ACTION_ADDED:
            event = Directory::EVENT_CREATED;
          break;

          case FILE_ACTION_RENAMED_OLD_NAME:
          case FILE_ACTION_REMOVED:
            event = Directory::EVENT_DESTROYED;
          break;

          case FILE_ACTION_MODIFIED:
            event = Directory::EVENT_MODIFIED;
          break;
        }

        dir->_on_event_callback(event, dir, entry, dir->_user_ptr);
      } while (notify->NextEntryOffset != 0 && !dir->_stopping);
    }

    if (!dir->_stopping)
      return;

    ReadDirectoryChangesW(
      dir->_sys_handle, &dir->_buf[0], sizeof(dir->_buf),
      dir->_recursively, _notify_filter, NULL, &dir->_overlapped,
      &WatchedDirectory::_read_directory_changes_callback
    );
  }
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif
} // foundation