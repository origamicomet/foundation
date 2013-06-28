// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_COMPAT_H_
#define _FOUNDATION_COMPAT_H_

/*!
	\brief Tries to level the playing field across different platforms and compilers.

	Tries to level the playing field across different platforms and compilers:
	 * Introduces stdint and inttypes definitions while working around broken
	   compilers and standard libraries (like Microsoft Visual Studio.)
	 * Provides minimal overhead safe variants of standard input/output functions
	   like snprintf.
	 * Aliases compiler specific extensions like __declspec and __attribute__,
	   as well as keywords like abstract, override, sealed, etc.
	 * Aliases (and provides fallbacks) for built-in functions and intrinsics.
	 * Aliases (and provides fallbacks) for C++11 type_trait information.
	 * Provides preprocessor macros like __foundation_stringify or
	   __foundation_source to aid in preprocessor use and magic.
*/

#include <foundation/detect.h>

#include <stdlib.h>
#include <float.h>
#include <foundation/compat/stdio.h>
#include <foundation/compat/stdint.h>
#include <foundation/compat/inttypes.h>
#include <foundation/compat/preprocessor.h>
#include <foundation/compat/extensions.h>
#include <foundation/compat/builtins.h>
#include <foundation/compat/type_traits.h>
#include <foundation/compat/memory.h>

#ifdef min
  #undef min
#endif

#ifdef max
  #undef max
#endif

#endif // _FOUNDATION_COMPAT_H_
