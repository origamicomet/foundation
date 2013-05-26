// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/directory.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  namespace Directory {
    bool create(
      const char* path )
    {
      assert(path != nullptr);
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path, -1, nullptr, 0);
        native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, native_path, len);
      }

      return (CreateDirectoryW(native_path, NULL) != FALSE);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    bool destroy(
      const char* path )
    {
      assert(path != nullptr);
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path, -1, nullptr, 0);
        native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, native_path, len);
      }

      return (RemoveDirectoryW(native_path) != FALSE);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    bool exists(
      const char* path )
    {
      assert(path != nullptr);
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path, -1, nullptr, 0);
        native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, native_path, len);
      }

      const DWORD attrib = GetFileAttributesW(native_path);
      return ((attrib != INVALID_FILE_ATTRIBUTES) && (attrib & FILE_ATTRIBUTE_DIRECTORY));
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    struct Watched {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      OVERLAPPED oio /* overlapped io */;
      HANDLE sh /* sys handle */;
      uint8_t fni[8192] /* file notifiy information */;
      String p /* path */;
      OnEventHandler oeh /* on event handler */;
      void* oehc /* on event handler closure */;
      bool s /* stopping */;

      Watched()
        : p(Allocators::heap())
      {}
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    };

  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    static const DWORD NotifiyFilter =
      FILE_NOTIFY_CHANGE_CREATION |
      FILE_NOTIFY_CHANGE_SIZE |
      FILE_NOTIFY_CHANGE_FILE_NAME;
  #endif

  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    void CALLBACK on_read_directory_changes(
      DWORD error_code,
      DWORD num_bytes_transfered,
      LPOVERLAPPED overlapped )
    {
      Watched* watched_dir = (Watched*)overlapped;

      if (num_bytes_transfered == 0)
        return;

      if (error_code == ERROR_SUCCESS) {
        size_t offset = 0;
        FILE_NOTIFY_INFORMATION* notify;

        do {
          notify = (FILE_NOTIFY_INFORMATION*)&watched_dir->fni[offset];
          offset += notify->NextEntryOffset;

          const size_t len = WideCharToMultiByte(
            CP_UTF8, 0, &notify->FileName[0], -1, 0, 0, 0, 0);

          String path(Allocators::scratch(), watched_dir->p.size() + len + 1);

          copy(
            (void*)path.raw(),
            (const void*)watched_dir->p.raw(),
            watched_dir->p.size() - 1);

          path.raw()[watched_dir->p.size()] = '/';

          WideCharToMultiByte(
            CP_UTF8, 0, &notify->FileName[0], -1, &path.raw()[watched_dir->p.size() + 1], len, 0, 0);
          
          path.raw()[path.size() - 1] = '\0';

          Event event;
          switch (notify->Action) {
            case FILE_ACTION_RENAMED_NEW_NAME:
            case FILE_ACTION_ADDED:
              event = CREATED;
            break;

            case FILE_ACTION_RENAMED_OLD_NAME:
            case FILE_ACTION_REMOVED:
              event = DESTROYED;
            break;

            case FILE_ACTION_MODIFIED:
              event = MODIFIED;
            break;
          }

          watched_dir->oeh(watched_dir->oehc, event, path.raw());
        } while (notify->NextEntryOffset != 0 && !watched_dir->s);
      }

      if (!watched_dir->s)
        return;

      ReadDirectoryChangesW(
        watched_dir->sh, (void*)&watched_dir->fni[0], 8192,
        TRUE, NotifiyFilter, NULL, &watched_dir->oio,
        &on_read_directory_changes);
    }
  #endif

    Watched* watch(
      const char* path,
      OnEventHandler handler,
      void* closure )
    {
      assert(path != nullptr);
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path, -1, nullptr, 0);
        native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path, -1, native_path, len);
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

      Watched* watched_dir = make_new(Watched, Allocators::heap())();
      zero((void*)watched_dir, sizeof(Watched));
      watched_dir->sh = sys_handle;
      watched_dir->oio.hEvent = event;
      watched_dir->p = path;
      watched_dir->oeh = handler;
      watched_dir->oehc = closure;

      static const bool successful = ReadDirectoryChangesW(
        watched_dir->sh, (void*)&watched_dir->fni[0], 8192,
        TRUE, NotifiyFilter, NULL, &watched_dir->oio,
        &on_read_directory_changes);

      if (successful)
        return watched_dir;

      CloseHandle(event);
      CloseHandle(sys_handle);
      make_delete(Watched, Allocators::heap(), watched_dir);
      return nullptr;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    void poll(
      Watched* watched_dir )
    {
      assert(watched_dir != nullptr);
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      MsgWaitForMultipleObjectsEx(0, NULL, 0, QS_ALLINPUT, MWMO_ALERTABLE);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    void unwatch(
      Watched* watched_dir )
    {
      assert(watched_dir != nullptr);
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      watched_dir->s = true;

      CancelIo(watched_dir->sh);
      ReadDirectoryChangesW(
        watched_dir->sh, (void*)&watched_dir->fni[0], 8192,
        TRUE, NotifiyFilter, NULL, &watched_dir->oio, NULL);

      if (!HasOverlappedIoCompleted(&watched_dir->oio))
        WaitForSingleObjectEx(watched_dir->oio.hEvent, INFINITE, TRUE);

      make_delete(Watched, Allocators::heap(), watched_dir);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    bool _scan(
      const wchar_t* pattern,
      Array<Entry>& entries,
      bool recursively )
    {
      WIN32_FIND_DATAW fd /* find data */;
      HANDLE sh /* sys handle */ = FindFirstFileW(pattern, &fd);

      if (sh == INVALID_HANDLE_VALUE)
        return false;

      do {
        Entry entry;
        
        /* entry.path = */ {
          const size_t offset = WideCharToMultiByte(
            CP_UTF8, 0, pattern, wcslen(pattern) - 2, &entry.path[0], 255, 0, 0);
          WideCharToMultiByte(
            CP_UTF8, 0, &fd.cFileName[0], -1, &entry.path[offset], 255 - offset, 0, 0);
        }

        /* entry.last_modified = */ {
          const FILETIME ft = fd.ftLastWriteTime;
          const uint64_t epoch =
            (((uint64_t)ft.dwHighDateTime) << 32) | ((uint64_t)ft.dwLowDateTime);
          entry.last_modified = (time_t)epoch / 10000000LL - 11644473600LL;
        }

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
          // Ignore '.' and '..'
          if ((fd.cFileName[0] == '.') &&
              (fd.cFileName[1] == '\0'))
          {
            continue;
          }

          if ((fd.cFileName[0] == '.') &&
              (fd.cFileName[1] == '.') &&
              (fd.cFileName[2] == '\0'))
          {
            continue;
          }

          if (!recursively)
            continue;

          const size_t len_p = wcslen(pattern);
          const size_t len_rp = wcslen(&fd.cFileName[0]);
          wchar_t* recursive_pattern =
            (wchar_t*)Allocators::scratch().alloc((len_p + len_rp + 2) * sizeof(wchar_t));

          copy(
            (void*)&recursive_pattern[0],
            (const void*)pattern,
            (len_p - 2) * sizeof(wchar_t));

          copy(
            (void*)&recursive_pattern[len_p - 2],
            (const void*)&fd.cFileName[0],
            (len_rp) * sizeof(wchar_t));

          recursive_pattern[(len_p - 2 + len_rp) + 0] = '/';
          recursive_pattern[(len_p - 2 + len_rp) + 1] = '*';
          recursive_pattern[(len_p - 2 + len_rp) + 2] = '*';
          recursive_pattern[(len_p - 2 + len_rp) + 3] = '\0';

          if (!_scan(recursive_pattern, entries, recursively))
            return false;

          Allocators::scratch().free((void*)recursive_pattern);
        } else {
          entries += entry; }
      } while (FindNextFileW(sh, &fd));

      FindClose(sh);
      return true;
    }
  #endif

    bool scan(
      const char* path,
      Array<Entry>& entries,
      bool recursively )
    {
      assert(path != nullptr);
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      wchar_t* pattern; {
        const String pattern_ = String::format(Allocators::scratch(), "%s/**", path); 
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, pattern_.raw(), pattern_.size(), nullptr, 0);
        pattern = (wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, pattern_.raw(), pattern_.size(), pattern, len); }
      return _scan(pattern, entries, recursively);
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }
  } // Directory
} // foundation
