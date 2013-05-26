// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/timer.h>

namespace foundation {
  Timer::Timer()
  { reset(); }

  Timer::Timer(
    const Timer& timer
  ) : _epoch(timer._epoch)
  {}

  Timer& Timer::operator= (
    const Timer& timer )
  { _epoch = timer._epoch; return *this; }

  Timer::~Timer()
  {}

  void Timer::reset()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    _epoch = counter.QuadPart;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  static LARGE_INTEGER frequency() {
    static LARGE_INTEGER freq;
    static const bool _ = QueryPerformanceFrequency(&freq);
    return freq;
  }
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

  uint64_t Timer::miliseconds() const
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return (counter.QuadPart - _epoch) / (frequency().QuadPart / 1000);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }
} // foundation
