// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/concurrency/thread.h>

#include <foundation/allocator.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #if defined(FOUNDATION_COMPILER_MSVC)
    #include <process.h>
  #endif
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #if defined(FOUNDATION_COMPILER_MSVC)
    namespace foundation {
      unsigned __stdcall Thread::__stub(
        void* copy )
      {
        Thread::Copy* copy_ = ((Thread::Copy*)copy);
        Thread::Copy copy__ = *copy_;
        make_delete(Copy, Allocators::heap(), copy_);
        _endthreadex((unsigned)copy__.entry_point(copy__.closure));
        __builtin_unreachable();
        return 0;
      }
    } // foundation
  #else
    namespace foundation {
      DWORD __stdcall Thread::__stub(
        void* copy )
      {
        Thread::Copy* copy_ = ((Thread::Copy*)copy);
        Thread::Copy copy__ = *copy_;
        make_delete(Copy, Allocators::heap(), copy_);
        ExitThread((DWORD)copy__.entry_point(copy__.closure));
        __builtin_unreachable();
        return 0;
      }
    } // foundation
  #endif
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  Thread::Thread(
    Entry entry_point,
    void* closure
  ) : _entry_point(entry_point)
    , _closure(closure)
    , _affinity(Thread::default_affinity)
    , _sys_handle(nullptr)
  {
    // If the thread is allocated on the stack it might be destructed/destroyed
    // prior to the stub calling the entry point.  Thus a copy is required.
    Copy* copy = make_new(Copy, Allocators::heap())();
    copy->entry_point = entry_point;
    copy->closure = closure;
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    #if defined(FOUNDATION_COMPILER_MSVC)
      _sys_handle = (HANDLE)_beginthreadex(
        NULL, 0, &Thread::__stub, (void*)copy, CREATE_SUSPENDED, NULL);
    #else
      _sys_handle = (HANDLE)CreateThread(
        NULL, 0, &Thread::__stub, (void*)copy, CREATE_SUSPENDED, NULL);
    #endif
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  Thread::~Thread()
  {
    detach();
  }

  void Thread::run()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    if (!_sys_handle)
      return;
    ResumeThread(_sys_handle);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  bool Thread::join( Thread::Return& returned )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    if (!_sys_handle)
      return false;
    DWORD ret = 0;
    WaitForSingleObject(_sys_handle, INFINITE);
    GetExitCodeThread(_sys_handle, &ret);
    CloseHandle(_sys_handle);
    _sys_handle = nullptr;
    returned = (Thread::Return)ret;
    return true;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  void Thread::detach()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    if (!_sys_handle)
      return;
    ResumeThread(_sys_handle);
    CloseHandle(_sys_handle);
    _sys_handle = nullptr;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }

  void Thread::set_affinity( Affinity affinity )
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    if (!_sys_handle)
      return;
    if ((SuspendThread(_sys_handle)) == ((DWORD)-1))
      return;
    if (SetThreadAffinityMask(_sys_handle, (DWORD_PTR)&affinity) == 0)
      return;
    ResumeThread(_sys_handle);
    _affinity = affinity;
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }
} // foundation
