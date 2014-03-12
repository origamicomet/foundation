//=== bitbyte/foundation/tier1/logger.cc =====================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier1/logger.h>
#include <bitbyte/foundation/tier1/assert.h>

namespace bitbyte {
namespace foundation {
namespace tier1 {

struct Logger_ {
  Logger logger;
  void *up;
};

static Logger_ loggers_[256];
static size_t loggers_n_ = 0;

void loggers::add(Logger logger, void *up) {
  bitbyte_foundation_assert(debug, loggers_n_ < 256);
  Logger_ *logger_ = &loggers_[loggers_n_++];
  logger_->logger = logger;
  logger_->up = up;
}

void log(const char *file, size_t line, const char *message) {
  for (size_t logger = 0; logger < loggers_n_; ++logger) {
    (loggers_[logger].logger)(file, line, message, loggers_[logger].up);
  }
}

} // tier1
} // foundation
} // bitbyte
