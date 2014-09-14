//===-- bitbyte/foundation.h ------------------------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@bitbyte.ca>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Imports Foundation into the global namespace.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_H_
#define _BITBYTE_FOUNDATION_H_

//============================================================================//

/// \def __BITBYTE_FOUNDATION_IMPORT__
/// \brief Defined implictly by bitbyte/foundation.h it results in the C-api
/// of Foundation being "imported" into the global namespace, that is to say,
/// bitbyte_foundation_xxx() becomes foundation_xxx().
///
#define __BITBYTE_FOUNDATION_IMPORT__

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

/// \namespace ::bitbyte::foundation
/// \brief A public domain foundation library for C/C++.
///
namespace bitbyte { namespace foundation {} }
using namespace ::bitbyte::foundation;

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_H_

//============================================================================//
