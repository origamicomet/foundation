// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_PREPROCESSOR_H_
#define _FOUNDATION_PREPROCESSOR_H_

// Provides simple macros to make preprocessor tricks easier:
//  * __foundation_stringify expands macros before stringifying them.
//  * __foundation_join expands macros before joining them.
//  * FOUNDATION_NON_COPYABLE defines private members to follow the RoT.
//  * make_new/delete wrap placement new for foundation::Allocators.

// __foundation_stringify [
#define __foundation_stringify1( _ToStringify ) \
  #_ToStringify

#define __foundation_stringify0( _ToStringify ) \
  __foundation_stringify1(_ToStringify)

#define __foundation_stringify( _ToStringify ) \
  __foundation_stringify0(_ToStringify)
// ]

// __foundation_join [
#define __foundation_join1( _Left, _Right ) \
  _Left##_Right

#define __foundation_join0( _Left, _Right ) \
  __foundation_join1(_Left, _Right)

#define __foundation_join( _Left, _Right ) \
  __foundation_join0(_Left, _Right)
// ]

#define FOUNDATION_NON_COPYABLE( _Class ) \
  private: \
    _Class( const _Class& _ ); \
    _Class& operator= ( const _Class& _ );

#include <new>

#define make_new( _Type, _Allocator ) \
  new ((_Allocator.alloc(sizeof(_Type), alignof(_Type)))) _Type

#define make_delete( _Type, _Allocator, _Instance ) \
  do { _Instance->~_Type(); _Allocator.free((void*)_Instance); } while (0, 0)

#endif // _FOUNDATION_PREPROCESSOR_H_
