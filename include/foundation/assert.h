// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ASSERT_H_
#define _FOUNDATION_ASSERT_H_

// Provides a more powerful assertion macro that provides contextual
// information: what code failed, on what line, in which file.

#include <foundation/config.h>
#include <foundation/preprocessor.h>

#include <signal.h>

// assertf [
#if defined(_DEBUG)
  #define assertf( _Condition, _Format, ... ) \
    do { if (!(_Condition)) { FOUNDATION_LOG_CALLBACK(_Format, ##__VA_ARGS__); raise(SIGABRT); } } while (0, 0)
#else
  #define assertf( _Condition, _Format, ... ) \
    do { (void)sizeof(_Condition); } while(0, 0)
#endif
// ]

// assert [
#ifdef assert
  #undef assert
#endif

#define assert( _Condition ) \
  assertf(_Condition, \
    "An assertion failed:\n" \
    "\n" \
    "  `%s`\n" \
    "    in `" __foundation_stringify(__FILE__) "` on line " __foundation_stringify(__LINE__) "\n\n", \
    #_Condition \
  )
// ]


#endif // _FOUNDATION_ASSERT_H_