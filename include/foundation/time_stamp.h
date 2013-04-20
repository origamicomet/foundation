// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_TIME_STAMP_H_
#define _FOUNDATION_TIME_STAMP_H_

// A cross-platform time stamp based on Unix epoch.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

namespace foundation {
  class FOUNDATION_EXPORT TimeStamp {
    public:
      TimeStamp();
      explicit TimeStamp( uint64_t time_since_epoch );
      TimeStamp( const TimeStamp& ts );
      TimeStamp& operator= ( const TimeStamp& ts );
      ~TimeStamp();

    public:
      static TimeStamp now();

    public:
      FOUNDATION_INLINE operator uint64_t() const
      { return _time_since_epoch; }

    private:
      uint64_t _time_since_epoch;
  };
} // foundation

#endif // _FOUNDATION_TIME_STAMP_H_