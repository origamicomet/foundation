/* ========================================================================== */
/*                                                                            */
/* This file is part of Foundation.                                           */
/*                                                                            */
/* Author(s):                                                                 */
/*                                                                            */
/*   Michael Williams <devbug@bitbyte.ca>                                     */
/*                                                                            */
/* This is free and unencumbered software released into the public domain.    */
/*                                                                            */
/* Anyone is free to copy, modify, publish, use, compile, sell, or distribute */
/* this software, either in source code form or as a compiled binary, for any */
/* purpose, commercial or non-commercial, and by any means.                   */
/*                                                                            */
/* In jurisdictions that recognize copyright laws, the author or authors of   */
/* this software dedicate any and all copyright interest in the software to   */
/* the public domain. We make this dedication for the benefit of the public   */
/* large and to the detriment of our heirs and successors. We intend this     */
/* dedication to be an overt act of relinquishment in perpetuity of all       */
/* present and future rights to this software under copyright law.            */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   */
/* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR      */
/* OTHER DEALINGS IN THE SOFTWARE.                                            */
/*                                                                            */
/* For more information, please refer to <http://unlicense.org/>              */
/*                                                                            */
/* ========================================================================== */
 #  include <foundation/monotonic_clock.h>
/* ========================================================================== */

#include <foundation/allocator.h>
#include <foundation/assert.h>
#include <foundation/detect/compiler.h>
#include <foundation/detect/architecture.h>
#include <foundation/detect/platform.h>

#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  static uint64_t __counts_per_sec;
  static void __perf_freq_ctor_() {
    LARGE_INTEGER perf_freq;
    QueryPerformanceFrequency(&perf_freq);
    __counts_per_sec = perf_freq.QuadPart; }
  #if (FND_COMPILER == FND_COMPILER_MSVC)
    static void __cdecl __perf_freq_ctor()
    { __perf_freq_ctor_(); }
    #pragma section(".CRT$XCU", read)
    __declspec(allocate(".CRT$XCU")) void (__cdecl*__perf_freq_ctor__)() = &__perf_freq_ctor;
  #elif (FND_COMPILER == FND_COMPILER_GCC) || \
        (FND_COMPILER == FND_COMPILER_CLANG)
    static void __attribute__((constructor)) __perf_freq_ctor()
    { __perf_freq_ctor_(); }
  #else
    #error ("Unknown or unsupported compiler.")
  #endif
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX) || \
      (FND_PLATFORM == FND_PLATFORM_IOS)
  #include <unistd.h>
  #include <mach/mach_time.h>
  static mach_timebase_info_data_t __mach_timebase_info;
  static void __attribute__((constructor)) __mach_timebase_info_ctor()
  { mach_timebase_info(&__mach_timebase_info); }
#elif (FND_PLATFORM == FND_PLATFORM_LINUX)   || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID)
  #include <unistd.h>
  #include <time.h>
#else
  #error ("Unknown or unsupported platform.")
#endif

/* ========================================================================== */
/*  C (fnd_monotonic_clock_t):                                                */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */

struct fnd_monotonic_clock {
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  LARGE_INTEGER epoch;
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX)  || \
      (FND_PLATFORM == FND_PLATFORM_IOS)     || \
      (FND_PLATFORM == FND_PLATFORM_LINUX)   || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID)
  uint64_t epoch;
#endif
};

/* ========================================================================== */

uint64_t fnd_monotonic_clock_secs(const fnd_monotonic_clock_t *mc) {
  fnd_assert(debug, mc != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return ((now.QuadPart - mc->epoch.QuadPart) / __counts_per_sec);
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX)  || \
      (FND_PLATFORM == FND_PLATFORM_IOS)     || \
      (FND_PLATFORM == FND_PLATFORM_LINUX)   || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID)
  return (fnd_monotonic_clock_nsecs(mc) / UINT64_C(1000000000));
#endif
}

uint64_t fnd_monotonic_clock_msecs(const fnd_monotonic_clock_t *mc) {
  fnd_assert(debug, mc != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (((now.QuadPart - mc->epoch.QuadPart) * UINT64_C(1000)) / __counts_per_sec);
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX)  || \
      (FND_PLATFORM == FND_PLATFORM_IOS)     || \
      (FND_PLATFORM == FND_PLATFORM_LINUX)   || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID)
  return (fnd_monotonic_clock_nsecs(mc) / UINT64_C(1000000));
#endif
}

uint64_t fnd_monotonic_clock_usecs(const fnd_monotonic_clock_t *mc) {
  fnd_assert(debug, mc != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (((now.QuadPart - mc->epoch.QuadPart) * UINT64_C(1000000)) / __counts_per_sec);
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX)  || \
      (FND_PLATFORM == FND_PLATFORM_IOS)     || \
      (FND_PLATFORM == FND_PLATFORM_LINUX)   || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID)
  return (fnd_monotonic_clock_nsecs(mc) / UINT64_C(1000));
#endif
}

uint64_t fnd_monotonic_clock_nsecs(const fnd_monotonic_clock_t *mc) {
  fnd_assert(debug, mc != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (((now.QuadPart - mc->epoch.QuadPart) * UINT64_C(1000000000)) / __counts_per_sec);
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX) || \
      (FND_PLATFORM == FND_PLATFORM_IOS)
  return (((mach_absolute_time() - mc->epoch) * __mach_timebase_info.numer) / __mach_timebase_info.denom);
#elif (FND_PLATFORM == FND_PLATFORM_LINUX) || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID)
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ((ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec) - mc->epoch);
#endif
}

/* ========================================================================== */

fnd_monotonic_clock_t *fnd_monotonic_clock_create(void) {
  fnd_monotonic_clock_t *mc = (fnd_monotonic_clock_t *)
    fnd_allocator_alloc(
      fnd_heap(),
      sizeof(fnd_monotonic_clock_t),
      fnd_alignof(fnd_monotonic_clock_t));
  fnd_monotonic_clock_reset(mc);
  return mc;
}

void fnd_monotonic_clock_reset(fnd_monotonic_clock_t *mc) {
  fnd_assert(debug, mc != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  QueryPerformanceCounter(&mc->epoch);
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX) || \
      (FND_PLATFORM == FND_PLATFORM_IOS)
  mc->epoch = mach_absolute_time();
#elif (FND_PLATFORM == FND_PLATFORM_LINUX) || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID)
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  mc->epoch = ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec;
#endif
}

void fnd_monotonic_clock_destroy(fnd_monotonic_clock_t *mc) {
  fnd_assert(debug, mc != NULL);
  fnd_allocator_free(fnd_heap(), (void *)mc);
}

/* ========================================================================== */

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::clock::Monotonic):                                       */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
namespace clock {
  /* ======================================================================== */

  // Monotonic::Monotonic() {
  // }
  //
  // Monotonic::Monotonic(const Monotonic &) {
  // }
  //
  // Monotonic &Monotonic::operator= (const Monotonic &) {
  // }
  //
  // Monotonic::~Monotonic() {
  // }

  /* ======================================================================== */

  Monotonic *Monotonic::recover_(::fnd_monotonic_clock_t *mc) {
    fnd_assert(debug, mc != NULL);
    return ((Monotonic *)mc);
  }

  ::fnd_monotonic_clock_t *Monotonic::lose_() {
    return ((::fnd_monotonic_clock_t *)this);
  }

  const Monotonic *Monotonic::recover_(const ::fnd_monotonic_clock_t *mc) {
    fnd_assert(debug, mc != NULL);
    return ((const Monotonic *)mc);
  }

  const ::fnd_monotonic_clock_t *Monotonic::lose_() const {
    return ((const ::fnd_monotonic_clock_t *)this);
  }

  /* ======================================================================== */

  uint64_t Monotonic::secs() const {
    return ::fnd_monotonic_clock_secs(this->lose_());
  }

  uint64_t Monotonic::msecs() const {
    return ::fnd_monotonic_clock_msecs(this->lose_());
  }

  uint64_t Monotonic::usecs() const {
    return ::fnd_monotonic_clock_usecs(this->lose_());
  }

  uint64_t Monotonic::nsecs() const {
    return ::fnd_monotonic_clock_nsecs(this->lose_());
  }

  /* ======================================================================== */

  Monotonic *Monotonic::create() {
    return ((Monotonic *)::fnd_monotonic_clock_create());
  }

  void Monotonic::reset() {
    fnd_monotonic_clock_reset(this->lose_());
  }

  void Monotonic::destroy() {
    fnd_monotonic_clock_destroy(this->lose_());
  }

  /* ======================================================================== */
} /* clock */
} /* foundation */
#endif

/* ========================================================================== */
