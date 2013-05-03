// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_COMPAT_PREPROCESSOR_H_
#define _FOUNDATION_COMPAT_PREPROCESSOR_H_

// Provides preprocessor macros like __foundation_stringify or
// __foundation_source to aid in preprocessor use and magic.

#include <foundation/detect.h>

// Expands macros before stringifying them.
#define __foundation_stringify1( _ToStringify ) \
  #_ToStringify
#define __foundation_stringify0( _ToStringify ) \
  __foundation_stringify1(_ToStringify)
#define __foundation_stringify( _ToStringify ) \
  __foundation_stringify0(_ToStringify)

// Exapnds macros before joining them.
#define __foundation_join1( _Left, _Right ) \
  _Left##_Right
#define __foundation_join0( _Left, _Right ) \
  __foundation_join1(_Left, _Right)
#define __foundation_join( _Left, _Right ) \
  __foundation_join0(_Left, _Right)

// Applies a trait (like non_copyable).
#define __foundation_trait( _Class, _Trait ) \
  __trait__##_Trait(_Class)

// Disallows (by declaring, but not defining) construction.
#define __trait__non_constructable( _Class ) \
  private: \
    _Class();

// Disallows (by declaring, but not defining) assignment.
#define __trait__non_assignable( _Class ) \
  private: \
    _Class& operator= ( const _Class& _ );

// Disallows (by declaring, but not defining) copy-construction or assignment.
#define __trait__non_copyable( _Class ) \
  private: \
    _Class( const _Class& _ ); \
    _Class& operator= ( const _Class& _ );

// Disallows (by declaring, but not defining) copy-construction.
#define __trait__non_copy_constructable( _Class ) \
  private: \
    _Class( const _Class& _ );

#endif // _FOUNDATION_COMPAT_PREPROCESSOR_H_
