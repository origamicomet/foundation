//===-- bitbyte/foundation/tier1/stdio.h -----------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Enforces an ISO C9x compliant stdio.h.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER1_STDIO_H_
#define _BITBYTE_FOUNDATION_TIER1_STDIO_H_

//============================================================================//

#include <stdio.h>
#include <stdarg.h>

//============================================================================//

#if defined(_MSC_VER)
  #define vsnprintf bitbyte_foundation_tier1_vsnprintf
  inline int bitbyte_foundation_tier1_vsnprintf(
    char *buf, size_t sz, const char *fmt, va_list ap)
  {
    int count = -1;
    if (sz != 0)
      count = _vsnprintf_s(buf, sz, _TRUNCATE, fmt, ap);
    if (count == -1)
      count = _vscprintf(fmt, ap);
    return count;
  }

  #define snprintf bitbyte_foundation_tier1_snprintf
  inline int bitbyte_foundation_tier1_snprintf(
    char *buf, size_t sz, const char *fmt, ...)
  {
    va_list ap;
    va_start(ap, fmt);
    return bitbyte_foundation_tier1_vsnprintf(buf, sz, fmt, ap);
  }
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER1_STDIO_H_

//============================================================================//
