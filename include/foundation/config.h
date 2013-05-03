// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_CONFIG_H_
#define _FOUNDATION_CONFIG_H_

// Provides a central location to modify library form and functionality.

#include <foundation/detect.h>
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

// Uncomment this if you want to track memory usage statistics.
#define FOUNDATION_TRACK_MEMORY_USAGE 1

// Uncomment this if you want memory usage statistics to be thread safe.
// This is only required if you register/unregister allocators or query them in
// a different thread.
#define FOUNDATION_MEMORY_USAGE_STATISTICS_ARE_THREAD_SAFE 1

// The number of bytes to allocate for the default scratch allocator.
#define FOUNDATION_DEFAULT_SCRATCH_ALLOCATOR_SIZE 1048575 /* 1mb */

#endif // _FOUNDATION_CONFIG_H_
