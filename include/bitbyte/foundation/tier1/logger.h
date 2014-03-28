//=== bitbyte/foundation/tier1/logger.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier1/logger.h
/// @brief Provides logging utilities.
///

#ifndef _BITBYTE_FOUNDATION_TIER1_LOGGER_H_
#define _BITBYTE_FOUNDATION_TIER1_LOGGER_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/export.h>

namespace bitbyte {
namespace foundation {
namespace tier1 {

/// ...
typedef void (*Logger)(
  const char *file,
  size_t line,
  const char *message,
  void *up);

namespace loggers {

/// ...
extern BITBYTE_FOUNDATION_TIER1_EXPORT void add(
  Logger logger,
  void *up = NULL);

} // loggers

///
extern BITBYTE_FOUNDATION_TIER1_EXPORT void log(
  const char *file,
  size_t line,
  const char *message);

} // tier1
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER1_LOGGER_H_
