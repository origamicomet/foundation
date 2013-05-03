// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DEBUG_CRASH_HANDLER_H_
#define _FOUNDATION_DEBUG_CRASH_HANDLER_H_

// Provides a crash-handler that logs pertinent information and callstack.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/debug/exception_handler.h>

namespace foundation {
  extern FOUNDATION_EXPORT void crash_handler(
    Exception exception,
    ExecutionState& execution_state );
} // foundation

#endif // _FOUNDATION_DEBUG_CRASH_HANDLER_H_
