// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_TIMER_H_
#define _FOUNDATION_SYSTEM_TIMER_H_

// Provides a collection of path manipulation functions.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#include <time.h>

namespace foundation {
  class FOUNDATION_EXPORT Timer final {
    public:
      Timer();
      Timer( const Timer& timer );
      Timer& operator= ( const Timer& timer );
      ~Timer();

    public:
      void reset();

      uint64_t miliseconds() const;

    private:
      uint64_t _epoch;
  };
} // foundation

#endif // _FOUNDATION_SYSTEM_TIMER_H_
