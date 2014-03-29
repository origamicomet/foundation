//=== bitbyte/foundation/tier3/bitset.h ======================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier3/bitset.h
/// @brief Provides an arbitrarily sized bitset.
///

#ifndef _BITBYTE_FOUNDATION_TIER3_BITSET_H_
#define _BITBYTE_FOUNDATION_TIER3_BITSET_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/tier1.h>
#include <bitbyte/foundation/tier2/tier2.h>
#include <bitbyte/foundation/tier3/export.h>

namespace bitbyte {
namespace foundation {
namespace tier3 {

/// @brief
///
class BITBYTE_FOUNDATION_TIER3_EXPORT Bitset {
  public: // constructor:
    /// ...
    Bitset(
      size_t sz,
      foundation::tier1::Allocator &allocator = foundation::tier1::heap());

  public: // copy-constructors:
    Bitset(const Bitset &bitset);

  public: // assignment operators:
    Bitset &operator=(const Bitset &bitset);

  public: // destructor:
    ~Bitset();

  public: // methods:
    /// ...
    bool is_set(const size_t bit);

    /// ...
    bool is_not_set(const size_t bit);

    /// ...
    void set();

    /// ...
    void unset();

    /// ...
    void set(const size_t bit);

    /// ...
    void unset(const size_t bit);

    /// ...
    bool and(const size_t lhs, const size_t rhs);

    /// ...
    bool or(const size_t lhs, const size_t rhs);

    /// ...
    bool xor(const size_t lhs, const size_t rhs);

  private: // members:
    foundation::tier1::Allocator &allocator_;
    unsigned *bits_;
    size_t num_bits_;
};

} // tier3
} // foundation
} // bitbyte

#include <bitbyte/foundation/tier3/bitset.inl>

#endif // _BITBYTE_FOUNDATION_TIER3_BITSET_H_
