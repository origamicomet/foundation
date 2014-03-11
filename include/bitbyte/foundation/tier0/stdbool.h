//=== bitbyte/foundation/tier0/stdbool.h =====================================//
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
/// @brief Provides an ISO C9x compliant stdbool.h when possible.
///

#ifndef _BITBYTE_FOUNDATION_STDBOOL_H_
#define _BITBYTE_FOUNDATION_STDBOOL_H_

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

#endif // _BITBYTE_FOUNDATION_STDBOOL_H_
