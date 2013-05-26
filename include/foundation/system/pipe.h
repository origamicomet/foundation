// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_PIPE_H_
#define _FOUNDATION_SYSTEM_PIPE_H_

// Provides a cross-platform wrapper around IPC pipes.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  class FOUNDATION_EXPORT Pipe final {
    __foundation_trait(Pipe, non_copyable);
    __foundation_trait(Pipe, non_constructable);
  };
} // foundation

#endif // _FOUNDATION_SYSTEM_PIPE_H_
