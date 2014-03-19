//=== bitbyte/foundation/tier2/thread.cc =====================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier2/thread.h>

#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
    #include <process.h>
  #endif
#else
  #error ("Unknown or unsupported platform.")
#endif

namespace bitbyte {
namespace foundation {
namespace tier2 {

#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
namespace {
  struct Thread_ {
    HANDLE handle_;
  };
}
#endif

Thread::Thread() {
}

Thread::~Thread() {
}

Thread::Affinity Thread::affinity() const {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  const Thread_ *thread = (const Thread_ *)this;
  bitbyte_foundation_assert_(::SuspendThread(thread->handle_) >= 1);
  ::SuspendThread(thread->handle_);
  const DWORD_PTR mask = ((DWORD_PTR)1);
  const DWORD_PTR original_mask = ::SetThreadAffinityMask(thread->handle_, mask);
  ::SetThreadAffinityMask(thread->handle_, original_mask);
  ::ResumeThread(thread->handle_);
  return (Thread::Affinity)original_mask;
#endif
}

Thread &Thread::set_affinity(const Thread::Affinity affinity) {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Thread_ *thread = (Thread_ *)this;
  bitbyte_foundation_assert_(::SuspendThread(thread->handle_) >= 1);
  const DWORD_PTR mask = ((DWORD_PTR)affinity);
  ::SetThreadAffinityMask(thread->handle_, mask);
  ::ResumeThread(thread->handle_);
  return *this;
#endif
}

Thread &Thread::create(Thread::EntryPoint entry_point, void *up) {
  bitbyte_foundation_assert(debug, entry_point != NULL);
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  struct EntryPoint_ {
    Thread::EntryPoint entry_point;
    void *up;
  };

  EntryPoint_ *entry_point_ = new EntryPoint_;
  entry_point_->entry_point = entry_point;
  entry_point_->up = up;

  Thread_ *thread = new Thread_;

  #if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
    struct StartRoutine {
      static unsigned __stdcall run(void *entry_point_) {
        EntryPoint entry_point = ((const EntryPoint_ *)entry_point_)->entry_point;
        void *up = ((const EntryPoint_ *)entry_point_)->up;
        delete (EntryPoint_ *)entry_point_;
        entry_point(up);
        return 0x0000000ul;
      }
    };

    thread->handle_ =
      reinterpret_cast<HANDLE>(
        _beginthreadex(
          NULL, 0,
          &StartRoutine::run, (void *)entry_point_,
          CREATE_SUSPENDED, NULL));
  #else
    struct StartRoutine {
      static DWORD WINAPI run(LPVOID entry_point_) {
        EntryPoint entry_point = ((const EntryPoint_ *)entry_point_)->entry_point;
        void *up = ((const EntryPoint_ *)entry_point_)->up;
        delete (EntryPoint_ *)entry_point_;
        entry_point(up);
        return 0x0000000ul;
      }
    };

    thread->handle_ =
      ::CreateThread(
        NULL, 0,
        &StartRoutine::run, (LPVOID)entry_point_,
        CREATE_SUSPENDED, NULL);
  #endif

  bitbyte_foundation_assert_(thread->handle_ != NULL);
  return *((Thread *)thread);
#endif
}

Thread &Thread::start() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Thread_ *thread = (Thread_ *)this;
  bitbyte_foundation_assert_(::ResumeThread(thread->handle_) == 1);
  return *this;
#endif
}

Thread &Thread::suspend() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Thread_ *thread = (Thread_ *)this;
  bitbyte_foundation_assert_(::SuspendThread(thread->handle_) == 1);
  return *this;
#endif
}

Thread &Thread::resume() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Thread_ *thread = (Thread_ *)this;
  bitbyte_foundation_assert_(::ResumeThread(thread->handle_) == 1);
  return *this;
#endif
}

void Thread::terminate() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Thread_ *thread = (Thread_ *)this;
  // This might leak memory in MSVC builds.
  bitbyte_foundation_assert_(::TerminateThread(thread->handle_, 0xFFFFFFFFul) != 0);
  ::CloseHandle(thread->handle_);
  delete thread;
#endif
}

void Thread::detach() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Thread_ *thread = (Thread_ *)this;
  ::ResumeThread(thread->handle_);
  ::CloseHandle(thread->handle_);
  delete thread;
#endif
}

void Thread::join() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Thread_ *thread = (Thread_ *)this;
  bitbyte_foundation_assert_(::ResumeThread(thread->handle_) <= 1);
  ::WaitForSingleObject(thread->handle_, INFINITE);
  ::CloseHandle(thread->handle_);
  delete thread;
#endif
}

} // tier2
} // foundation
} // bitbyte
