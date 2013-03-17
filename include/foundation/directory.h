// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DIRECTORY_H_
#define _FOUNDATION_DIRECTORY_H_

// A cross-platform representation of a directory, that exposes the ability to:
//  * Open, create, and delete directories.
//  * Scan directories for entries (other directories and files).
//  * Watch directories for creation, modification, and removal events.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/array.h>
#include <foundation/string.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
  #include <sys/types.h>
  #include <dirent.h>
#elif 
#endif

namespace foundation {
  class WatchedDirectory;
  class FOUNDATION_EXPORT Directory {
    FOUNDATION_NON_COPYABLE(Directory);

    public:
      struct Entry {
        enum Type {
          FILE      = 1,
          DIRECTORY = 2
        };

        Type type;
        char path[255];
      };

      enum Event {
        EVENT_CREATED   = 1,
        EVENT_DESTROYED = 2,
        EVENT_MODIFIED  = 3
      };

      typedef void (*OnEventCallback)(
        Event event,
        WatchedDirectory* directory,
        const Entry* entry,
        void* user_ptr );

    private:
      Directory();
      ~Directory();

    public:
      static Directory* open(
        const char* path );

      static Directory* create(
        const char* path );

      void remove();
      
      void close();

      static bool scan(
        const char* path,
        Array<Entry>& entries,
        bool recursively = true );

      static WatchedDirectory* watch(
        const char* path,
        void* user_ptr,
        OnEventCallback on_event_callback,
        bool recursively = true );

    private:
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        HANDLE _sys_handle;
        void* _watch_data;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
        DIR* _sys_handle;
      #endif
  };

  class FOUNDATION_EXPORT WatchedDirectory {
    FOUNDATION_NON_COPYABLE(WatchedDirectory);

    private:
      friend class Directory;

    private:
      WatchedDirectory();
      ~WatchedDirectory();

    public:
      void poll();
      void unwatch();

    private:
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      static void CALLBACK _read_directory_changes_callback(
        DWORD error_code,
        DWORD num_bytes_transfered,
        LPOVERLAPPED overlapped );
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif

    private:
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        OVERLAPPED _overlapped;
        HANDLE _sys_handle;
        uint8_t _buf[65535];
        String _path;
        void* _user_ptr;
        Directory::OnEventCallback _on_event_callback;
        bool _recursively;
        bool _stopping;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
  };
} // foundation

#endif // _FOUNDATION_DIRECTORY_H_