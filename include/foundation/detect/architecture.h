#ifndef _FOUNDATION_DETECT_ARCHITECTURE_H_
#define _FOUNDATION_DETECT_ARCHITECTURE_H_

#if defined(_M_X64) || defined(__x86_64__)
  #define FOUNDATION_ARCH_X86 1
  #define FOUNDATION_ARCH_X86_64 1
  #define FOUNDATION_ARCH_64_BIT 1
  #define FOUNDATION_ARCH_LITTLE_ENDIAN 1
#elif defined(_M_IX86) || defined(__i386__)
  #define FOUNDATION_ARCH_X86 1
  #define FOUNDATION_ARCH_32_BIT 1
  #define FOUNDATION_ARCH_LITTLE_ENDIAN 1
#elif defined(__ARMEL__)
  #define FOUNDATION_ARCH_ARM 1
  #define FOUNDATION_ARCH_32_BIT 1
  #define FOUNDATION_ARCH_LITTLE_ENDIAN 1
#elif defined(__pnacl__)
  #define FOUNDATION_ARCH_32_BIT 1
#elif defined(__MIPSEL__)
  #define FOUNDATION_ARCH_MIPS 1
  #define FOUNDATION_ARCH_32_BIT 1
  #define FOUNDATION_ARCH_LITTLE_ENDIAN 1
#else
  #error Unknown or unsupported architecture.
#endif

#endif // _FOUNDATION_DETECT_ARCHITECTURE_H_
