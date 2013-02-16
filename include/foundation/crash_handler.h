// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_CRASH_HANDLER_H_
#define _FOUNDATION_CRASH_HANDLER_H_

// A simple handler that logs pertinent information on crash.

#include <foundation/config.h>
#include <foundation/compat.h>

namespace foundation {
  // Installs the crash handler (this registers underlying system handlers.)
  extern FOUNDATION_EXPORT bool install_crash_handler();

  // Uninstalls the crash handler (this unregisters underlying system handlers.)
  extern FOUNDATION_EXPORT bool uninstall_crash_handler();
} // foundation

#endif // _FOUNDATION_CRASH_HANDLER_H_