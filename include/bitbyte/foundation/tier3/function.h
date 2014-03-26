//=== bitbyte/foundation/tier3/function.h ====================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier3/function.h
/// @brief Provides bindable functions.
///

#ifndef _BITBYTE_FOUNDATION_TIER3_FUNCTION_H_
#define _BITBYTE_FOUNDATION_TIER3_FUNCTION_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/tier2.h>
#include <bitbyte/foundation/tier3/export.h>

#include <functional>
#include <utility>

namespace bitbyte {
namespace foundation {
namespace tier3 {

template <typename _Return, typename... _Arguments>
using Function = ::std::function<_Return(_Arguments...)>;

template <typename _Return, typename _Function, typename... _Arguments>
auto bind(_Function &&F, _Arguments &&...A) -> decltype(::std::bind(::std::forward<_Function, _Arguments>(F, A)...)) {
  return ::std::bind(::std::forward<_Function, _Arguments>(F, A)...);
}

namespace placeholders { using namespace ::std::placeholders; }

} // tier3
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER3_FUNCTION_H_
