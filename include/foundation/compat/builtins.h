// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_COMPAT_BUILTINS_H_
#define _FOUNDATION_COMPAT_BUILTINS_H_

// Aliases (and provides fallbacks) for built-in functions and intrinsics.
// TODO: _clear87, _clearfp, _control87, _controlfp, _fpreset, _isnan,
//       _set_controlfp, _status87, _statusfp

#include <foundation/detect.h>
#include <foundation/compat/stdint.h>
#include <foundation/compat/inttypes.h>

#if defined(FOUNDATION_COMPILER_MSVC)
  #include <malloc.h>
  #if defined(alloca)
    #undef alloca
  #endif // defined(alloca)
  #define alloca _alloca
#else
  #include <alloca.h>
#endif

#if defined(FOUNDATION_COMPILER_MSVC)
  #define _Exit( _Return ) \
    _exit(_Return)
#endif

#if defined(FOUNDATION_COMPILER_MSVC)
  #define WIN32_LEAN_AND_MEAN
  #include <signal.h>
  #include <Windows.h>
  #include <intrin.h>
  #include <mmintrin.h>
  #include <xmmintrin.h>

  namespace foundation {
    #pragma intrinsic(_InterlockedExchangeAdd)
    static __forceinline int32_t __sync_fetch_and_add( volatile int32_t* ptr, int32_t val )
    { return _InterlockedExchangeAdd((volatile long*)ptr, (long)val); }
    static __forceinline int32_t __sync_fetch_and_sub( volatile int32_t* ptr, int32_t val )
    { return _InterlockedExchangeAdd((volatile long*)ptr, (long)-val); }
  }

  #define __sync_fetch_and_add( _Pointer, _Value ) \
    foundation::__sync_fetch_and_add(_Pointer, _Value)

  #define __sync_fetch_and_sub( _Pointer, _Value ) \
    foundation::__sync_fetch_and_sub(_Pointer, _Value)

  namespace foundation {
    #pragma intrinsic(_InterlockedOr)
    static __forceinline int32_t __sync_fetch_and_or( volatile int32_t* value, int32_t mask )
    { return _InterlockedOr((volatile long*)value, (long)mask); }
  }

  #define __sync_fetch_and_or( _Value, _Mask ) \
    foundation::__sync_fetch_and_or(_Value, _Mask)

  namespace foundation {
    #pragma intrinsic(_InterlockedXor)
    static __forceinline int32_t __sync_fetch_and_xor( volatile int32_t* value, int32_t mask )
    { return _InterlockedXor((volatile long*)value, (long)mask); }
  }

  #define __sync_fetch_and_xor( _Value, _Mask ) \
    foundation::__sync_fetch_and_xor(_Value, _Mask)

  namespace foundation {
    #pragma intrinsic(_InterlockedAnd)
    static __forceinline int32_t __sync_fetch_and_and( volatile int32_t* value, int32_t mask )
    { return _InterlockedAnd((volatile long*)value, (long)mask); }
    static __forceinline int32_t __sync_fetch_and_nand( volatile int32_t* value, int32_t mask )
    { return _InterlockedAnd((volatile long*)value, (long)~mask); }
  }

  #define __sync_fetch_and_and( _Value, _Mask ) \
    foundation::__sync_fetch_and_and(_Value, _Mask)

  #define __sync_fetch_and_nand( _Value, _Mask ) \
    foundation::__sync_fetch_and_nand(_Value, _Mask)

  namespace foundation {
    #pragma intrinsic(_InterlockedCompareExchange)
    static __forceinline bool __sync_bool_compare_and_swap( volatile int32_t* ptr, int32_t compare, int32_t swap )
    { return (_InterlockedCompareExchange((volatile long*)ptr, (long)swap, (long)compare) == compare); }
    static __forceinline int32_t __sync_val_compare_and_swap( volatile int32_t* ptr, int32_t compare, int32_t swap )
    { return _InterlockedCompareExchange((volatile long*)ptr, (long)swap, (long)compare); }
  }

  #define __sync_bool_compare_and_swap( _Pointer, _Compare, _Swap ) \
    foundation::__sync_bool_compare_and_swap(_Pointer, _Compare, _Swap)

  #define __sync_val_compare_and_swap( _Pointer, _Compare, _Swap ) \
    foundation::__sync_val_compare_and_swap(_Pointer, _Compare, _Swap)

  #define __builtin_expect( _Expression, _Result ) \
    ((_Expression) == (_Result))

  #define __builtin_trap() \
    do { ::raise(SIGABRT); } while (0, 0)

  #define __builtin_unreachable() \
    __builtin_trap()

  namespace foundation {
    static __forceinline void __builtin___clear_cache( char* begin, char* end ) {
      ::FlushInstructionCache(
        GetCurrentProcess(), begin,
        (SIZE_T)(end - begin - ((end == begin) ? 0 : 1)));
    }
  } // foundation

  #define __builtin___clear_cache( _Begin, _End ) \
    do { foundation::__builtin___clear_cache((char*)_Begin, (char*)_End); } while (0, 0)

  namespace foundation {
    static __forceinline void __builtin_prefetch0( char* addr )
    { _mm_prefetch(addr, _MM_HINT_NTA); }

    static __forceinline void __builtin_prefetch1( char* addr )
    { _mm_prefetch(addr, _MM_HINT_T0); }

    static __forceinline void __builtin_prefetch2( char* addr )
    { _mm_prefetch(addr, _MM_HINT_T1); }

    static __forceinline void __builtin_prefetch3( char* addr )
    { _mm_prefetch(addr, _MM_HINT_T2); }
  } // foundation

  #define __builtin_prefetch( _Address, _ReadWrite, _Locality ) \
    do { foundation::__builtin_prefetch##_Locality((char*)_Address); } while (0, 0)

  namespace foundation {
    static __forceinline uint32_t __builtin_clz( uint32_t x ) {
      unsigned long r = 0;
      _BitScanReverse(&r, x);
      return (32 - r);
    }
  } // foundation

  #define __builtin_clz( _X ) \
    foundation::__builtin_clz(_X)

  namespace foundation {
    static __forceinline uint32_t __builtin_ctz( uint32_t x ) {
      unsigned long r = 0;
      _BitScanForward(&r, x);
      return r;
    }
  } // foundation

  #define __builtin_ctz( _X ) \
    foundation::__builtin_ctz(_X)

  #define __builtin_bswap16( _Short ) \
    _byteswap_ushort(_Short)

  #define __builtin_bswap32( _Long ) \
    _byteswap_ulong(_Long)

  #define __builtin_bswap64( _LongLong ) \
    _byteswap_uint64(_LongLong)

  #define __builtin_yield() \
    __yield()

  #if defined(FOUNDATION_ARCHITECTURE_X86_64) || defined(FOUNDATION_ARCHITECTURE_X86)
    #define __builtin_rdtsc() \
      __rdtsc()

    #define __builtin_cpuid( _CpuInfo, _InfoType ) \
      do { __cpuid(_CpuInfo, _InfoType); } while (0, 0)
  #else
    namespace foundation {
      static __inline__ uint64_t __builtin_rdtsc() {
        return 0;
      }
    } // foundation

    #define __builtin_rdtsc() \
      foundation::__builtin_rdtsc()

    #define __builtin_cpuid( _CpuInfo, _InfoType ) \
      __builtin_trap()
  #endif
#elif defined(FOUNDATION_COMPILER_CLANG) || defined(FOUNDATION_COMPILER_GCC) || defined(FOUNDATION_COMPILER_ICC)
  #include <mmintrin.h>

  #define __builtin_yield() \
    _mm_pause()

  namespace foundation {
    static __inline__ uint64_t __builtin_rdtsc() {
    #if defined(FOUNDATION_ARCHITECTURE_X86_64)
      unsigned hi, lo;
      __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
      return ((uint64_t)lo) | (((uint64_t)hi) << 32);
    #elif defined(FOUNDATION_ARCHITECTURE_X86)
      uint64_t rdtsc;
      __asm__ volatile (".byte 0x0f, 0x31" : "=A" (rdtsc));
      return rdtsc;
    #else
      return 0;
    #endif
    }
  } // foundation

  #define __builtin_rdtsc() \
    foundation::__builtin_rdtsc()

  namespace foundation {
    static __inline__ void __builtin_cpuid( int cpu_info[4], int info_type ) {
    #if defined(FOUNDATION_ARCHITECTURE_X86_64) || defined(FOUNDATION_ARCHITECTURE_X86)
      __asm__ __volatile__ (
        "cpuid":
        "=a" (cpu_info[0]),
        "=b" (cpu_info[1]),
        "=c" (cpu_info[2]),
        "=d" (cpu_info[3]) :
        "a" (info_type)
      );
    #else
      __builtin_trap()
    #endif
    }
  } // foundation

  #define __builtin_cpuid( _CpuInfo, _InfoType ) \
    do { foundation::__builtin_cpuid(_CpuInfo, _InfoType); } while (0, 0)
#else
  #error ("Unknown or unsupported compiler!")
#endif

#endif // _FOUNDATION_COMPAT_BUILTINS_H_
