//=== bitbyte/foundation/tier0/malloc.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier0/stdbool.h
/// @brief Standardizes malloc.h.
///

#ifndef _BITBYTE_FOUNDATION_MALLOC_H_
#define _BITBYTE_FOUNDATION_MALLOC_H_

#if defined(__APPLE__) || defined(__linux__)
  #include <malloc.h>
  #include <alloca.h>
#elif defined(__GNUC__) || defined(__clang__)
  #include <malloc.h>
#else
  #include <malloc.h>
  #define alloca _alloca
#endif

#endif // _BITBYTE_FOUNDATION_MALLOC_H_
