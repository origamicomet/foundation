// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_SERVICE_H_
#define _FOUNDATION_SYSTEM_SERVICE_H_

// Provides a cross-platform wrapper around services/daemons.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  class FOUNDATION_EXPORT Service final {
    __foundation_trait(Service, non_copyable);
    __foundation_trait(Service, non_constructable);
  };
} // foundation

#endif // _FOUNDATION_SYSTEM_SERVICE_H_
