// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DETECT_COMPILER_H_
#define _FOUNDATION_DETECT_COMPILER_H_

// Tries to detect the compiler based on various preprocessor definitions.

// Microsoft Visual Studio C/C++:
#if defined(_MSC_VER)
  #define FOUNDATION_COMPILER_MSVC _MSC_VER
  #define MICROSOFT_VISUAL_STUDIO_2012 1700
  #define MICROSOFT_VISUAL_STUDIO_2010 1600
  #define MICROSOFT_VISUAL_STUDIO_2008 1500
  #define MICROSOFT_VISUAL_STUDIO_2005 1400
  #define MICROSOFT_VISUAL_STUDIO_2003 1310
// Clang / LLVM:
#elif defined(__clang__)
  #define FOUNDATION_COMPILER_CLANG \
    ((__clang_major__ * 100) + (__clang_minor__ * 10) + (__clang_patchlevel__ * 1))
// GCC:
#elif (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
  #if (__GNUC__ >= 3)
    #define FOUNDATION_COMPILER_GCC \
      ((__GNUC__ * 100) + (__GNUC_MINOR__ * 10) + (__GNUC_PATCHLEVEL__ * 1))
  #else
    #define FOUNDATION_COMPILER_GCC \
      ((__GNUC__ * 100) + (__GNUC_MINOR__ * 10)
  #endif
// Intel C/C++ Compiler:
#elif defined(__ICC) || defined(__INTEL_COMPILER)
  #define FOUNDATION_COMPILER_ICC __INTEL_COMPILER
#else
  #error ("Unknown or unsupported C/C++ compiler!")
#endif

#endif // _FOUNDATION_DETECT_COMPILER_H_
