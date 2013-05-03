// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DEBUG_CALLSTACK_H_
#define _FOUNDATION_DEBUG_CALLSTACK_H_

// Provides a cross-platform callstack generator.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/containers/array.h>
#include <foundation/debug/symbol.h>
#include <foundation/debug/execution_state.h>

namespace foundation {
  class Callstack final {
    public:
      class Frame final {
        public:
          FOUNDATION_INLINE Frame(
            const Symbol& symbol )
            : symbol(symbol)
          {}

          FOUNDATION_INLINE Frame(
            const Frame& frame
          ) : symbol(frame.symbol)
          {}

          FOUNDATION_INLINE Frame& operator= (
            const Frame& frame )
          {
            if (&frame == this)
              return *this;
            symbol = frame.symbol;
            return *this;
          }

          FOUNDATION_INLINE ~Frame()
          {}

        public:
          Symbol symbol;
      };

    public:
      FOUNDATION_INLINE Callstack()
        : frames(Allocators::heap())
      {}

      FOUNDATION_INLINE Callstack(
        const Callstack& callstack
      ) : frames(callstack.frames)
      {}

      FOUNDATION_INLINE Callstack& operator= (
        const Callstack& callstack )
      {
        if (&callstack == this)
          return *this;
        frames = callstack.frames;
        return *this;
      }

      FOUNDATION_INLINE ~Callstack()
      {}

    public:
      Array<Frame> frames;
  };

  extern FOUNDATION_EXPORT bool callstack(
    Callstack& callstack,
    ExecutionState& execution_state );
} // foundation

#endif // _FOUNDATION_DEBUG_CALLSTACK_H_
