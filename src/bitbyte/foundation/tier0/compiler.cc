//=== bitbyte/foundation/tier0/compiler.cc ===================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier0/compiler.h>

namespace bitbyte {
namespace foundation {
namespace tier0 {

const Compiler compiler() {
  static const Compiler compiler = (Compilers::_)BITBYTE_FOUNDATION_COMPILER;
  return compiler;
}

} // tier0
} // foundation
} // bitbyte
