// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_CONCURRENCY_THREAD_H_
#define _FOUNDATION_SYSTEM_CONCURRENCY_THREAD_H_

// Provides a cross-platform wrapper around thread managment.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  class FOUNDATION_EXPORT Thread final {
    __foundation_trait(Thread, non_copyable);

    public:
      typedef uint32_t Return;

    public:
      typedef unsigned Affinity;

      // The default affinity of a thread. Scheduled for any core.
      static const Affinity default_affinity = 0xFFFFFFFFFFFFFFFFull;

    public:
      typedef Return (*Entry)(
        Thread& thread,
        void* closure );

    private:
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      #if defined(FOUNDATION_COMPILER_MSVC)
        static unsigned __stdcall __stub(
          void* thread );
      #else
        static DWORD __stdcall __stub(
          void* thread );
      #endif
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif

    public:
      Thread(
        Entry entry_point,
        void* closure = nullptr );

      ~Thread();

    public:
      // Unsuspends the thread.
      void run();

      // Waits for this thread to exit, returns false if the thread already exited.
      bool join(
        Thread::Return& returned );

      // Doesn't wait for the thread to exit, but releases the underlying system
      // resources. Subsequent calls to Thread::join will fail.
      void detach();

    public:
      FOUNDATION_INLINE Affinity affinity() const
      { return _affinity; }

      // Tries to set the affinity of the thread. Use affinity() to check.
      void set_affinity( Affinity affinity );

    private:
      Entry _entry_point;
      void* _closure;
      Affinity _affinity;

    private:
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      HANDLE _sys_handle;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
  };
} // foundation

#endif // _FOUNDATION_SYSTEM_CONCURRENCY_THREAD_H_
