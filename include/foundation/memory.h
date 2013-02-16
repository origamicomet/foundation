// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_MEMORY_H_
#define _FOUNDATION_MEMORY_H_

// A collection of simple helper functions for memory, pointers, and alignment.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/preprocessor.h>
#include <foundation/assert.h>

#include <string.h>

namespace foundation {
  FOUNDATION_INLINE void copy(
    void* dest,
    const void* src,
    size_t num_bytes )
  {
    memcpy(dest, src, num_bytes);
  }

  FOUNDATION_INLINE void copy_safe(
    void* dest,
    const void* src,
    size_t num_bytes )
  {
    memmove(dest, src, num_bytes);
  }

  FOUNDATION_INLINE void fill(
    void* dest,
    uint8_t b,
    size_t num_bytes )
  {
    memset(dest, b, num_bytes);
  }

  FOUNDATION_INLINE void zero( 
    void* dest,
    size_t num_bytes )
  {
    fill(dest, 0, num_bytes);
  }

  // Moves a pointer up to align on |alignment| byte boundry.
  extern FOUNDATION_EXPORT void* align_forward(
    void* ptr,
    size_t alignment );
} // foundation

#endif // _FOUNDATION_MEMORY_H_