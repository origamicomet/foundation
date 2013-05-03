// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_COMPAT_EXTENSIONS_H_
#define _FOUNDATION_COMPAT_EXTENSIONS_H_

// Aliases compiler specific extensions like __declspec and __attribute__,
// as well as keywords like abstract, override, sealed, etc.

#include <foundation/detect.h>

// Hint to the compiler to inline a function aggressively as possible.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_INLINE __forceinline
#elif defined(FOUNDATION_COMPILER_CLANG) || defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_ICC)
  #define FOUNDATION_INLINE __attribute__ ((always_inline))
#else
  #warning ("No inline forcing function attribute is supported, thus performance might be degraded!")
  #define FOUNDATION_INLINE inline
#endif

// Hint to the compiler to never inline a function.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_NEVER_INLINE __declspec(noinline)
#elif defined(FOUNDATION_COMPILER_CLANG) || defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_ICC)
  #define FOUNDATION_NEVER_INLINE __attribute__ ((noinline))
#else
  #warning ("No never inline forcing function attribute is supported, thus performance might be degraded!")
  #define FOUNDATION_NEVER_INLINE
#endif

// Hint to the compiler that global state is never mutated by a function.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_NO_ALIAS __declspec(noalias)
#else
  #warning ("No no-alias function attribute is supported, thus performance might be degraded!")
  #define FOUNDATION_INLINE inline
#endif

// Hint to the compiler and user that a function is deprecated and that usage
// should be limited upon usage.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_DEPRECATED __declspec(deprecated)
#elif defined(FOUNDATION_COMPILER_CLANG) || defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_ICC)
  #define FOUNDATION_DEPRECATED __attribute__ ((deprecated))
#else
  #warning ("No deprecated function attribute is supported, thus deprecated function usage does not raise a warning!")
  #define FOUNDATION_DEPRECATED
#endif

// Hint to the compiler that no other pointer aliases to this pointer.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_RESTRICT __restrict
#elif defined(FOUNDATION_COMPILER_CLANG) || defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_ICC)
  #define FOUNDATION_RESTRICT __restrict
#else
  #warning ("No restrict attribute is supported, thus performance might be degraded!")
  #define FOUNDATION_RESTRICT
#endif

// Hints to the compiler to export a function if a DLL.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_DYNAMIC_EXPORT __declspec(dllexport)
  #define FOUNDATION_DYNAMIC_IMPORT __declspec(dllimport)
#else
  #define FOUNDATION_DYNAMIC_EXPORT
  #define FOUNDATION_DYNAMIC_IMPORT
#endif

// Aligns a type onto an |_Alignment| bits boundry.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_ALIGNED_TYPE( _Type, _Alignment ) \
    __declspec(align(_Alignment)) _Type
#elif defined(FOUNDATION_COMPILER_CLANG) || defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_ICC)
  #define FOUNDATION_ALIGNED_TYPE( _Type, _Alignment ) \
    __attribute__ ((aligned(_Alignment))) _Type
#else
  #warning ("No alignment attribute is supported, thus performance might be degraded!")
  #define FOUNDATION_ALIGNED_TYPE( _Type, _Alignment ) \
    _Type
#endif

// Stores a variable per-thread rather than globally.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_THREAD_LOCAL_STORAGE __declspec(thread)
#elif defined(FOUNDATION_COMPILER_CLANG) || defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_ICC)
  #define FOUNDATION_TREAD_LOCAL_STORAGE __thread
#else
  #error ("No Thread-Local Storage attribute is supported!")
#endif

// The compiler won't generate a prologue and epilogue for a function.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_NAKED __declspec(naked)
#elif defined(FOUNDATION_COMPILER_CLANG) || defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_ICC)
  #define FOUNDATION_NAKED __attribute__ ((naked))
#else
  #error ("Compiler doesn't support naked functions!")
#endif

// Modifies a functions calling convention to determine who handles stack
// clean-up post function call.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_STDCALL __stdcall
  #define FOUNDATION_CDECL __cdecl
#elif defined(FOUNDATION_COMPILER_CLANG) || defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_ICC)
  #define FOUNDATION_STDCALL __attribute__ ((stdcall))
  #define FOUNDATION_CDECL __attribute__ ((cdecl))
#else
  #error ("No calling convention function attribute is supported!")
#endif

// Disable C4505: nonstandard extension used: override specifier 'keyword'
// Due to the override, sealed, etc. aliases.
#if defined(FOUNDATION_COMPILER_MSVC)
  #pragma warning(disable:4481) 
#endif

// Sanity checks that a function is overriding a virtual function.
#if (__cplusplus < 201103L) && (FOUNDATION_COMPILER_MSVC < MICROSOFT_VISUAL_STUDIO_2005)
  #define override
#endif

// Prevents the inheritance of a class or struct, or override of a virtual function.
#if (__cplusplus < 201103L)
  #if (FOUNDATION_COMPILER_MSVC >= MICROSOFT_VISUAL_STUDIO_2005) && (FOUNDATION_COMPILER_MSVC < MICROSOFT_VISUAL_STUDIO_2012)
    #define final sealed
  #else
    #define final
  #endif
#endif

// Prevents the use but not the inheritance of a class or struct.
#if (FOUNDATION_COMPILER_MSVC < MICROSOFT_VISUAL_STUDIO_2005)
  #define abstract
#endif

// Alias nullptr to NULL if not supported.
#if !defined(FOUNDATION_COMPILER_SUPPORTS_NULLPTR)
  #if (FOUNDATION_COMPILER_MSVC >= MICROSOFT_VISUAL_STUDIO_2010)
    #define nullptr __nullptr
  #else
    #define nullptr NULL
  #endif
#endif

#endif // _FOUNDATION_COMPAT_EXTENSIONS_H_
