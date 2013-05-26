// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_PROCESS_H_
#define _FOUNDATION_SYSTEM_PROCESS_H_

// Provides a cross-platform wrapper around process managment.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #include <process.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  class FOUNDATION_EXPORT Process final {
    __foundation_trait(Process, non_copyable);

    public:
      typedef uint64_t Id;

    private:
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      Process( Id id, HANDLE sys_handle )
        : _id(id), _sys_handle(sys_handle)
      {}

      ~Process()
      {}
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
      
    public:
      // Gets this process.
      static Process& current();

    public:
      // Gets the this process's id.
      FOUNDATION_INLINE Id id() const
      { return _id; }

    public:
      // Executes a new process (doesn't return on success).
      static bool exec(
        const char* path,
        char *const argv[],
        char *const envp[] );

    private:
      Id _id;
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      HANDLE _sys_handle;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
  };
} // foundation

#endif // _FOUNDATION_SYSTEM_PROCESS_H_
