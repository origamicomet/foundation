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

namespace bitbyte {
namespace foundation {
namespace tier3 {

//===----------------------------------------------------------------------===//
// Function
//

/// @brief
///
template <typename _Return>
class BITBYTE_FOUNDATION_TIER3_EXPORT Function {
  public: // operator overloads:
    _Return operator()() const {
      bitbyte_foundation_assert(debug, this->binding != NULL);
      return this->binding(this->bounded);
    }

  public: // methods:
    void unbind() {
      ::free(this->bounded);
      this->binding = NULL;
      this->bounded = NULL;
    }

  public: // members:
    _Return (*binding)(void *bounded);
    void *bounded;
};

//===----------------------------------------------------------------------===//
// Binders
//

/// @brief
///
template <typename _Return>
Function<_Return> bind(_Return (*function)());

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0>
Function<_Return> bind(
  _Return (*function)(_Argument_0),
  _Argument_0);

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0, typename _Argument_1>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1),
  _Argument_0, _Argument_1);

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2),
  _Argument_0, _Argument_1, _Argument_2);

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3);

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3, typename _Argument_4>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3, _Argument_4),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3, _Argument_4);

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3, typename _Argument_4, typename _Argument_5>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3, _Argument_4, _Argument_5),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3, _Argument_4, _Argument_5);

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3, typename _Argument_4, typename _Argument_5,
          typename _Argument_6>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3, _Argument_4, _Argument_5,
                      _Argument_6),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3, _Argument_4, _Argument_5,
  _Argument_6);

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3, typename _Argument_4, typename _Argument_5,
          typename _Argument_6, typename _Argument_7>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3, _Argument_4, _Argument_5,
                      _Argument_6, _Argument_7),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3, _Argument_4, _Argument_5,
  _Argument_6, _Argument_7);

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3, typename _Argument_4, typename _Argument_5,
          typename _Argument_6, typename _Argument_7, typename _Argument_8>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3, _Argument_4, _Argument_5,
                      _Argument_6, _Argument_7, _Argument_8),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3, _Argument_4, _Argument_5,
  _Argument_6, _Argument_7, _Argument_8);

/// @copydoc ::bitbyte::foundation::tier3::bind
///
template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3, typename _Argument_4, typename _Argument_5,
          typename _Argument_6, typename _Argument_7, typename _Argument_8,
          typename _Argument_9>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3, _Argument_4, _Argument_5,
                      _Argument_6, _Argument_7, _Argument_8,
                      _Argument_9),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3, _Argument_4, _Argument_5,
  _Argument_6, _Argument_7, _Argument_8,
  _Argument_9);

} // tier3
} // foundation
} // bitbyte

#include <bitbyte/foundation/tier3/function.inl>

#endif // _BITBYTE_FOUNDATION_TIER3_FUNCTION_H_
