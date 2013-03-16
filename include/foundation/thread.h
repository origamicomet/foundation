// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_THREAD_H_
#define _FOUNDATION_THREAD_H_

// A wrapper around platform specific threads.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/assert.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #include <process.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#elif 
#endif

namespace foundation {
  class FOUNDATION_EXPORT Thread {
    FOUNDATION_NON_COPYABLE(Thread);

    public:
      typedef uint32_t Affinity;
      typedef void (*Entry)( void* /* arg */ );
      static const Affinity DEFAULT_AFFINITY = 0xFFFFFFFFu;

    public:
      FOUNDATION_INLINE Thread(
        Entry entry,
        void* arg = nullptr,
        Affinity affinity = DEFAULT_AFFINITY )
        : _entry(entry)
        , _arg(arg)
      {
        assert(affinity <= 31);

      #if defined(FOUNDATION_PLATFORM_WINDOWS)
      #if defined(FOUNDATION_COMPILER_MSVC)
        _sys_handle = (HANDLE)(_beginthreadex(
          0,
          0,
          &stub,
          (void*)this,
          CREATE_SUSPENDED,
          0
        ));

        if (affinity != DEFAULT_AFFINITY)
          SetThreadAffinityMask(_sys_handle, 1 << affinity);

        ResumeThread(_sys_handle);
      #else
        #error ("Unsupported compiler and platform combination!")
      #endif
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      FOUNDATION_INLINE ~Thread()
      {
        detach();
      }

    public:
      // Waits for this thread to exit.
      FOUNDATION_INLINE void join() {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        if (!_sys_handle)
          return;

        DWORD dwExitCode = 0;
        WaitForSingleObject(_sys_handle, INFINITE);
        GetExitCodeThread(_sys_handle, &dwExitCode);
        CloseHandle(_sys_handle);

        _sys_handle = nullptr;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

      // Releases any underlying system resources.
      FOUNDATION_INLINE void detach() {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        if (!_sys_handle)
          return;

        CloseHandle(_sys_handle);

        _sys_handle = nullptr;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

    public:
      // Determines the maximum affinity level allowed.
      static Affinity maximum_affinity()
      {
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        return min((uint32_t)si.dwNumberOfProcessors, 31);
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
      }

    private:
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        static unsigned __stdcall stub( void* thread_ ) {
          Thread* thread = (Thread*)thread_;
          thread->_entry(thread->_arg);
          _endthreadex(0);
          return 0;
        }
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif

    private:
      #if defined(FOUNDATION_PLATFORM_WINDOWS)
        HANDLE _sys_handle;
        Entry _entry;
        void* _arg;
      #elif defined(FOUNDATION_PLATFORM_POSIX)
      #endif
  };
} // foundation

#endif // _FOUNDATION_THREAD_H_