// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_CONCURRENCY_MUTEX_H_
#define _FOUNDATION_SYSTEM_CONCURRENCY_MUTEX_H_

// Provides a cross-platform wrapper around a mutex (or critical section).

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  class FOUNDATION_EXPORT Mutex final {
    __foundation_trait(Mutex, non_copyable);

    private:
      friend class ConditionVariable;

    public:
      Mutex()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        InitializeCriticalSection(&_cs);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      ~Mutex()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        DeleteCriticalSection(&_cs);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

    public:
      // Locks this mutex (waits if held by another thread).
      FOUNDATION_INLINE void lock()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        EnterCriticalSection(&_cs);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      // Trys to lock this mutex (returns false if held by another thread).
      FOUNDATION_INLINE bool try_lock()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        return (TryEnterCriticalSection(&_cs) == TRUE);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      // Unlocks this mutex.
      FOUNDATION_INLINE void unlock()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        LeaveCriticalSection(&_cs);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

    public:
      // Locks a mutex until destructed (scope exit).
      class ScopedLock final {
        __foundation_trait(ScopedLock, non_copyable);

        public:
          FOUNDATION_INLINE ScopedLock( Mutex& mutex )
            : _mutex(mutex)
          { _mutex.lock(); }

          FOUNDATION_INLINE ~ScopedLock()
          { _mutex.unlock(); }

        private:
          Mutex& _mutex;
      };

    private:
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      CRITICAL_SECTION _cs;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
  };
} // foundation

#endif // _FOUNDATION_SYSTEM_CONCURRENCY_MUTEX_H_
