//=== bitbyte/foundation/tier1/assertion.h ===================================//
//                                                                            //
//  Foundation                                                                //
//                                                                            //
//  This file is distributed under the terms described in LICENSE.            //
//                                                                            //
//  Author(s):                                                                //
//   Michael Williams <mwilliams@bitbyte.ca>                                  //
//                                                                            //
//===----------------------------------------------------------------------===//

/// @file bitbyte/foundation/tier1/assertion.h
/// @brief Provides assertion management utilities.
///

#ifndef _BITBYTE_FOUNDATION_TIER1_ASSERTION_H_
#define _BITBYTE_FOUNDATION_TIER1_ASSERTION_H_

#include <bitbyte/foundation/config.h>
#include <bitbyte/foundation/tier0/tier0.h>
#include <bitbyte/foundation/tier1/export.h>

namespace bitbyte {
namespace foundation {
namespace tier1 {

/// @brief
///
class BITBYTE_FOUNDATION_TIER1_EXPORT Assertion {
  public: // types:
    typedef bool (*Handler)(const Assertion &assertion, void *up);

  public: // constructors:
    Assertion()
      : predicate(NULL)
      , file(NULL)
      , line(0)
      , message(NULL) {
    }

  public: // copy-constructors:
    Assertion(const Assertion &assertion)
      : predicate(assertion.predicate)
      , file(assertion.file)
      , line(assertion.line)
      , message(assertion.message) {
    }

  public: // assignment operators:
    Assertion &operator=(const Assertion &assertion) {
      predicate = assertion.predicate;
      file = assertion.file;
      line = assertion.line;
      message = assertion.message;
      return *this;
    }

  public: // destructor:
    // ~Assertion() {}

  public: // static methods:
    ///
    static void handler(Handler &handler, void *&up);

    ///
    static void set_handler(Handler handler, void *up = NULL);

  public: // methods:
    ///
    void handle() const;

  public: // members:
    const char *predicate;
    const char *file;
    size_t line;
    const char *message;
};

} // tier1
} // foundation
} // bitbyte

#endif // _BITBYTE_FOUNDATION_TIER1_ASSERTION_H_
