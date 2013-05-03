// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_CONCURRENCY_CONDITION_VARIABLE_H_
#define _FOUNDATION_SYSTEM_CONCURRENCY_CONDITION_VARIABLE_H_

// Provides a cross-platform wrapper around a conditon variable.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/system/concurrency/mutex.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  class FOUNDATION_EXPORT ConditionVariable final {
    __foundation_trait(ConditionVariable, non_copyable);

    public:
      ConditionVariable()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        InitializeConditionVariable(&_cv);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      ~ConditionVariable()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

    public:
      // Waits on this condition variable indefinitely.
      FOUNDATION_INLINE bool wait( Mutex& mutex )
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        return (SleepConditionVariableCS(&_cv, &mutex._cs, INFINITE) != 0);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      // Waits on this condition variable until signaled or |miliseconds| elapsed.
      FOUNDATION_INLINE bool wait( Mutex& mutex, uint32_t miliseconds )
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        return (SleepConditionVariableCS(&_cv, &mutex._cs, miliseconds) != 0);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      // Signals this condition variable (wakes up one thread).
      FOUNDATION_INLINE void signal()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        WakeConditionVariable(&_cv);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      // Signals this condition variable (wakes up all threads).
      FOUNDATION_INLINE void broadcast()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        WakeAllConditionVariable(&_cv);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

    private:
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      CONDITION_VARIABLE _cv;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
  };
} // foundation

#endif // _FOUNDATION_SYSTEM_CONCURRENCY_CONDITION_VARIABLE_H_