// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/time_stamp.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#elif 
#endif

namespace foundation {
  TimeStamp::TimeStamp()
    : _time_since_epoch(0)
  {
  }
  
  TimeStamp::TimeStamp( uint64_t time_since_epoch )
    : _time_since_epoch(time_since_epoch)
  {
  }

  TimeStamp::TimeStamp( const TimeStamp& ts )
    : _time_since_epoch(ts._time_since_epoch)
  {
  }

  TimeStamp& TimeStamp::operator= ( const TimeStamp& ts )
  {
    _time_since_epoch = ts._time_since_epoch;
    return *this;
  }

  TimeStamp::~TimeStamp()
  {
  }

  TimeStamp TimeStamp::now()
  {
  #if defined(FOUNDATION_PLATFORM_WINDOWS)
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    const uint64_t epoch =
      (((uint64_t)ft.dwHighDateTime) << 32) | ((uint64_t)ft.dwLowDateTime);
    return TimeStamp(epoch / 10000000LL - 11644473600LL);
  #elif defined(FOUNDATION_PLATFORM_POSIX)
  #endif
  }
} // foundation