// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DETECT_ARCHITECTURE_H_
#define _FOUNDATION_DETECT_ARCHITECTURE_H_

// Tries to detect the architecture and based on various preprocessor definitions.

#if defined(_M_X64) || defined(__x86_64__)
  #define FOUNDATION_ARCHITECTURE_X86 1
  #define FOUNDATION_ARCHITECTURE_X86_64 1
  #define FOUNDATION_ARCHITECTURE_64_BIT 1
  #define FOUNDATION_ARCHITECTURE_LITTLE_ENDIAN 1
#elif defined(_M_IX86) || defined(__i386__)
  #define FOUNDATION_ARCHITECTURE_X86 1
  #define FOUNDATION_ARCHITECTURE_32_BIT 1
  #define FOUNDATION_ARCHITECTURE_LITTLE_ENDIAN 1
#elif defined(__ARMEL__)
  #define FOUNDATION_ARCHITECTURE_ARM 1
  #define FOUNDATION_ARCHITECTURE_32_BIT 1
  #define FOUNDATION_ARCHITECTURE_LITTLE_ENDIAN 1
#elif defined(__pnacl__)
  #define FOUNDATION_ARCHITECTURE_32_BIT 1
  #define FOUNDATION_ARCHITECTURE_LITTLE_ENDIAN 1
#elif defined(__MIPSEL__)
  #define FOUNDATION_ARCHITECTURE_MIPS 1
  #define FOUNDATION_ARCHITECTURE_32_BIT 1
  #define FOUNDATION_ARCHITECTURE_LITTLE_ENDIAN 1
#else
  #error ("Unknown or unsupported architecture!")
#endif

#endif // _FOUNDATION_DETECT_ARCHITECTURE_H_
