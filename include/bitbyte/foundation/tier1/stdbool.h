//===-- bitbyte/foundation/tier1/stdbool.h ----------------------*- C++ -*-===//
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
/// \brief Enforces an ISO C9x compliant stdbool.h.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER1_STDBOOL_H_
#define _BITBYTE_FOUNDATION_TIER1_STDBOOL_H_

//============================================================================//

#if defined(_MSC_VER)
  #ifndef __cplusplus
    typedef unsigned char _Bool;
    typedef _Bool bool;
    #define true ((_Bool)1)
    #define false ((_Bool)0)
    #define __bool_true_false_are_defined 1
  #endif
#else
  #include <stdbool.h>
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER1_STDBOOL_H_

//============================================================================//
