//=== bitbyte/foundation/tier3/function.inl ==================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier3/function.in;
/// @brief Implements function binders.
///

#ifndef _BITBYTE_FOUNDATION_TIER3_FUNCTION_INL_
#define _BITBYTE_FOUNDATION_TIER3_FUNCTION_INL_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/tier2.h>
#include <bitbyte/foundation/tier3/export.h>

namespace bitbyte {
namespace foundation {
namespace tier3 {

//===----------------------------------------------------------------------===//
// Binders
//

template <typename _Return>
Function<_Return> bind(_Return (*function)())
{
  bitbyte_foundation_assert(debug, function != NULL);

  typedef _Return (*__Bounded__)();

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      return bounded();
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded = &function;

  return function;
}

template <typename _Return,
          typename _Argument_0>
Function<_Return> bind(
  _Return (*function)(_Argument_0),
  _Argument_0)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0);
    _Argument_0 _0;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0;

  return function;
}

template <typename _Return,
          typename _Argument_0, typename _Argument_1>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1),
  _Argument_0, _Argument_1)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0, _Argument_1);
    _Argument_0 _0; _Argument_1 _1;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0, bounded->_1);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0; bounded->_1 = _1;

  return function;
}

template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2),
  _Argument_0, _Argument_1, _Argument_2)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0, _Argument_1, _Argument_2);
    _Argument_0 _0; _Argument_1 _1; _Argument_2 _2;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0, bounded->_1, bounded->_2);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0; bounded->_1 = _1; bounded->_2 = _2;

  return function;
}

template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                        _Argument_3);
    _Argument_0 _0; _Argument_1 _1; _Argument_2 _2;
    _Argument_3 _3;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0, bounded->_1, bounded->_2,
        bounded->_3);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0; bounded->_1 = _1; bounded->_2 = _2;
  bounded->_3 = _3;

  return function;
}

template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3, typename _Argument_4>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3, _Argument_4),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3, _Argument_4)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                        _Argument_3, _Argument_4);
    _Argument_0 _0; _Argument_1 _1; _Argument_2 _2;
    _Argument_3 _3; _Argument_4 _4;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0, bounded->_1, bounded->_2,
        bounded->_3, bounded->_4);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0; bounded->_1 = _1; bounded->_2 = _2;
  bounded->_3 = _3; bounded->_4 = _4;

  return function;
}

template <typename _Return,
          typename _Argument_0, typename _Argument_1, typename _Argument_2,
          typename _Argument_3, typename _Argument_4, typename _Argument_5>
Function<_Return> bind(
  _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                      _Argument_3, _Argument_4, _Argument_5),
  _Argument_0, _Argument_1, _Argument_2,
  _Argument_3, _Argument_4, _Argument_5)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                        _Argument_3, _Argument_4, _Argument_5);
    _Argument_0 _0; _Argument_1 _1; _Argument_2 _2;
    _Argument_3 _3; _Argument_4 _4; _Argument_5 _5;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0, bounded->_1, bounded->_2,
        bounded->_3, bounded->_4, bounded->_5);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0; bounded->_1 = _1; bounded->_2 = _2;
  bounded->_3 = _3; bounded->_4 = _4; bounded->_5 = _5;

  return function;
}

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
  _Argument_6)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                        _Argument_3, _Argument_4, _Argument_5,
                        _Argument_6);
    _Argument_0 _0; _Argument_1 _1; _Argument_2 _2;
    _Argument_3 _3; _Argument_4 _4; _Argument_5 _5;
    _Argument_6 _6;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0, bounded->_1, bounded->_2,
        bounded->_3, bounded->_4, bounded->_5,
        bounded->_6);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0; bounded->_1 = _1; bounded->_2 = _2;
  bounded->_3 = _3; bounded->_4 = _4; bounded->_5 = _5;
  bounded->_6 = _6;

  return function;
}

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
  _Argument_6, _Argument_7)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                        _Argument_3, _Argument_4, _Argument_5,
                        _Argument_6, _Argument_7);
    _Argument_0 _0; _Argument_1 _1; _Argument_2 _2;
    _Argument_3 _3; _Argument_4 _4; _Argument_5 _5;
    _Argument_6 _6; _Argument_7 _7;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0, bounded->_1, bounded->_2,
        bounded->_3, bounded->_4, bounded->_5,
        bounded->_6, bounded->_7);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0; bounded->_1 = _1; bounded->_2 = _2;
  bounded->_3 = _3; bounded->_4 = _4; bounded->_5 = _5;
  bounded->_6 = _6; bounded->_7 = _7;

  return function;
}

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
  _Argument_6, _Argument_7, _Argument_8)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                        _Argument_3, _Argument_4, _Argument_5,
                        _Argument_6, _Argument_7, _Argument_8);
    _Argument_0 _0; _Argument_1 _1; _Argument_2 _2;
    _Argument_3 _3; _Argument_4 _4; _Argument_5 _5;
    _Argument_6 _6; _Argument_7 _7; _Argument_8 _8;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0, bounded->_1, bounded->_2,
        bounded->_3, bounded->_4, bounded->_5,
        bounded->_6, bounded->_7, bounded->_8);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0; bounded->_1 = _1; bounded->_2 = _2;
  bounded->_3 = _3; bounded->_4 = _4; bounded->_5 = _5;
  bounded->_6 = _6; bounded->_7 = _7; bounded->_8 = _8;

  return function;
}

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
  _Argument_9)
{
  bitbyte_foundation_assert(debug, function != NULL);

  struct __Bounded__ {
    _Return (*function)(_Argument_0, _Argument_1, _Argument_2,
                        _Argument_3, _Argument_4, _Argument_5,
                        _Argument_6, _Argument_7, _Argument_8,
                        _Argument_9);
    _Argument_0 _0; _Argument_1 _1; _Argument_2 _2;
    _Argument_3 _3; _Argument_4 _4; _Argument_5 _5;
    _Argument_6 _6; _Argument_7 _7; _Argument_8 _8;
    _Argument_9 _9;
  };

  struct __Binder__ {
    static _Return exec(__Bounded__ *bounded) {
      bitbyte_foundation_assert(debug, bounded != NULL);
      bitbyte_foundation_assert(debug, bounded->function != NULL);
      return bounded->function(
        bounded->_0, bounded->_1, bounded->_2,
        bounded->_3, bounded->_4, bounded->_5,
        bounded->_6, bounded->_7, bounded->_8,
        bounded->_9);
    }
  };

  Function<_Return> function;
  function.binding = (_Return (*)(void *))&__Binder__::exec;
  __Bounded__ *bounded = (__Bounded__ *)::malloc(sizeof(__Bounded__));
  function.bounded = (void *)bounded;
  bounded->_0 = _0; bounded->_1 = _1; bounded->_2 = _2;
  bounded->_3 = _3; bounded->_4 = _4; bounded->_5 = _5;
  bounded->_6 = _6; bounded->_7 = _7; bounded->_8 = _8;
  bounded->_9 = _9;

  return function;
}

} // tier3
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER3_FUNCTION_INL_
