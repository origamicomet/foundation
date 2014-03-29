//=== bitbyte/foundation/tier3/bitset.in; ====================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier3/bitset.inl
/// @brief ...
///

#ifndef _BITBYTE_FOUNDATION_TIER3_BITSET_INL_
#define _BITBYTE_FOUNDATION_TIER3_BITSET_INL_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/tier2.h>
#include <bitbyte/foundation/tier3/export.h>

#include <string.h>

namespace bitbyte {
namespace foundation {
namespace tier3 {

//===----------------------------------------------------------------------===//
// Constructors:
//

Bitset::Bitset(size_t sz, foundation::tier1::Allocator &allocator)
  : allocator_(allocator)
  , bits_(NULL)
  , num_bits_(sz)

{
  bits_ =
    (unsigned *)allocator.alloc(
      (sz + (sizeof(unsigned) * CHAR_BIT) - 1) / (sizeof(unsigned) * CHAR_BIT) * sizeof(unsigned),
      alignof(unsigned));
}

//===----------------------------------------------------------------------===//
// Copy constructors:
//

#if 0
Bitset::Bitset(const Bitset &bitset) {}
#endif

//===----------------------------------------------------------------------===//
// Assignment operators:
//

#if 0
Bitset &Bitset::operator=(const Bitset &bitset) {}
#endif

//===----------------------------------------------------------------------===//
// Destructor:
//

Bitset::~Bitset()
{
  allocator_.free((void *)bits_);
}

//===----------------------------------------------------------------------===//
// Bitset::is_set
//

bool Bitset::is_set(const size_t bit)
{
  unsigned *bits =
    &bits_[(bit + (sizeof(unsigned) * CHAR_BIT) - 1) / (sizeof(unsigned) * CHAR_BIT)];
  return !!(*bits & (1 << (bit % (sizeof(unsigned) * CHAR_BIT))));
}

//===----------------------------------------------------------------------===//
// Bitset::is_not_set
//

bool Bitset::is_not_set(const size_t bit)
{
  unsigned *bits =
    &bits_[(bit + (sizeof(unsigned) * CHAR_BIT) - 1) / (sizeof(unsigned) * CHAR_BIT)];
  return !(*bits & (1 << (bit % (sizeof(unsigned) * CHAR_BIT))));
}

//===----------------------------------------------------------------------===//
// Bitset::set
//

void Bitset::set()
{
  memset((void *)bits_, 0xFF, (num_bits_ + CHAR_BIT - 1) / CHAR_BIT);
}

//===----------------------------------------------------------------------===//
// Bitset::unset
//

void Bitset::unset()
{
  memset((void *)bits_, 0x00, (num_bits_ + CHAR_BIT - 1) / CHAR_BIT);
}

//===----------------------------------------------------------------------===//
// Bitset::set
//

void Bitset::set(const size_t bit)
{
  bitbyte_foundation_assert(debug, bit < num_bits_);
  unsigned *bits =
    &bits_[(bit + (sizeof(unsigned) * CHAR_BIT) - 1) / (sizeof(unsigned) * CHAR_BIT)];
  *bits = *bits | (1 << (bit % (sizeof(unsigned) * CHAR_BIT)));
}

//===----------------------------------------------------------------------===//
// Bitset::unset
//

void Bitset::unset(const size_t bit)
{
  bitbyte_foundation_assert(debug, bit < num_bits_);
  unsigned *bits =
    &bits_[(bit + (sizeof(unsigned) * CHAR_BIT) - 1) / (sizeof(unsigned) * CHAR_BIT)];
  *bits = *bits & ~((1 << (bit % (sizeof(unsigned) * CHAR_BIT))));
}

//===----------------------------------------------------------------------===//
// Bitset::and
//

bool Bitset::and(const size_t lhs, const size_t rhs)
{
  bitbyte_foundation_assert(debug, lhs < num_bits_);
  bitbyte_foundation_assert(debug, rhs < num_bits_);
  const bool set = is_set(lhs) & is_set(rhs);
  unsigned *l =
    &bits_[(lhs + (sizeof(unsigned) * CHAR_BIT) - 1) / (sizeof(unsigned) * CHAR_BIT)];
  *l = *l | (-((unsigned)set) & ((1 << (lhs % (sizeof(unsigned) * CHAR_BIT)))));
  return set;
}

//===----------------------------------------------------------------------===//
// Bitset::or
//

bool Bitset::or(const size_t lhs, const size_t rhs)
{
  bitbyte_foundation_assert(debug, lhs < num_bits_);
  bitbyte_foundation_assert(debug, rhs < num_bits_);
  const bool set = is_set(lhs) | is_set(rhs);
  unsigned *l =
    &bits_[(lhs + (sizeof(unsigned) * CHAR_BIT) - 1) / (sizeof(unsigned) * CHAR_BIT)];
  *l = *l | (-((unsigned)set) & ((1 << (lhs % (sizeof(unsigned) * CHAR_BIT)))));
  return set;
}

//===----------------------------------------------------------------------===//
// Bitset::xor
//

bool Bitset::xor(const size_t lhs, const size_t rhs)
{
  bitbyte_foundation_assert(debug, lhs < num_bits_);
  bitbyte_foundation_assert(debug, rhs < num_bits_);
  const bool set = is_set(lhs) ^ is_set(rhs);
  unsigned *l =
    &bits_[(lhs + (sizeof(unsigned) * CHAR_BIT) - 1) / (sizeof(unsigned) * CHAR_BIT)];
  *l = *l | (-((unsigned)set) & ((1 << (lhs % (sizeof(unsigned) * CHAR_BIT)))));
  return set;
}

} // tier3
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER3_BITSET_INL_
