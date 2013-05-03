// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_COMPAT_STDIO_H_
#define _FOUNDATION_COMPAT_STDIO_H_

// Provides minimal overhead safe variants of standard input/output functions.

#include <foundation/detect.h>
#include <foundation/compat/extensions.h>

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

// Disable C4505: 'function' : unreferenced local function has been removed
#if defined(FOUNDATION_COMPILER_MSVC)
  #pragma warning(disable:4505) 
#endif

namespace foundation {
  static FOUNDATION_INLINE int vsnprintf(
    char* buffer, size_t buf_size,
    const char* format, va_list ap )
  {
  #if defined(FOUNDATION_COMPILER_MSVC)
    return ::_vsnprintf(buffer, buf_size, format, ap);
  #else
    return ::vsnprintf(buffer, buf_size, format, ap);
  #endif
  }
  static int snprintf(
    char* buffer, size_t buf_size,
    const char* format, ... )
  {
    va_list ap;
    va_start(ap, format);
    const int ret = foundation::vsnprintf(buffer, buf_size, format, ap);
    va_end(ap);
    return ret;
  }

} // foundation

#define snprintf foundation::snprintf
#define vsnprintf foundation::vsnprintf

#endif // _FOUNDATION_COMPAT_STDIO_H_
