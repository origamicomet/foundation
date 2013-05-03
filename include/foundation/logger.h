// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_LOGGER_H_
#define _FOUNDATION_LOGGER_H_

// Provides a uniform logging interface

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

// Disable C4505: 'function' : unreferenced local function has been removed
#if defined(FOUNDATION_COMPILER_MSVC)
  #pragma warning(disable:4505) 
#endif

namespace foundation {
  typedef void (*Logger)(
    void* closure,
    const char* format,
    va_list ap );

  extern FOUNDATION_EXPORT void add_logger(
    Logger logger,
    void* closure = nullptr );

  extern FOUNDATION_EXPORT void console_logger(
    void* closure,
    const char* format,
    va_list ap );

  extern FOUNDATION_EXPORT void file_logger(
    // The FILE* to use.
    void* closure,
    const char* format,
    va_list ap );

  extern FOUNDATION_EXPORT void debug_logger(
    // The log identifier to use (used for openlog on POSIX systems).
    void* closure,
    const char* format,
    va_list ap );

  // ============================================================

  extern FOUNDATION_EXPORT void log(
    const char* format,
    va_list ap );

  static void log(
    const char* format, ... )
  {
    va_list ap;
    va_start(ap, format);
    foundation::log(format, ap);
    va_end(ap);
  }
} // foundation

#endif // _FOUNDATION_LOGGER_H_
