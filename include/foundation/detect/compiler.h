#ifndef _FOUNDATION_DETECT_COMPILER_H_
#define _FOUNDATION_DETECT_COMPILER_H_

#if defined(_MSC_VER)
  #define FOUNDATION_COMPILER_MSVC 1
#elif defined(__clang__)
  #define FOUNDATION_CLANG_BUILD 1
#elif defined(__MINGW32__)
  #define FOUNDATION_COMPILER_MINGW32 1
  #define FOUNDATION_COMPILER_GCC 1
#elif defined(__CYGWIN32__)
  #define FOUNDATION_COMPILER_CYGWIN 1
  #define FOUNDATION_COMPILER_GCC 1
#elif defined(__INTEL_COMPILER ) || defined(__ICC)
  #define FOUNDATION_COMPILER_ICC 1
#else
  #error Unknown or unsupported compiler.
#endif

#endif // _FOUNDATION_DETECT_COMPILER_H_
