//===-- bitbyte/foundation/tier1/malloc.h -----------------------*- C++ -*-===//
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
/// \brief Enforces the existance of alloca in malloc.h.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER1_MALLOC_H_
#define _BITBYTE_FOUNDATION_TIER1_MALLOC_H_

//============================================================================//

#if defined(__APPLE__) || defined(__linux__)
  #include <malloc.h>
  #include <alloca.h>
#elif defined(__GNUC__) || defined(__clang__)
  #include <malloc.h>
#elif defined(_MSC_VER)
  #include <malloc.h>
  #define alloca _alloca
#endif

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER1_MALLOC_H_

//============================================================================//
