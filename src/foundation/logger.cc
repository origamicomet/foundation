// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/logger.h>

#include <foundation/assert.h>
#include <foundation/containers.h>

namespace foundation {
  static FOUNDATION_THREAD_LOCAL_STORAGE LogScope* _log_scope = nullptr;

  LogScope::LogScope(
    const char* name
  ) : _parent(_log_scope)
    , _name(name)
  {
    _log_scope = this;
  }

  LogScope::~LogScope()
  {
    _log_scope = _parent;
  }
} // foundation

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
    const LogScope* log_scope,
    const char* format,
    va_list ap )
  {
    (void)closure;
    if (log_scope)
      fprintf(stdout, "[%s] ", log_scope->name());
    vfprintf(stdout, format, ap);
    fprintf(stdout, "\n");
    fflush(stdout);
  }

  void file_logger(
    void* closure,
    const LogScope* log_scope,
    const char* format,
    va_list ap )
  {
    assert(closure != nullptr);
    if (log_scope)
      fprintf(((FILE*)closure), "[%s] ", log_scope->name());
    vfprintf(((FILE*)closure), format, ap);
    fprintf(((FILE*)closure), "\n");
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
    const LogScope* log_scope,
    const char* format,
    va_list ap )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    (void)closure;
    size_t len = 0;
    size_t offset = 0;
    if (log_scope) {
      len = snprintf(nullptr, 0, "[%s] ", log_scope->name());
      offset += len; }
    len += vsnprintf(nullptr, 0, format, ap) + 1;
    char* dbg_string = (char*)alloca(len + 1);
    if (log_scope)
      snprintf(dbg_string, offset + 1, "[%s] ", log_scope->name()) + 1;
    vsnprintf((char*)&dbg_string[offset], len - offset, format, ap);
    dbg_string[len - 1] = '\n';
    dbg_string[len] = '\0';
    OutputDebugStringA(dbg_string);
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
      ((*iter).log)((*iter).closure, _log_scope, format, ap);
  }
} // foundation
