// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_PATH_H_
#define _FOUNDATION_SYSTEM_PATH_H_

// Provides a collection of path manipulation functions.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/string.h>

namespace foundation {
  namespace Path {
    // Returns the seperator character for the target platform.
    extern FOUNDATION_EXPORT char seperator();

    // Returns the |path| stripped of leading directories and extension.
    extern FOUNDATION_EXPORT String basename(
      const String& path );

    // Returns the |path| striped of trailing file name and extension.
    extern FOUNDATION_EXPORT String dirname(
      const String& path );

    // Returns the file extension from |path|.
    extern FOUNDATION_EXPORT String extension(
      const String& path );

    // Returns the absolute unixified version of the |path|.
    extern FOUNDATION_EXPORT String absolute(
      const String& path );

    // Returns |path| relative to |relative_to|.
    extern FOUNDATION_EXPORT String relative_to(
      const String& path,
      const String& relative_to );

    // Returns |path| with `\` in |path| replaced with `/`, and drive letters
    // replaced replaced with /<letter>/ (like mingw).
    extern FOUNDATION_EXPORT String unixify(
      const String& path );
  } // Path
} // foundation

#endif // _FOUNDATION_SYSTEM_PATH_H_
