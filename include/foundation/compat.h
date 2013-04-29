// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_COMPAT_H_
#define _FOUNDATION_COMPAT_H_

// Tries to level the playing field across different platforms and compilers:
//  * Introduces stdint and inttype definitions while working around 'broken'
//    compilers like Microsoft Visual C/C++.
//  * Aliases a bunch of safe variants of stdlib functions like vsnprintf. Also
//    aliases platform and compiler specific extensions and keywords (like
//    dllexport, abstract, override, sealed, et cetra). Furthermore, aliases
//    C++11 keywords and features like nullptr and alignof.
//  * Exposes uniform bit manipulation helpers (like clz, ctz, swaps, et cetra).
//  * Aliases compile time type trait helpers (like align_of, is_pod, et cetra).

#include <foundation/detect.h>

// Hint to the compiler to inline a function aggressively as possible.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_INLINE __forceinline
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
  #define FOUNDATION_INLINE __attribute__ ((always_inline))
#else
  #warning ("No inline forcing function attribute is supported, thus performance might be degraded!")
  #define FOUNDATION_INLINE inline
#endif

// Hint to the compiler to never inline a function.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_NEVER_INLINE __declspec(noinline)
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
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
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
  #define FOUNDATION_DEPRECATED __attribute__ ((deprecated))
#else
  #warning ("No deprecated function attribute is supported, thus deprecated function usage does not raise a warning!")
  #define FOUNDATION_DEPRECATED
#endif

// Hint to the compiler that no other pointer aliases to this pointer.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_RESTRICT __restrict
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
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
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
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
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
  #define FOUNDATION_TREAD_LOCAL_STORAGE __thread
#else
  #error ("No Thread Local Storage attribute is supported!")
#endif

// The compiler won't generate a prologue and epilogue for a function.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_NAKED __declspec(naked)
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
  #define FOUNDATION_NAKED __attribute__ ((naked))
#else
  #error ("Compiler doesn't support naked functions!")
#endif

// Modifies a functions calling convention to determine who handles stack
// clean-up post function call.
#if defined(FOUNDATION_COMPILER_MSVC)
  #define FOUNDATION_STDCALL __stdcall
  #define FOUNDATION_CDECL __cdecl
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
  #define FOUNDATION_STDCALL __attribute__ ((stdcall))
  #define FOUNDATION_CDECL __attribute__ ((cdecl))
#else
  #error ("No calling convention function attribute is supported!")
#endif

// Alias C++11 some useful keywords if not supported.
#if __cplusplus >= 201103L
  #define FOUNDATION_OVERRIDE override
  #define FOUNDATION_FINAL final
#elif defined(FOUNDATION_COMPILER_MSVC)
  #define nullptr NULL
  #define FOUNDATION_OVERRIDE override
  #define FOUNDATION_FINAL final
#else
  #define nullptr NULL
  #define FOUNDATION_OVERRIDE
  #define FOUNDATION_FINAL
#endif

// Provide a hacky implementation of C++11's alignof if not supported.
#if __cplusplus <= 201103L
  #include <stddef.h>

  template <class _Type>
  struct __foundation_align_of { char __0; _Type __1; };

  #define alignof( _Type ) \
    (offsetof(__foundation_align_of<_Type>, __1))
#endif

#define __STDC_LIMIT_MACROS
#define __STDC_FORMAT_MACROS

// Microsoft's Visual C/C++ requires a work around for stdint and inttypes.
#if defined(FOUNDATION_COMPILER_MSVC)
  #include <foundation/compat/msvc_stdint.h>
  #include <foundation/compat/msvc_inttypes.h>
#else
  #include <stdint.h>
  #include <inttypes.h>
#endif

// Fix up _alloca vs alloca.
#if defined(FOUNDATION_COMPILER_MSVC)
  #include <malloc.h>

  #ifdef alloca
    #undef alloca
  #endif

  #define alloca( _NumBytes ) \
    _alloca(_NumBytes)
#elif defined(FOUNDATION_PLATFORM_POSIX)
  #include <alloca.h>
#else
  #error ("Platform and/or compiler does not support alloca!")
#endif

// Alias intrinsics.
#if defined(FOUNDATION_COMPILER_MSVC)
  #include <intrin.h>
  #include <stdlib.h>
  #include <stdlib.h>

  static uint32_t __inline __builtin_clz( uint32_t x ) {
    uint32_t r = 0;
    _BitScanForward((unsigned long*)&r, x);
    return r;
  }

  static uint32_t __inline __builtin_ctz( uint32_t x ) {
    uint32_t r = 0;
    _BitScanReverse((unsigned long*)&r, x);
    return r;
  }

  #define __builtin_bswap16( _Word ) \
    _byteswap_ushort(_Word)

  #define __builtin_bswap32( _Dword ) \
    _byteswap_ulong(_Dword)

  #define __builtin_bswap64( _Qword ) \
    _byteswap_uint64(_Qword)

  // TODO: Create a proper wrapper (this doesn't exactly match).
  #define snprintf _snprintf
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
#else
  #error ("Compiler does not support important intrinsics!")
#endif

#if defined(FOUNDATION_COMPILER_MSVC)
  #if (_MSC_VER >= 1600) // Microsoft Visual Studio 2010, or greater:
    #include <foundation/compat/c++11_type_traits.h>
  #else
    #include <foundation/compat/c++03_type_traits.h>
  #endif
#elif defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_CLANG)
  #include <foundation/compat/c++11_type_traits.h>
#else
  #error ("Type traits are not supported!")
#endif

#endif // _FOUNDATION_COMPAT_H_