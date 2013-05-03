// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DETECT_H_
#define _FOUNDATION_DETECT_H_

// Tries to detect the platform, compiler, architecture and supported standards
// from various preprocessor definitions. See foundation/detect/* for more info.
//  Platforms:
//    Windows, Mac OSX, Linux;
//    FreeBSD, NetBSD, OpenBSD, DragonFly;
//    iOS, Android, and NaCl.
//  Compilers:
//    Microsoft Visual C/C++;
//    Clang and GCC;
//    and Intel's C/C++ compiler.
//  Architectures:
//    x86, x86_64, ARM, and Mips.
//  Supported Standards:
//    C++11.

#include <foundation/detect/compiler.h>
#include <foundation/detect/architecture.h>
#include <foundation/detect/platform.h>
#include <foundation/detect/supported_standards.h>

#endif // _FOUNDATION_DETECT_H_
