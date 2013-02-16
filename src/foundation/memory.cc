// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/memory.h>

namespace foundation {
  void* align_forward(
    void* ptr,
    size_t alignment )
  {
    const uintptr_t mod = ((uintptr_t)ptr) % alignment;

    if (mod)
      ptr = (void*)((uintptr_t)(ptr) + (alignment - mod));
    
    return ptr;
  }
} // foundation