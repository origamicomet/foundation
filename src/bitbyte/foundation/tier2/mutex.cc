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
  #include <windows.h>
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

//===----------------------------------------------------------------------===//
// Constructors
//

Mutex::Mutex() {
}

//===----------------------------------------------------------------------===//
// Destructor
//

Mutex::~Mutex() {
}

//===----------------------------------------------------------------------===//
// Mutex::create
//

Mutex &Mutex::create() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = new Mutex_;
  ::InitializeCriticalSection(&mutex->cs_);
  return *((Mutex *)mutex);
#endif
}

//===----------------------------------------------------------------------===//
// Mutex::destroy
//

void Mutex::destroy() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = (Mutex_ *)this;
  ::DeleteCriticalSection(&mutex->cs_);
  delete mutex;
#endif
}

//===----------------------------------------------------------------------===//
// Mutex::lock
//

void Mutex::lock() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = (Mutex_ *)this;
  ::EnterCriticalSection(&mutex->cs_);
#endif
}

//===----------------------------------------------------------------------===//
// Mutex::try_lock
//

bool Mutex::try_lock() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = (Mutex_ *)this;
  return (::TryEnterCriticalSection(&mutex->cs_) != 0);
#endif
}

//===----------------------------------------------------------------------===//
// Mutex::unlock
//

void Mutex::unlock() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Mutex_ *mutex = (Mutex_ *)this;
  ::LeaveCriticalSection(&mutex->cs_);
#endif
}

} // tier2
} // foundation
} // bitbyte
