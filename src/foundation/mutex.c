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
 #  include <foundation/mutex.h>
/* ========================================================================== */

#include <foundation/allocator.h>
#include <foundation/assert.h>

/* ========================================================================== */
/*  C (fnd_mutex_t):                                                          */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

fnd_mutex_t *fnd_mutex_create(void) {
  fnd_mutex_t *mutex = (fnd_mutex_t *)
    fnd_allocator_alloc(
      fnd_heap(),
      sizeof(fnd_mutex_t),
      fnd_alignof(fnd_mutex_t));
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  InitializeCriticalSection(&mutex->cs);
#endif
  return mutex;
}

void fnd_mutex_destroy(fnd_mutex_t *mutex) {
  fnd_assert(debug, mutex != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  DeleteCriticalSection(&mutex->cs);
#endif
  fnd_allocator_free(fnd_heap(), (void *)mutex);
}

/* ========================================================================== */

void fnd_mutex_lock(fnd_mutex_t *mutex) {
  fnd_assert(debug, mutex != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  EnterCriticalSection(&mutex->cs);
#endif
}

bool fnd_mutex_try_lock(fnd_mutex_t *mutex) {
  fnd_assert(debug, mutex != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  return (TryEnterCriticalSection(&mutex->cs) == TRUE);
#endif
}

void fnd_mutex_unlock(fnd_mutex_t *mutex) {
  fnd_assert(debug, mutex != NULL);
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  LeaveCriticalSection(&mutex->cs);
#endif
}

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::Mutex):                                                  */
/* ========================================================================== */

/* ... */
