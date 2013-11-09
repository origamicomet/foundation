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
 #  include <foundation/system.h>
/* ========================================================================== */

#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #include <process.h>
  #include <psapi.h>
#elif (FND_PLATFORM == FND_PLATFORM_MACOSX)  || \
      (FND_PLATFORM == FND_PLATFORM_LINUX)   || \
      (FND_PLATFORM == FND_PLATFORM_ANDROID) || \
      (FND_PLATFORM == FND_PLATFORM_IOS)
  #error ("Not implemented, yet.")
#else
  #error ("Unknown or unsupported platform.")
#endif

/* ========================================================================== */
/*  C (fnd_system_xxx):                                                       */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*  Processor:                                                                */
/* ========================================================================== */

size_t fnd_sys_num_of_cores(void) {
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  SYSTEM_INFO si;
  GetSystemInfo(&si);
  return ((size_t)si.dwNumberOfProcessors);
#endif
}

/* ========================================================================== */
/*  Memory:                                                                   */
/* ========================================================================== */

size_t fnd_sys_total_physical_memory(void) {
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  MEMORYSTATUSEX msi;
  msi.dwLength = sizeof(MEMORYSTATUSEX);
  GlobalMemoryStatusEx(&msi);
  return ((size_t)msi.ullTotalPhys);
#endif
}

size_t fnd_sys_available_physical_memory(void) {
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  MEMORYSTATUSEX msi;
  msi.dwLength = sizeof(MEMORYSTATUSEX);
  GlobalMemoryStatusEx(&msi);
  return ((size_t)msi.ullAvailPhys);
#endif
}

size_t fnd_sys_unavailable_physical_memory(void) {
#if (FND_PLATFORM == FND_PLATFORM_WINDOWS)
  MEMORYSTATUSEX msi;
  msi.dwLength = sizeof(MEMORYSTATUSEX);
  GlobalMemoryStatusEx(&msi);
  return ((size_t)(msi.ullTotalPhys - msi.ullAvailPhys));
#endif
}

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*  C++ (foundation::atomic::*).                                              */
/* ========================================================================== */

/* ... */
