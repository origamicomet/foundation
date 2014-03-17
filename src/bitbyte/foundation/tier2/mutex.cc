//=== bitbyte/foundation/tier2/mutex.cc ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier2/mutex.h>

#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #error ("Unknown or unsupported platform.")
#endif

namespace bitbyte {
namespace foundation {
namespace tier2 {

#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
namespace {
  struct Mutex_ {
    CRITICAL_SECTION cs_;
  };
}
#endif

Mutex::Mutex() {
}

Mutex::~Mutex() {
}

Mutex &Mutex::create() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = new Mutex_;
  ::InitializeCriticalSection(&mutex->cs_);
  return *((Mutex *)mutex);
#endif
}

void Mutex::lock() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = (Mutex_ *)this;
  ::EnterCriticalSection(&mutex->cs_);
#endif
}

bool Mutex::try_lock() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = (Mutex_ *)this;
  return (::TryEnterCriticalSection(&mutex->cs_) != 0);
#endif
}

void Mutex::unlock() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = (Mutex_ *)this;
  ::LeaveCriticalSection(&mutex->cs_);
#endif
}

void Mutex::destroy() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = (Mutex_ *)this;
  ::DeleteCriticalSection(&mutex->cs_);
  delete mutex;
#endif
}

} // tier2
} // foundation
} // bitbyte
