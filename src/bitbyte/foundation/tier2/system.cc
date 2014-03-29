//=== bitbyte/foundation/tier2/system.cc =====================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

#include <bitbyte/foundation/tier2/system.h>

#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #if (BITBYTE_FOUNDATION_COMPILER == BITBYTE_FOUNDATION_COMPILER_MSVC)
    #include <process.h>
  #endif
#else
  #error ("Unknown or unsupported platform.")
#endif


namespace bitbyte {
namespace foundation {
namespace tier2 {

//===----------------------------------------------------------------------===//
// Processors
//

namespace system {

size_t num_logical_processors()
{
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  SYSTEM_INFO si;
  ::GetNativeSystemInfo(&si);
  return si.dwNumberOfProcessors;
#endif
}

size_t num_physical_processors()
{
#if (BITBYTE_FOUNDATION_TARGET_PLATFORM == BITBYTE_FOUNDATION_PLATFORM_WINDOWS)
  DWORD required_buffer_len = 0;
  ::GetLogicalProcessorInformation(
    (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)NULL,
    &required_buffer_len);
  bitbyte_foundation_assert(release, GetLastError() == ERROR_INSUFFICIENT_BUFFER);
  void *buffer = malloc(required_buffer_len);
  DWORD buffer_len = required_buffer_len;
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION *first =
    (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)buffer;
  ::GetLogicalProcessorInformation(
    (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)buffer,
    &buffer_len);
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION *last =
    ((SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)((uintptr_t)first) + buffer_len);
  size_t num_physical_processors = 0;
  for (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *lpi = first; lpi != last; ++lpi)
    if (lpi->Relationship == RelationProcessorCore)
      ++num_physical_processors;
  free(buffer);
  return num_physical_processors;
#endif
}

} // system

} // tier2
} // foundation
} // bitbyte
