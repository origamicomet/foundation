// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_FILE_H_
#define _FOUNDATION_SYSTEM_FILE_H_

// Provides a collection of file manipulation functions.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/allocator.h>

namespace foundation {
  namespace File {
    struct Mapping;

    // Maps a |file| for |num_bytes| if it exists.
    extern FOUNDATION_EXPORT void* map(
      const char* path,
      size_t& num_bytes,
      Mapping*& mapping );

    // Unmaps a mapped file.
    extern FOUNDATION_EXPORT void unmap(
      Mapping* mapping );

    // Determines if a |file| exists.
    extern FOUNDATION_EXPORT bool exists(
      const char* path );

    // Opens a |file|.
    extern FOUNDATION_EXPORT FILE* open(
      const char* file,
      const char* mode );

    // Destroys |file| if it exists.
    extern FOUNDATION_EXPORT bool remove(
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

    // Copies |src| to |dest| in chunks.
    extern FOUNDATION_EXPORT bool copy(
      FILE* src,
      FILE* dest,
      size_t chunk_size = 4096 );

    // Reads |file| in to a buffer allocated using |allocator|.
    extern FOUNDATION_EXPORT void* read(
      FILE* file,
      Allocator& allocator,
      size_t* length = nullptr );

    // Reads |num_bytes| from |file| completly into |buffer|.
    extern FOUNDATION_EXPORT bool read(
      FILE* file,
      void* buffer,
      size_t num_bytes );

    // Writes |num_bytes| from |buffer| completly out to |file|.
    extern FOUNDATION_EXPORT bool write(
      FILE* file,
      const void* buffer,
      size_t num_bytes );

    // Reads |value from |file|.
    template <typename T>
    extern FOUNDATION_EXPORT bool read(
      FILE* file,
      T& value );

    // Writes |value| to |file|.
    template <typename T>
    extern FOUNDATION_EXPORT bool write(
      FILE* file,
      const T& value );
  } // File
} // foundation

#endif // _FOUNDATION_SYSTEM_FILE_H_
