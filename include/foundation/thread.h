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
/*! @file include/foundation/thread.h
     Provides platform independent thread management.                         */
/* ========================================================================== */

#ifndef _FOUNDATION_THREAD_H_
#define _FOUNDATION_THREAD_H_

#include <foundation/config.h>
#include <foundation/compat/stdint.h>
#include <foundation/compat/inttypes.h>

/* ========================================================================== */
/*  Threading:                                                                */
/*   * C (fnd_thread_t);                                                      */
/*   * C++ (foundation::Thread).                                              */
/* ========================================================================== */

/* ========================================================================== */
/*  C (fnd_thread_t):                                                         */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/*! */
typedef void (*fnd_thread_entry_point_fn)(uintptr_t);

/*! */
typedef uint32_t fnd_thread_affinity_t;

/*! */
typedef struct fnd_thread {
  uintptr_t handle_;
} fnd_thread_t;

/* ========================================================================== */

/*! */
extern fnd_thread_affinity_t fnd_thread_any(void);

/* ========================================================================== */

/*! */
extern fnd_thread_t *fnd_thread_create(
  fnd_thread_entry_point_fn entry_point,
  uintptr_t argument);

/*! */
extern void fnd_thread_destroy(
  fnd_thread_t *thread);

/* ========================================================================== */

/*! */
extern fnd_thread_affinity_t fnd_thread_affinity(const fnd_thread_t *thread);

/*! */
extern void fnd_thread_set_affinity(fnd_thread_t *thread, fnd_thread_affinity_t affinity);

/* ========================================================================== */

/*! */
extern void fnd_thread_start(fnd_thread_t *thread);

/*! */
extern void fnd_thread_suspend(fnd_thread_t *thread);

/*! Waits for `thread` to exit. */
extern void fnd_thread_join(fnd_thread_t *thread);

/*! Destroys `thread` without waiting for `thread` to exit. */
extern void fnd_thread_detach(fnd_thread_t *thread);

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::atomic::*).                                              */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
  /*! @copydoc fnd_thread_t */
  class Thread : private fnd_thread_t {
    public:
      typedef fnd_thread_entry_point_fn EntryPoint;
      typedef fnd_thread_affinity_t Affinity;
    public:
      static const Affinity any;
    private:
      Thread(const Thread &);
      Thread& operator =(const Thread &);
    private:
      Thread();
      ~Thread();
    public:
      /*! @copydoc fnd_thread_create */
      static Thread *create(EntryPoint entry_point, uintptr_t argument);
      /*! @copydoc fnd_thread_destroy */
      void destroy();
    public:
      /*! @copydoc fnd_thread_start */
      void start();
      /*! @copydoc fnd_thread_suspend */
      void suspend();
      /*! @copydoc fnd_thread_join */
      void join();
      /*! @copydoc fnd_thread_detach */
      void detach();
    public:
      /*! @copydoc fnd_thread_affinity */
      Affinity affinity() const;
      /*! @copydoc fnd_thread_set_affinity */
      void set_affinity(const Affinity affinity);
  };
} /* foundation */
#endif

#endif /* _FOUNDATION_THREAD_H_ */
