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

#include <foundation/utf8.h>

namespace foundation {
namespace utf8 {
  static const uint8_t _transition_table[] = {
    // The first part of the table maps bytes to character classes that
    // to reduce the size of the transition table and create bitmasks.
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
     7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
     8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

    // The second part is a transition table that maps a combination
    // of a state of the automaton and a character class to a state.
     0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
    12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
    12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
    12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
    12,36,12,12,12,12,12,12,12,12,12,12,
  };

  uint32_t decode( uint32_t* state, uint32_t* code_point, uint32_t byte ) {
    uint32_t type = _transition_table[byte];
    *code_point = (*state != ACCEPT) ?
      (byte & 0x3fu) | (*code_point << 6) :
      (0xff >> type) & (byte);
    *state = _transition_table[256 + *state + type];
    return *state;
  }

  uint32_t encode( uint32_t code_point, const char* str ) {
    uint8_t* u_str = (uint8_t*)str;
    if (code_point <= 0x7f) {
      u_str[0] = (uint8_t)code_point;
      return 1;
    } else if (code_point <= 0x7ff ) {
      u_str[0] = (uint8_t)(0xc0 + (code_point >> 6));
      u_str[1] = (uint8_t)(0x80 + (code_point & 0x3f));
      return 2;
    } else if (code_point <= 0xffff) {
      u_str[0] = (uint8_t)(0xe0 + (code_point >> 12));
      u_str[1] = (uint8_t)(0x80 + ((code_point >> 6) & 63));
      u_str[2] = (uint8_t)(0x80 + (code_point & 63));
      return 3;
    } else if (code_point <= 0x1ffff) {
      u_str[0] = (uint8_t)(0xf0 + (code_point >> 18));
      u_str[1] = (uint8_t)(0x80 + ((code_point >> 12) & 0x3f));
      u_str[2] = (uint8_t)(0x80 + ((code_point >> 6) & 0x3f));
      u_str[3] = (uint8_t)(0x80 + (code_point & 0x3f));
      return 4;
    }
  }

  size_t strlen( const uint8_t* str ) {
    const uint8_t* iter = str;
    uint32_t state = 0;
    size_t len = 0;
    if (!str)
      return 0;
    while (*iter != 0) {
      uint32_t code_point = 0;
      uint32_t r = decode(&state, &code_point, *iter);
      ++iter;
      if ((r == ACCEPT) || (r == REJECT))
        ++len;
    } return len;
  }

  size_t strnlen( const uint8_t* str, size_t len_ ) {
    const uint8_t* iter = str;
    uint32_t state = 0;
    size_t len = 0;
    if (!str)
      return 0;
    while ((*iter != 0) && (len_--)) {
      uint32_t code_point = 0;
      uint32_t r = decode(&state, &code_point, *iter);
      ++iter;
      if ((r == ACCEPT) || (r == REJECT))
        ++len;
    } return len;
  }
} // utf8
} // foundation