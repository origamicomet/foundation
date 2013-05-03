// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #include <process.h>
  #include <psapi.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  namespace System {
    void info( Info& info )
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      SYSTEM_INFO si;
      GetSystemInfo(&si);

      OSVERSIONINFO osvi;
      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      GetVersionEx(&osvi);

      MEMORYSTATUSEX msi;
      msi.dwLength = sizeof(MEMORYSTATUSEX);
      GlobalMemoryStatusEx(&msi);

      /* info.os.version */ {
        snprintf(&info.os.version[0], 255, "Windows %s%u.%u.%u",
          (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) ? "" : "NT ",
          osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
      }

      /* info.os.page_size = */ {
        info.os.page_size = (uint32_t)si.dwPageSize;
      }

      // http://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process

      /* info.memory.physical = */ {
        info.memory.physical = msi.ullTotalPhys;
      }

      /* info.memory.physical_available = */ {
        info.memory.physical_available = msi.ullAvailPhys;
      }

      /* info.memory.physical_unavailable = */ {
        info.memory.physical_unavailable = msi.ullTotalPhys - msi.ullAvailPhys;
      }

      /* info.processors.architecture = */ {
        switch (si.wProcessorArchitecture) {
          case PROCESSOR_ARCHITECTURE_INTEL:
            info.processors.architecture = PROCESSOR_ARCH_X86;
            break;
          case PROCESSOR_ARCHITECTURE_AMD64:
            info.processors.architecture = PROCESSOR_ARCH_X86_64;
            break;
          case PROCESSOR_ARCHITECTURE_ARM:
            info.processors.architecture = PROCESSOR_ARCH_ARM;
            break;
          default:
            info.processors.architecture = PROCESSOR_ARCH_UNKNOWN;
            break;
        }
      }

      /* info.processors.count = */ {
        info.processors.count = (uint32_t)si.dwNumberOfProcessors;
      }
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }
  } // System
} // foundation
