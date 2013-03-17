// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_FILE_H_
#define _FOUNDATION_FILE_H_

// A collection of cross-platform file utilities.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  namespace File {
    // Opens a |file|.
    extern FOUNDATION_EXPORT FILE* open(
      const char* file,
      const char* mode );

    // Destroys |file| if it exists.
    extern FOUNDATION_EXPORT bool destroy(
      const char* file );

    // Moves |src| to |dest| if it exists.
    extern FOUNDATION_EXPORT bool move(
      const char* src,
      const char* dest );

    // Copies |src| to |dest| if it exists.
    extern FOUNDATION_EXPORT bool copy(
      const char* src,
      const char* dest,
      bool overwrite = false );
  } // File
} // foundation

#endif // _FOUNDATION_FILE_H_