// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/logger.h>

#include <foundation/assert.h>
#include <foundation/containers.h>

namespace foundation {
  namespace {
    struct _Logger {
      Logger log;
      void* closure;
    };
  }

  static Array<_Logger>& loggers() {
    static Array<_Logger> loggers(Allocators::heap());
    return loggers;
  }

  void add_logger(
    Logger logger,
    void* closure )
  {
    (void)closure;
    assert(logger != nullptr);
    const _Logger logger_ = { logger, closure };
    loggers() += logger_;
  }

  void console_logger(
    void* closure,
    const char* format,
    va_list ap )
  {
    (void)closure;
    vfprintf(stdout, format, ap);
    fflush(stdout);
  }

  void file_logger(
    void* closure,
    const char* format,
    va_list ap )
  {
    assert(closure != nullptr);
    vfprintf(((FILE*)closure), format, ap);
    fflush(((FILE*)closure));
  }
} // foundation

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
  #include <syslog.h>
  #include <unistd.h>
#else
  #error ("Unsupported or unknown platform!")
#endif

namespace foundation {
  void debug_logger(
    void* closure,
    const char* format,
    va_list ap )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    (void)closure;
    size_t len = vsnprintf(nullptr, 0, format, ap) + 1;
    char* debug_string = (char*)alloca(len);
    vsnprintf((char*)debug_string, len, format, ap);
    OutputDebugStringA(debug_string);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
    assert(closure != nullptr);
    static bool initialized = false;
    if (!initialized) {
      initialized = true;
      openlog((const char*)closure, LOG_NDELAY, LOG_USER); }
    vsyslog(LOG_DEBUG, format, ap);
  #endif
  }
} // foundation

namespace foundation {
  void log(
    const char* format,
    va_list ap )
  {
    for (auto iter = loggers().begin(); iter != loggers().end(); ++iter)
      ((*iter).log)((*iter).closure, format, ap);
  }
} // foundation
