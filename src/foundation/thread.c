/* ========================================================================== */
/*                                                                            */
/* This file is part of Foundation.                                           */
/*                                                                            */
/* Author(s):                                                                 */
/*                                                                            */
/*   Michael Williams <devbug@bitbyte.ca>                                     */
/*                                                                            */
/* This is free and unencumbered software released into the public domain.    */
/*                                                                            */
/* Anyone is free to copy, modify, publish, use, compile, sell, or distribute */
/* this software, either in source code form or as a compiled binary, for any */
/* purpose, commercial or non-commercial, and by any means.                   */
/*                                                                            */
/* In jurisdictions that recognize copyright laws, the author or authors of   */
/* this software dedicate any and all copyright interest in the software to   */
/* the public domain. We make this dedication for the benefit of the public   */
/* large and to the detriment of our heirs and successors. We intend this     */
/* dedication to be an overt act of relinquishment in perpetuity of all       */
/* present and future rights to this software under copyright law.            */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   */
/* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR      */
/* OTHER DEALINGS IN THE SOFTWARE.                                            */
/*                                                                            */
/* For more information, please refer to <http://unlicense.org/>              */
/*                                                                            */
/* ========================================================================== */
 #  include <foundation/thread.h>
/* ========================================================================== */

#include <foundation/allocator.h>
#include <foundation/assert.h>
#include <foundation/detect/compiler.h>
#include <foundation/detect/platform.h>

#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #if (FND_COMPILER == FND_COMPILER_MSVC)
    #include <process.h>
  #else
  #endif
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX)  || \
      (FND_PLATFORM == FND_PLATFORM_LINUX)   || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID) || \
      (FND_PLATFORM == FND_PLATFORM_IOS)
  #error ("Not implemented, yet.")
#else
  #error ("Unknown or unsupported platform.")
#endif

/* ========================================================================== */
/*  C (fnd_thread_t):                                                         */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct fnd_thread_entry_point {
  fnd_thread_entry_point_fn fn;
  uintptr_t argument;
} fnd_thread_entry_point_t;

/* ========================================================================== */

fnd_thread_affinity_t fnd_thread_any() {
  return ~((fnd_thread_affinity_t)0);
}

/* ========================================================================== */

#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  #if (FND_COMPILER == FND_COMPILER_MSVC)
    static unsigned __stdcall fnd_thread_entry_(void *entry_) {
  #else
    static DWORD WINAPI fnd_thread_entry_(void *entry_) {
  #endif
      fnd_assert(paranoid, entry_ != NULL);
      fnd_thread_entry_point entry;
      memcpy((void *)&entry, (const void *)entry_, sizeof(fnd_thread_entry_point));
      fnd_allocator_free(fnd_heap(), entry_);
      entry.fn(entry.argument);
  #if (FND_COMPILER == FND_COMPILER_MSVC)
      _endthreadex((unsigned)0);
      return ((unsigned)0);
    }
  #else
      ExitThread((DWORD)0);
      return ((DWORD)0);
    }
  #endif
#endif

fnd_thread_t *fnd_thread_create(fnd_thread_entry_point_fn entry_point, uintptr_t argument) {
  fnd_assert(debug, entry_point != NULL);

  /* This has a different lifetime from the `fnd_thread_t` object, as the
    latter's existence is not guaranteed when entering the thread stub. */
  fnd_thread_entry_point *entry = (fnd_thread_entry_point *)
      fnd_allocator_alloc(
        fnd_heap(),
        sizeof(fnd_thread_entry_point),
        fnd_alignof(fnd_thread_entry_point));
  entry->fn = entry_point;
  entry->argument = argument;

  fnd_thread_t *thread = (fnd_thread_t *)
      fnd_allocator_alloc(
        fnd_heap(),
        sizeof(fnd_thread_t),
        fnd_alignof(fnd_thread_t));

#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  #if (FND_COMPILER == FND_COMPILER_MSVC)
    /* See http://stackoverflow.com/questions/331536. */
    thread->handle_ =
      _beginthreadex(
        NULL, 0,
        &fnd_thread_entry_, (void *)entry,
        CREATE_SUSPENDED,
        NULL);
  #else
    thread->handle_ = (uintptr_t)
      CreateThread(
        NULL, 0,
        &fnd_thread_entry_, (void *)entry,
        CREATE_SUSPENDED,
        NULL);
  #endif
#endif

  return thread;
}

void fnd_thread_destroy(fnd_thread_t *thread) {
  fnd_assert(debug, thread != NULL);
  fnd_thread_detach(thread);
}

/* ========================================================================== */

fnd_thread_affinity_t fnd_thread_affinity(const fnd_thread_t *thread) {
  fnd_assert(debug, thread != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  if (!thread->handle_)
    return ((fnd_thread_affinity_t)0);
  SuspendThread((HANDLE)thread->handle_);
  const DWORD_PTR mask = ((DWORD_PTR)1);
  const DWORD_PTR original_mask = SetThreadAffinityMask((HANDLE)thread->handle_, mask);
  SetThreadAffinityMask((HANDLE)thread->handle_, original_mask);
  return ((fnd_thread_affinity_t)original_mask);
#endif
}

void fnd_thread_set_affinity(fnd_thread_t *thread, fnd_thread_affinity_t affinity) {
  fnd_assert(debug, thread != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  if (!thread->handle_)
    return;
  /* Why would you want to change affinity of an already running thread? */
  SuspendThread((HANDLE)thread->handle_);
  const DWORD_PTR mask = ((DWORD_PTR)affinity);
  /* This should work. Should. */
  SetThreadAffinityMask((HANDLE)thread->handle_, mask);
  ResumeThread((HANDLE)thread->handle_);
#endif
}

/* ========================================================================== */

void fnd_thread_start(fnd_thread_t *thread) {
  fnd_assert(debug, thread != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  if (!thread->handle_)
    return;
  ResumeThread((HANDLE)thread->handle_);
#endif
}

void fnd_thread_suspend(fnd_thread_t *thread) {
  fnd_assert(debug, thread != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  if (!thread->handle_)
    return;
  SuspendThread((HANDLE)thread->handle_);
#endif
}

void fnd_thread_join(fnd_thread_t *thread) {
  fnd_assert(debug, thread != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  if (!thread->handle_)
    return;
  /* This allows idomatic usage of fnd_thread_join:
    fnd_thread_join(fnd_thread_create(&entry, argument)); */
  ResumeThread((HANDLE)thread->handle_);
  /* Wait, then free. */
  WaitForSingleObject((HANDLE)thread->handle_, INFINITE);
  CloseHandle((HANDLE)thread->handle_);
  fnd_allocator_free(fnd_heap(), (void *)thread);
#endif
}

void fnd_thread_detach(fnd_thread_t *thread) {
  fnd_assert(debug, thread != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  if (!thread->handle_)
    return;
  /* This allows idomatic usage of fnd_thread_detach:
    fnd_thread_detach(fnd_thread_create(&entry, argument)); */
  ResumeThread((HANDLE)thread->handle_);
  /* Don't wait, and free. */
  CloseHandle((HANDLE)thread->handle_);
  fnd_allocator_free(fnd_heap(), (void *)thread);
#endif
}

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::atomic::*):                                              */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
  const Thread::Affinity Thread::any = ((Thread::Affinity)fnd_thread_any());

  Thread::Thread() {
  }

  Thread::~Thread() {
  }

  Thread *Thread::create(EntryPoint entry_point, uintptr_t argument) {
    return ((Thread *)fnd_thread_create(
      ((fnd_thread_entry_point_fn)entry_point),
      argument));
  }

  void Thread::destroy() {
    fnd_thread_destroy((fnd_thread_t *)this);
  }

  void Thread::start() {
    fnd_thread_start((fnd_thread_t *)this);
  }

  void Thread::suspend() {
    fnd_thread_suspend((fnd_thread_t *)this);
  }

  void Thread::join() {
    fnd_thread_join((fnd_thread_t *)this);
  }

  void Thread::detach() {
    fnd_thread_detach((fnd_thread_t *)this);
  }

  Thread::Affinity Thread::affinity() const {
    return ((Thread::Affinity)fnd_thread_affinity((const fnd_thread_t *)this));
  }

  void Thread::set_affinity(const Affinity affinity) {
    fnd_thread_set_affinity(
      (fnd_thread_t *)this,
      (const fnd_thread_affinity_t)affinity);
  }
} /* foundation */
#endif
