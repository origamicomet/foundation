// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_MUTEX_H_
#define _FOUNDATION_MUTEX_H_

// A wrapper around platform specific mutexes.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/assert.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#elif 
#endif

namespace foundation {
  class ConditionVariable;
  class FOUNDATION_EXPORT Mutex {
    FOUNDATION_NON_COPYABLE(Mutex);

    private:
      friend class ConditionVariable;

    public:
      FOUNDATION_INLINE Mutex()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        InitializeCriticalSection(&_cs);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      FOUNDATION_INLINE ~Mutex()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        DeleteCriticalSection(&_cs);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

    public:
      // Locks this mutex (waits until unlocked if already locked).
      FOUNDATION_INLINE void lock()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        EnterCriticalSection(&_cs);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      // Trys to lock this mutex (doesn't wait if already locked).
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

    private:
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        CRITICAL_SECTION _cs;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
  };

  // Locks a mutex until destructed (scope exit).
  class ScopedMutexLock {
    FOUNDATION_NON_COPYABLE(ScopedMutexLock);

    public:
      ScopedMutexLock( Mutex& mutex )
        : _mutex(mutex)
      {
        _mutex.lock();
      }

      ~ScopedMutexLock()
      {
        _mutex.unlock();
      }

    private:
      Mutex& _mutex;
  };
} // foundation

#endif // _FOUNDATION_MUTEX_H_