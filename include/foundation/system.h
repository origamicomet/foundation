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
/*! @file include/foundation/system.h
     Provides platform independent querying of hardware capabilities (number
     of cores, supported instruction sets, etc.).                             */
/* ========================================================================== */

#ifndef _FOUNDATION_SYSTEM_H_
#define _FOUNDATION_SYSTEM_H_

#include <foundation/config.h>
#include <foundation/compat/stdint.h>
#include <foundation/compat/inttypes.h>

/* ========================================================================== */
/*  Threading:                                                                */
/*   * C (fnd_system_xxx);                                                    */
/*   * C++ (foundation::System::*).                                           */
/* ========================================================================== */

/* ========================================================================== */
/*  C (fnd_system_xxx):                                                       */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*  Processor:                                                                */
/* ========================================================================== */

/*! */
extern size_t fnd_sys_num_of_cores(void);

/* ========================================================================== */
/*  Memory:                                                                   */
/* ========================================================================== */

/*! */
extern size_t fnd_sys_total_physical_memory(void);

/*! */
extern size_t fnd_sys_available_physical_memory(void);

/*! */
extern size_t fnd_sys_unavailable_physical_memory(void);

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::atomic::*).                                              */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
  namespace system {
    /* ====================================================================== */
    /*  Processor:                                                            */
    /* ====================================================================== */
    /*! @copydoc fnd_sys_num_of_cores */
    static size_t num_of_cores() {
      return fnd_sys_num_of_cores(); }

    /* ====================================================================== */
    /*  Memory:                                                               */
    /* ====================================================================== */
    namespace physical_memory {
      /*! @copydoc fnd_sys_total_physical_memory */
      static size_t total() {
        return fnd_sys_total_physical_memory(); }
      /*! @copydoc fnd_sys_available_physical_memory */
      static size_t available() {
        return fnd_sys_available_physical_memory(); }
      /*! @copydoc fnd_sys_unavailable_physical_memory */
      static size_t unavailable() {
        return fnd_sys_unavailable_physical_memory(); }
    } /* physical_memory */
  } /* system */
} /* foundation */
#endif

#endif /* _FOUNDATION_SYSTEM_H_ */
