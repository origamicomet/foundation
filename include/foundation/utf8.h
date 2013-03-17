// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _FOUNDATION_UTF8_H_
#define _FOUNDATION_UTF8_H_

// A collection of minimalistic UTF-8 helper functions. 

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
namespace utf8 {
  enum State {
    ACCEPT = 0,
    REJECT = 12,
  };

  extern FOUNDATION_EXPORT uint32_t decode(
    uint32_t* state,
    uint32_t* code_point,
    uint32_t byte );

  extern FOUNDATION_EXPORT size_t strlen(
    const uint8_t* str );

  extern FOUNDATION_EXPORT size_t strnlen(
    const uint8_t* str,
    size_t len );

  FOUNDATION_INLINE bool is_continuation_byte( uint8_t byte ) {
    return ((byte & 0xc0) == 0x80);
  }

  FOUNDATION_INLINE bool is_initial_byte( uint8_t byte ) {
    return ((byte & 0x80) == 0 || (byte & 0xc0) == 0xc0);
  }
} // utf8
} // foundation

#endif // _FOUNDATION_UTF8_H_