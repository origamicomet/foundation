//=== bitbyte/foundation/tier1/assertion.cc ==================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier1/assertion.h>

#include <stdlib.h>
#include <signal.h>

namespace bitbyte {
namespace foundation {
namespace tier1 {

static Assertion::Handler assertion_handler_ = NULL;
static void *assertion_handler_up_ = NULL;

void Assertion::handler(Handler &handler, void *&up) {
  handler = assertion_handler_;
  up = assertion_handler_up_;
}

void Assertion::set_handler(Handler handler, void *up) {
  assertion_handler_ = handler;
  assertion_handler_up_ = up;
}

void Assertion::handle() const {
  if (assertion_handler_)
    assertion_handler_(*this, assertion_handler_up_);
  ::abort();
}

} // tier1
} // foundation
} // bitbyte
