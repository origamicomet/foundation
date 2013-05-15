// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_COMPAT_MEMORY_H_
#define _FOUNDATION_COMPAT_MEMORY_H_

// Provides memory manipulation functions. 

#include <foundation/detect.h>

#include <string.h>

namespace foundation {
  FOUNDATION_INLINE void copy(
    void* dest,
    const void* src,
    size_t num_bytes )
  {
    if ((dest == nullptr) || (src == nullptr) || (num_bytes == 0))
      return;
    memcpy(dest, src, num_bytes);
  }

  FOUNDATION_INLINE void copy_safe(
    void* dest,
    const void* src,
    size_t num_bytes )
  {
    if ((dest == nullptr) || (src == nullptr) || (num_bytes == 0))
      return;
    memmove(dest, src, num_bytes);
  }

  FOUNDATION_INLINE void fill(
    void* dest,
    uint8_t b,
    size_t num_bytes )
  {
    if ((dest == nullptr) || (num_bytes == 0))
      return;
    memset(dest, b, num_bytes);
  }

  FOUNDATION_INLINE void zero( 
    void* dest,
    size_t num_bytes )
  {
    if ((dest == nullptr) || (num_bytes == 0))
      return;
    fill(dest, 0, num_bytes);
  }

  // Moves a pointer up to align on |alignment| byte boundry.
  FOUNDATION_INLINE void* align_forward(
    void* ptr,
    size_t alignment )
  {
    const uintptr_t mod = ((uintptr_t)ptr) % alignment;
    if (mod)
      return (void*)((uintptr_t)(ptr) + (alignment - mod));
    return ptr;
  }
} // foundation

#endif // _FOUNDATION_COMPAT_MEMORY_H_
