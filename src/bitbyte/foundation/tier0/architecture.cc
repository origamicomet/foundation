//=== bitbyte/foundation/tier0/architecture.cc ===============================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier0/architecture.h>

namespace bitbyte {
namespace foundation {
namespace tier0 {

template <>
bool Architecture::compatible<Architectures::x86>() {
  return (_ == Architectures::x86) || (_ == Architectures::x86_64);
}

} // tier0
} // foundation
} // bitbyte
