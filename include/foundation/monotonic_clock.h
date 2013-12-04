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
/*! @file include/foundation/monotonic_clock.h
     Provides a high-precision monotonic (steadily increasing) clock.         */
/* ========================================================================== */

#ifndef _FOUNDATION_MONOTONIC_CLOCK_H_
#define _FOUNDATION_MONOTONIC_CLOCK_H_

#include <foundation/config.h>
#include <foundation/compat/stdint.h>
#include <foundation/compat/inttypes.h>

/* ========================================================================== */
/*  Monotonic Clock:                                                          */
/*   * C (fnd_monotonic_clock_t);                                             */
/*   * C++ (foundation::clock::Monotonic).                                    */
/* ========================================================================== */

/* ========================================================================== */
/*  C (fnd_monotonic_clock_t):                                                */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */

/*! A high-precision monotonic (steadily increasing) clock. */
typedef struct fnd_monotonic_clock fnd_monotonic_clock_t;

/* ========================================================================== */

/*! Gets the number of seconds elapsed since reset. */
extern uint64_t fnd_monotonic_clock_secs(const fnd_monotonic_clock_t *mc);

/*! Gets the number of miliseconds elapsed since reset. */
extern uint64_t fnd_monotonic_clock_msecs(const fnd_monotonic_clock_t *mc);

/*! Gets the number of microseconds elapsed since reset. */
extern uint64_t fnd_monotonic_clock_usecs(const fnd_monotonic_clock_t *mc);

/*! Gets the number of nanoseconds elapsed since reset. */
extern uint64_t fnd_monotonic_clock_nsecs(const fnd_monotonic_clock_t *mc);

/* ========================================================================== */

/*! Creates and resets a monotonic clock. */
extern fnd_monotonic_clock_t *fnd_monotonic_clock_create(void);

/*! Resets `mc`. */
extern void fnd_monotonic_clock_reset(fnd_monotonic_clock_t *mc);

/*! Destroys `mc`. */
extern void fnd_monotonic_clock_destroy(fnd_monotonic_clock_t *mc);

/* ========================================================================== */

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::clock::Monotonic):                                       */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
namespace clock {
  /*! @copydoc fnd_monotonic_clock_t */
  class Monotonic {
    private:
      Monotonic();
      Monotonic(const Monotonic &);
      Monotonic &operator= (const Monotonic &);
      ~Monotonic();
    public: /* private: */
      static Monotonic *recover_(::fnd_monotonic_clock_t *mc);
      ::fnd_monotonic_clock_t *lose_();
      static const Monotonic *recover_(const ::fnd_monotonic_clock_t *mc);
      const ::fnd_monotonic_clock_t *lose_() const;
    public:
      /*! @copydoc fnd_monotonic_clock_secs */
      uint64_t secs() const;
      /*! @copydoc fnd_monotonic_clock_msecs */
      uint64_t msecs() const;
      /*! @copydoc fnd_monotonic_clock_usecs */
      uint64_t usecs() const;
      /*! @copydoc fnd_monotonic_clock_nsecs */
      uint64_t nsecs() const;
    public:
      /*! @copydoc fnd_monotonic_clock_create */
      static Monotonic *create();
      /*! @copydoc fnd_monotonic_clock_reset */
      void reset();
      /*! @copydoc fnd_monotonic_clock_destroy */
      void destroy();
  };
} /* clock */
} /* foundation */
#endif

/* ========================================================================== */

#endif /* _FOUNDATION_MONOTONIC_CLOCK_H_ */
