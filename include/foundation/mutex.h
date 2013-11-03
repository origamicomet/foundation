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
/*! @file include/foundation/mutex.h
     Provides platform independent mutex.                                     */
/* ========================================================================== */

#ifndef _FOUNDATION_MUTEX_H_
#define _FOUNDATION_MUTEX_H_

#include <foundation/config.h>
#include <foundation/detect/platform.h>
#include <foundation/compat/stdint.h>
#include <foundation/compat/inttypes.h>

/* ========================================================================== */
/*  Mutex:                                                                    */
/*   * C (fnd_mutex_t);                                                       */
/*   * C++ (foundation::Mutex).                                               */
/* ========================================================================== */

#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX)  || \
      (FND_PLATFORM == FND_PLATFORM_LINUX)   || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID) ||
      (FND_PLATFORM == FND_PLATFORM_IOS)
  #error ("Not implemented, yet.")
#else
  #error ("Unknown or unsupported platform.")
#endif

/* ========================================================================== */
/*  C (fnd_mutex_t):                                                          */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/*! */
typedef struct fnd_mutex {
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  CRITICAL_SECTION cs;
#endif
} fnd_mutex_t;

/* ========================================================================== */

/*! */
extern fnd_mutex_t *fnd_mutex_create(void);

/*! */
extern void fnd_mutex_destroy(fnd_mutex_t *mutex);

/* ========================================================================== */

/*! */
extern void fnd_mutex_lock(fnd_mutex_t *mutex);

/*! */
extern bool fnd_mutex_try_lock(fnd_mutex_t *mutex);

/*! */
extern void fnd_mutex_unlock(fnd_mutex_t *mutex);

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::Mutex):                                                  */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
  /*! @copydoc fnd_mutex_t */
  class Mutex : private fnd_mutex_t {
    private:
      Mutex(const Mutex &);
      Mutex &operator= (const Mutex &);
    private:
      Mutex();
      ~Mutex();
    public:
      /*! @copydoc fnd_mutex_create */
      static Mutex *create() {
        return ((Mutex *)fnd_mutex_create()); }
      /*! @copydoc fnd_mutex_destroy */
      void destroy() {
        fnd_mutex_destroy((fnd_mutex_t *)this); }
    public:
      /*! @copydoc fnd_mutex_lock */
      void lock() {
        fnd_mutex_lock((fnd_mutex_t *)this); }
      /*! @copydoc fnd_mutex_try_lock */
      bool try_lock() {
        return fnd_mutex_try_lock((fnd_mutex_t *)this); }
      /*! @copydoc fnd_mutex_unlock */
      void unlock() {
        fnd_mutex_unlock((fnd_mutex_t *)this); }
  };
} /* foundation */
#endif

#endif /* _FOUNDATION_MUTEX_H_ */
