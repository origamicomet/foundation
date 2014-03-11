//=== bitbyte/foundation/tier0/preprocessor.h ================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier0/preprocessor.h
/// @brief Abuses the pre-processor to provide useful functionality.
///

#ifndef _BITBYTE_FOUNDATION_TIER0_PREPROCESSOR_H_
#define _BITBYTE_FOUNDATION_TIER0_PREPROCESSOR_H_

/// @def bitbyte_foundation_stringify
/// @brief Expands `_Token` then stringificates.
///
#define __bitbyte_foundation_stringify__(_Token) #_Token
#define _bitbyte_foundation_stringify_(_Token) __bitbyte_foundation_stringify__(_Token)
#define bitbyte_foundation_stringify(_Token) _bitbyte_foundation_stringify_(_Token)

/// @def bitbyte_foundation_join
/// @brief Expands `_Lhs` and `_Rhs` then joins.
///
#define __bitbyte_foundation_join__(_Lhs, _Rhs) _Lhs ## _Rhs
#define _bitbyte_foundation_join_(_Lhs, _Rhs) __bitbyte_foundation_join__(_Lhs, _Rhs)
#define bitbyte_foundation_join(_Lhs, _Rhs) _bitbyte_foundation_join_(_Lhs, _Rhs)

#endif // _BITBYTE_FOUNDATION_TIER0_PREPROCESSOR_H_
