//===-- bitbyte/foundation/tier3/cpu.h --------------------------*- C++ -*-===//
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
///
/// \file
/// \brief Abstracts CPU capability and information queries.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER3_CPU_H_
#define _BITBYTE_FOUNDATION_TIER3_CPU_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdint.h"
#include "bitbyte/foundation/tier3/linkage.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief
///
typedef enum bitbyte_foundation_tier3_cpu_vendor {
  /// Unknown.
  BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_UNKNOWN = 0,
  /// Intel.
  BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_INTEL = 1,
  /// Advanced Micro Devices.
  BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_AMD = 2
} bitbyte_foundation_tier3_cpu_vendor_t;

//===----------------------------------------------------------------------===//

/// \def foundation_cpu_vendor
/// \copydoc bitbyte_foundation_cpu_vendor
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_cpu_vendor bitbyte_foundation_cpu_vendor
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_cpu_vendor
/// \copydoc bitbyte_foundation_tier3_cpu_vendor
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_cpu_vendor bitbyte_foundation_tier3_cpu_vendor
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the vendor of the CPU.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
bitbyte_foundation_tier3_cpu_vendor_t
bitbyte_foundation_tier3_cpu_vendor(void);

//===----------------------------------------------------------------------===//

/// \def foundation_cpu_cores
/// \copydoc bitbyte_foundation_cpu_cores
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_cpu_cores bitbyte_foundation_cpu_cores
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_cpu_cores
/// \copydoc bitbyte_foundation_tier3_cpu_cores
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_cpu_cores bitbyte_foundation_tier3_cpu_cores
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the number of logical processors.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
unsigned
bitbyte_foundation_tier3_cpu_cores(void);

//===----------------------------------------------------------------------===//

/// \def foundation_cpu_threads
/// \copydoc bitbyte_foundation_cpu_threads
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_cpu_threads bitbyte_foundation_cpu_threads
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_cpu_threads
/// \copydoc bitbyte_foundation_tier3_cpu_threads
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_cpu_threads bitbyte_foundation_tier3_cpu_threads
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief Returns the number of hardware threads.
///
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
unsigned
bitbyte_foundation_tier3_cpu_threads(void);

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

//===----------------------------------------------------------------------===//

/// \namespace bitbyte::foundation::tier3::Vendors
/// \copydoc bitbyte_foundation_tier3_vendor_t
namespace Vendors {
enum __Enum__ {
  // \copydoc BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_UNKNOWN
  Unknown = BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_UNKNOWN,
  // \copydoc BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_INTEL
  Intel = BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_INTEL,
  // \copydoc BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_AMD
  AMD = BITBYTE_FOUNDATION_TIER3_CPU_VENDOR_AMD
};
}

/// \copydoc bitbyte_foundation_tier3_vendor_t
typedef Vendors::__Enum__ Vendor;

//===----------------------------------------------------------------------===//

/// \copydoc ::foundation_cpu_vendor
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
Vendor
vendor(void);

/// \copydoc ::foundation_cpu_cores
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
unsigned
cores(void);

/// \copydoc ::foundation_cpu_threads
extern
BITBYTE_FOUNDATION_TIER3_EXPORT
unsigned
threads(void);

//===----------------------------------------------------------------------===//

} // cpu

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier3

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER3_CPU_H_

//============================================================================//
