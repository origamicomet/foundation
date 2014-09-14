//===-- bitbyte/foundation/tier3/cpu.c --------------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@bitbyte.ca>
//
//===----------------------------------------------------------------------===//

#include "bitbyte/foundation/tier3/cpu.h"

//===----------------------------------------------------------------------===//

#include <string.h>
#include "bitbyte/foundation/tier0/architecture.h"
#include "bitbyte/foundation/tier0/compiler.h"

//===----------------------------------------------------------------------===//

#if (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__)    || \
    (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__)
  #if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
    #include <intrin.h>
  #endif
#endif

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#if (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__)    || \
    (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__)
static void cpuid(unsigned info, unsigned *eax, unsigned *ebx, unsigned *ecx, unsigned *edx) {
#if BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_MSVC__
  unsigned registers[4];
  __cpuid((int *)&registers[0], (int)info);
  *eax = registers[0];
  *ebx = registers[1];
  *ecx = registers[2];
  *edx = registers[3];
#elif (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_GCC__)   || \
      (BITBYTE_FOUNDATION_TIER0_COMPILER == __BITBYTE_FOUNDATION_TIER0_COMPILER_CLANG__)
  __asm__(
    "cpuid;"
    :"=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
    :"a" (info)
  );
#endif
}
#endif

//===----------------------------------------------------------------------===//

bitbyte_foundation_tier3_cpu_vendor_t
bitbyte_foundation_tier3_cpu_vendor(void)
{
#if (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__)    || \
    (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__)
  unsigned eax, ebx, ecx, edx;
  char vendor[12];
  cpuid(0, &eax, &ebx, &ecx, &edx);
  ((unsigned *)vendor)[0] = ebx;
  ((unsigned *)vendor)[1] = edx;
  ((unsigned *)vendor)[2] = ecx;

  if (memcmp(&vendor[0], "GenuineIntel", 12) == 0) {
    return BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_INTEL;
  } else if (memcmp(&vendor[0], "AuthenticAMD", 12) == 0) {
    return BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_AMD;
  }

  return BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_UNKNOWN;
#endif
}

//===----------------------------------------------------------------------===//

unsigned
bitbyte_foundation_tier3_cpu_cores(void)
{
#if (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__)    || \
    (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__)
  unsigned eax, ebx, ecx, edx;
  cpuid(1, &eax, &ebx, &ecx, &edx);
  const unsigned logical = (ebx >> 16) & 0xFF; // ebx[23:16]
  return logical;
#endif
}

//===----------------------------------------------------------------------===//

unsigned
bitbyte_foundation_tier3_cpu_threads(void)
{
#if (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86__)    || \
    (BITBYTE_FOUNDATION_TIER0_ARCHITECTURE == __BITBYTE_FOUNDATION_TIER0_ARCHITECTURE_X86_64__)
  // TODO(mwilliams): This breaks in a variety of "strange" corner cases, but
  // fuck people who game on server hardware.
  unsigned eax, ebx, ecx, edx;

  char vendor[12];
  cpuid(0, &eax, &ebx, &ecx, &edx);
  ((unsigned *)vendor)[0] = ebx;
  ((unsigned *)vendor)[1] = edx;
  ((unsigned *)vendor)[2] = ecx;

  if (memcmp(&vendor[0], "GenuineIntel", 12) == 0) {
    cpuid(4, &eax, &ebx, &ecx, &edx);
    return ((eax >> 26) & 0xFF) + 1; // eax[31:26] + 1
  } else if (memcmp(&vendor[0], "AuthenticAMD", 12) == 0) {
    cpuid(0x80000008, &eax, &ebx, &ecx, &edx);
    return (ecx & 0xff) + 1; // ecx[7:0] + 1
  }

  return bitbyte_foundation_tier3_cpu_cores();
#endif
}

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier3 {

//===----------------------------------------------------------------------===//

namespace cpu {

Vendor
vendor(void)
{
  return (Vendor)::bitbyte_foundation_tier3_cpu_vendor();
}

unsigned
cores(void)
{
  return ::bitbyte_foundation_tier3_cpu_cores();
}

unsigned
threads(void)
{
  return ::bitbyte_foundation_tier3_cpu_threads();
}

} // cpu

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier3

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
