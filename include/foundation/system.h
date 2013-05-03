// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_SYSTEM_H_
#define _FOUNDATION_SYSTEM_H_

// Provides a cross-platform wrapper around:
//  * Process managment and concurrency;
//  * Services (aka daemons) managment;
//  * Memory management;
//  * Networking;
//  * Shared libraries (dlopen, dlsym, etc.);
//  * Capability queries (number of cores, supported instruction sets, etc);
//  * Environment variables;
//  * and IPC.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#include <foundation/system/concurrency.h>
#include <foundation/system/file.h>
#include <foundation/system/path.h>
#include <foundation/system/pipe.h>
#include <foundation/system/process.h>
#include <foundation/system/service.h>
#include <foundation/system/shared_library.h>
// #include <foundation/system/network.h>

namespace foundation {
  enum ProcessorArchitecture {
    PROCESSOR_ARCH_UNKNOWN = 0,
    PROCESSOR_ARCH_X86     = 1,
    PROCESSOR_ARCH_X86_64  = 2,
    PROCESSOR_ARCH_ARM     = 3
  };

  namespace System {
    struct Info {
      struct {
        char version[255];
        uint32_t page_size;
      } os;

      struct {
        uint64_t physical;
        uint64_t physical_available;
        uint64_t physical_unavailable;
      } memory;

      struct {
        ProcessorArchitecture architecture;
        uint32_t count;
      } processors;
    };

    extern FOUNDATION_EXPORT void info( Info& info );
  } // System
} // foundation

#endif // _FOUNDATION_SYSTEM_H_