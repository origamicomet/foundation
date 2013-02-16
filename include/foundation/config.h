// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_CONFIG_H_
#define _FOUNDATION_CONFIG_H_

// Provides a central location to modify library from and functionality.

#include <foundation/compat.h>

// Uncomment this if you're linking to this library dynamically.
// #define FOUNDATION_DYNAMICALLY_LINKED 1

#if defined(FOUNDATION_DYNAMICALLY_LINKED)
  #if defined(FOUNDATION_COMPILING)
    #define FOUNDATION_EXPORT FOUNDATION_DYNAMIC_EXPORT
  #else
    #define FOUNDATION_EXPORT FOUNDATION_DYNAMIC_IMPORT
  #endif
#else
  #define FOUNDATION_EXPORT
#endif

// Define this if you're going to use a customized log callback.
// #define FOUNDATION_CUSTOM_LOG_CALLBACK

#if !defined(FOUNDATION_CUSTOM_LOG_CALLBACK)
  #include <stdio.h>
  #include <stdarg.h>

  static void __foundation_default_log_callback( const char* format, ... ) {
    va_list va;
    va_start(va, format);
    vfprintf(stderr, format, va);
    va_end(va);
  }

  #define FOUNDATION_LOG_CALLBACK \
    __foundation_default_log_callback
#else
  #define FOUNDATION_LOG_CALLBACK \
    FOUNDATION_CUSTOM_LOG_CALLBACK
#endif

#define FOUNDATION_LOG FOUNDATION_LOG_CALLBACK

// The number of bytes to allocate for the default scratch allocator.
#define FOUNDATION_DEF_SCRATCH_ALLOCATOR_SIZE 1048575 /* 1mb */

#endif // _FOUNDATION_CONFIG_H_