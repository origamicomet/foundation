// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_DIRECTORY_H_
#define _FOUNDATION_SYSTEM_DIRECTORY_H_

// Provides a collection of directory manipulation functions.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>
#include <foundation/allocator.h>
#include <foundation/string.h>
#include <foundation/containers/array.h>

#include <time.h>

namespace foundation {
  namespace Directory {
    extern FOUNDATION_EXPORT bool create(
      const char* path );

    extern FOUNDATION_EXPORT bool destroy(
      const char* path,
      bool recursively = false );

    extern FOUNDATION_EXPORT bool exists(
      const char* path );

    enum Event {
      CREATED   = 1,
      DESTROYED = 2,
      MODIFIED  = 3
    };

    typedef void (*OnEventHandler)(
      void* closure,
      const Event event,
      const char* path );

    struct Watched;

    extern FOUNDATION_EXPORT Watched* watch(
      const char* path,
      OnEventHandler handler,
      void* closure = nullptr );

    extern FOUNDATION_EXPORT void poll(
      Watched* watched_dir );

    extern FOUNDATION_EXPORT void unwatch(
      Watched* watched_dir );

    struct Entry {
      char path[255];
      time_t last_modified;
    };

    extern FOUNDATION_EXPORT bool scan(
      const char* path,
      Array<Entry>& entries,
      bool recursively = true );
  } // Directory
} // foundation

#endif // _FOUNDATION_SYSTEM_DIRECTORY_H_
