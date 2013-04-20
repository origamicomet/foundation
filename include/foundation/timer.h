// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_TIMER_H_
#define _FOUNDATION_TIMER_H_

// A cross-platform timer that allows for relative timing.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#elif 
#endif

namespace foundation {
  class FOUNDATION_EXPORT Timer {
    FOUNDATION_NON_COPYABLE(Timer);

    public:
      Timer();
      ~Timer();

    public:
      // Resets the timer to zero.
      void reset();

      // The number of elapsed miliseconds.
      uint64_t elapsed();

    private:
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
      LARGE_INTEGER _start;
      LARGE_INTEGER _tick;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
  };
} // foundation

#endif // _FOUNDATION_TIMER_H_