// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/process.h>

#include <foundation/logger.h>

namespace foundation {
  Process& Process::current()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    static Process process((Id)GetCurrentProcessId(), GetCurrentProcess());
    return process;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  bool Process::exec(
    const char* path,
    char *const argv[],
    char *const envp[] )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    #if defined(FOUNDATION_COMPILER_MSVC)
      return (_execve(path, argv, envp) != -1);
    #else
      log("Process::exec is not implemented, yet.");
      return false;
    #endif
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }
} // foundation
