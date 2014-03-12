//=== bitbyte/foundation/config.h =============================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/config.h
/// @brief Configuration.
///

#ifndef _BITBYTE_FOUNDATION_CONFIG_H_
#define _BITBYTE_FOUNDATION_CONFIG_H_

/// @def BITBYTE_FOUNDATION_PARANOID
/// @brief Specifies how paranoid Foundation is; if defined Foundation will
///  perform more sanity checks.
///

/// @def BITBYTE_FOUNDATION_DEBUG
/// @brief Enables debugging (and higher) checks and profiling.
///
#define BITBYTE_FOUNDATION_DEBUG 1

/// @def BITBYTE_FOUNDATION_DEVELOPMENT
/// @brief Enables development (and higher) checks and profiling.
///
#define BITBYTE_FOUNDATION_DEVELOPMENT 2

/// @def BITBYTE_FOUNDATION_RELEASE
/// @brief Enables release checks.
///
#define BITBYTE_FOUNDATION_RELEASE 3

/// @def BITBYTE_FOUNDATION_CONFIGURATION
/// @brief Specifies how "loose and fast" Foundation is.
///
#ifndef BITBYTE_FOUNDATION_CONFIGURATION
  #error ("Please specify a configuration by defining `BITBYTE_FOUNDATION_CONFIGURATION`.")
#endif

#endif // _BITBYTE_FOUNDATION_CONFIG_H_
