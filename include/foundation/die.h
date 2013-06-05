// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DIE_H_
#define _FOUNDATION_DIE_H_

// Abnormally terminates the program while provding a callstack.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  extern FOUNDATION_EXPORT void die(
    bool no_exception_handler = false );
} // foundation

#endif // _FOUNDATION_DIE_H_
