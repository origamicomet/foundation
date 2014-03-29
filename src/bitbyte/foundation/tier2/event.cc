//=== bitbyte/foundation/tier2/event.cc ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier2/event.h>

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
  struct Event_ {
    HANDLE handle_;
  };
}
#endif

//===----------------------------------------------------------------------===//
// Constructors
//

Event::Event() {}

//===----------------------------------------------------------------------===//
// Copy constructors:
//

#if 0
Event::Event(const Event &event) {}
#endif

//===----------------------------------------------------------------------===//
// Assignment operators:
//

#if 0
Event &Event::operator=(const Event &event) {}
#endif

//===----------------------------------------------------------------------===//
// Destructor:
//

Event::~Event() {}

//===----------------------------------------------------------------------===//
// Event::create
//

Event &Event::create() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Event_ *event = new Event_;
  event->handle_ = ::CreateEvent(NULL, TRUE, FALSE, NULL);
  return *((Event *)event);
#endif
}

//===----------------------------------------------------------------------===//
// Event::destroy
//

void Event::destroy() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Event_ *event = (Event_ *)this;
  ::CloseHandle(event->handle_);
  delete event;
#endif
}

//===----------------------------------------------------------------------===//
// Event::signal
//

void Event::signal() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Event_ *event = (Event_ *)this;
  ::SetEvent(event->handle_);
#endif
}

//===----------------------------------------------------------------------===//
// Event::reset
//

void Event::reset() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Event_ *event = (Event_ *)this;
  ::ResetEvent(event->handle_);
#endif
}

//===----------------------------------------------------------------------===//
// Event::is_signaled
//

bool Event::is_signaled() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Event_ *event = (Event_ *)this;
  return (::WaitForSingleObject(event->handle_, 0) == WAIT_OBJECT_0);
#endif
}

//===----------------------------------------------------------------------===//
// Event::is_not_signaled
//

bool Event::is_not_signaled() {
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  Event_ *event = (Event_ *)this;
  return (::WaitForSingleObject(event->handle_, 0) == WAIT_TIMEOUT);
#endif
}

} // tier2
} // foundation
} // bitbyte
