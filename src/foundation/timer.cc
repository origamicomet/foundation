// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/timer.h>

namespace foundation {
#if defined(FOUNDATION_PLATFORM_WINDOWS)
  static const LARGE_INTEGER& frequency() {
    static LARGE_INTEGER freq;
    static const BOOL has_freq = QueryPerformanceFrequency(&freq);
    assert(has_freq);
    return freq;
  }

  static LARGE_INTEGER count() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return count;
  }
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

  Timer::Timer()
  {
    reset();
  }

  Timer::~Timer()
  {
  }

  void Timer::reset()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    _start = _tick = count();
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  uint64_t Timer::elapsed()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    _tick = count();
    return ((_tick.QuadPart - _start.QuadPart) / (frequency().QuadPart / 1000));
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }
} // foundation