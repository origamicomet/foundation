//=== bitbyte/foundation/tier0/stdio.h =======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier0/stdio.h
/// @brief Provides an ISO C9x compliant stdio.h when possible.
///

#ifndef _BITBYTE_FOUNDATION_STDBOOL_H_
#define _BITBYTE_FOUNDATION_STDBOOL_H_

#include <stdio.h>

#if defined(_MSC_VER)
  #define vsnprintf __vsnprintf__
  inline int __vsnprintf__(const char *buf, size_t sz, const char *fmt, va_list ap) {
    int count = -1;
    if (size != 0)
      count = _vsnprintf_s(buf, sz, _TRUNCATE, fmt, ap);
    if (count == -1)
      count = _vscprintf(fmt, ap);
    return count;
  }

  #define snprintf __snprintf__
  inline int __snprintf__(const char *buf, size_t sz, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    return __vsnprintf__(buf, sz, fmt, ap);
  }
#endif

#endif // _BITBYTE_FOUNDATION_STDBOOL_H_
