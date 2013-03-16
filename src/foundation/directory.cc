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
    NativeString native_path(String(Allocator::scratch(), path));

    HANDLE sys_handle = CreateFileW(
      native_path.to_ptr(),
      GENERIC_READ,
      FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL,
      OPEN_EXISTING,
      FILE_FLAG_BACKUP_SEMANTICS, /* Don't ask me. */
      NULL );

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
    NativeString native_path(String(Allocator::scratch(), path));

    HANDLE sys_handle = CreateFileW(
      native_path.to_ptr(),
      GENERIC_READ | GENERIC_WRITE,
      FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL,
      CREATE_NEW,
      FILE_FLAG_BACKUP_SEMANTICS, /* Don't ask me. */
      NULL );

    if (sys_handle == INVALID_HANDLE_VALUE)
      return nullptr;

    Directory* dir = make_new(Directory, Allocator::heap())();
    dir->_sys_handle = sys_handle;
    return dir;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
    return nullptr;
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
      const NativeString& pattern,
      Array<Directory::Entry>& entries,
      bool recursively )
    {
      WIN32_FIND_DATAW find_data;
      HANDLE sys_handle = FindFirstFileW(pattern.to_ptr(), &find_data);

      if (sys_handle == INVALID_HANDLE_VALUE)
        return false;

      do {
        Directory::Entry entry;
        
        entry.type = (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ?
          Directory::Entry::DIRECTORY : Directory::Entry::FILE;

        /* entry.path = */ {
          const String pattern_ = String(pattern);
          const String file_name_ = String(
            NativeString(Allocator::scratch(), find_data.cFileName[0])
          );

          copy(
            (void*)&entry.path[0],
            (const void*)pattern_.to_ptr(),
            pattern_.length_in_bytes()
          );

          copy(
            (void*)&entry.path[pattern_.length_in_bytes() - 1],
            (const void*)file_name_.to_ptr(),
            file_name_.length_in_bytes()
          );
        }

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
          // Ignore `.` and `..`
          if ((find_data.cFileName[0] == '.') &&
              (find_data.cFileName[1] == '\0'))
            continue;

          if ((find_data.cFileName[0] == '.') &&
              (find_data.cFileName[1] == '.') &&
              (find_data.cFileName[2] == '\0'))
            continue;

          if (!recursively)
            continue;

          const NativeString recursive_pattern = NativeString(
            Allocator::scratch(), L"%s/**", find_data.cFileName);

          if (!win32_scan_directory(recursive_pattern, entries, recursively))
            return false;
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
    const NativeString pattern =
      String(Allocator::scratch(), "%s/**", path);
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
    NativeString native_path(String(Allocator::scratch(), path));

    HANDLE sys_handle = CreateFileW(
      native_path.to_ptr(),
      GENERIC_READ | GENERIC_WRITE,
      FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL,
      OPEN_EXISTING,
      FILE_FLAG_BACKUP_SEMANTICS, /* Don't ask me. */
      NULL );

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
          const String file_name = String(
            NativeString(Allocator::scratch(), notify->FileName)
          );

          const String path = String(
            Allocator::scratch(), "%s/%s",
            Path::unixify(file_name)
          );

          copy(
            (void*)&entry.path[0],
            (const void*)path.to_ptr(),
            path.length_in_bytes()
          );
        }

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

        dir->_on_event_callback(event, dir, &entry, dir->_user_ptr);
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