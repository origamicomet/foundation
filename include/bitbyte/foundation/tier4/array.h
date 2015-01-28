//===-- bitbyte/foundation/tier4/array.h ------------------------*- C++ -*-===//
//
//  Foundation
//
//  This file is distributed under the terms described in LICENSE.
//
//  Author(s):
//
//    * Michael Williams <mike@origamicomet.com>
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief TODO(mike): Document this.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER4_ARRAY_H_
#define _BITBYTE_FOUNDATION_TIER4_ARRAY_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdint.h"
#include "bitbyte/foundation/tier2/assert.h"
#include "bitbyte/foundation/tier4/linkage.h"
#include "bitbyte/foundation/tier4/allocator.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

typedef struct bitbyte_foundation_tier4_array {
  ///
  size_t _size;
  ///
  size_t _capacity;
} bitbyte_foundation_tier4_array_t;

/// \copydoc bitbyte_foundation_tier4_array_t
typedef bitbyte_foundation_tier4_array_t bitbyte_foundation_array_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_array_t
  typedef bitbyte_foundation_array_t foundation_array_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

#define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type, _Name)                   \
  typedef struct _Name {                                                      \
    bitbyte_foundation_tier4_array_t __array__;                               \
  } _Name##_t;                                                                \
                                                                              \
  extern size_t _Name##_size(const _Name##_t *_This);                         \
                                                                              \
  extern size_t _Name##_capacity(const _Name##_t *_This);                     \
                                                                              \
  extern int _Name##_to_s(const _Name##_t *_This,                             \
                          char buf[],                                         \
                          const size_t buf_sz);

#define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_CXX(_Type, _Name) \
  template <> \
  class ::bitbyte::foundation::tier4::Array<##_Type##_t> : private _Name##_t { \
   public: \
    typedef _Name##_t _Array_c; \
    typedef ::bitbyte::foundation::tier4::Array<##_Type##_t> _Array_cxx; \
   public: \
    Array() { /*_Name##_init((_Array_c *)this);*/ } \
    Array(const _Array_c *array) { /*_Name##_dup(array, (_Array_c *)this);*/ } \
    Array(const _Array_cxx &array) { /*_Name##_dup((const _Array_c *)&array, (_Array_c *)this);*/ } \
    Array &operator=(const _Array_c *array) { \
      this->__array__._size = array->__array__._size; array->__array__._size = 0; \
      this->__array__._capacity = array->__array__._capacity;  array->__array__._capacity = 0; \
      return *this; } \
    Array &operator=(const _Array_cxx &array) { \
      this->__array__._size = array.__array__._size; array.__array__._size = 0; \
      this->__array__._capacity = array.__array__._capacity;  array.__array__._capacity = 0; \
      return *this; } \
    ~Array() { /*_Name##_destroy((const _Array_c *)&array, (_Array_c *)this);*/ } \
   public: \
    operator _Name##_t ()       { return (      _Array_c *)this; } \
    operator _Name##_t () const { return (const _Array_c *)this; } \
   public: \
    size_t size() const { return this->__array__._size; } \
    size_t capacity() const  { return this->__array__._capacity; } \
   public: \
    int to_s(char buf[], const size_t buf_sz) { return _Name##_to_s((const _Array_c *)this, buf, buf_sz); } \
  };

/// \def FOUNDATION_DECL_ARRAY
/// \copydoc BITBYTE_FOUNDATION_DECL_ARRAY
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define FOUNDATION_DECL_ARRAY BITBYTE_FOUNDATION_DECL_ARRAY
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def BITBYTE_FOUNDATION_DECL_ARRAY
/// \copydoc BITBYTE_FOUNDATION_TIER4_DECL_ARRAY
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define BITBYTE_FOUNDATION_DECL_ARRAY BITBYTE_FOUNDATION_TIER4_DECL_ARRAY
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def BITBYTE_FOUNDATION_TIER4_DECL_ARRAY
/// \brief
///
#ifdef __cplusplus
  #define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY(_Type, _Name) \
    BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type, _Name) \
    BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_CXX(_Type, _Name)
#else // !__cplusplus
  #define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY(_Type, _Name) \
    BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type, _Name)
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#define BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_C(_Type, _Name)                    \
  size_t _Name##_size(const _Name##_t *_This) {                               \
    bitbyte_foundation_tier2_assert(_This != NULL);                           \
    return _This->__array__._size;                                            \
  }                                                                           \
                                                                              \
  size_t _Name##_capacity(const _Name##_t *_This) {                           \
    bitbyte_foundation_tier2_assert(_This != NULL);                           \
    return _This->__array__._capacity;                                        \
  }                                                                           \
                                                                              \
  int _Name##_to_s(const _Name##_t *_This, char buf[], const size_t buf_sz) { \
    bitbyte_foundation_tier2_assert(_This != NULL);                           \
    return snprintf(&buf[0], buf_sz, "#%s_t<%p>", #_Name, _This);             \
  }                                                                           \

#define BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_CXX(_Type, _Name)

/// \def FOUNDATION_DEF_ARRAY
/// \copydoc BITBYTE_FOUNDATION_DEF_ARRAY
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define FOUNDATION_DEF_ARRAY BITBYTE_FOUNDATION_DEF_ARRAY
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def BITBYTE_FOUNDATION_DEF_ARRAY
/// \copydoc BITBYTE_FOUNDATION_TIER4_DEF_ARRAY
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define BITBYTE_FOUNDATION_DEF_ARRAY BITBYTE_FOUNDATION_TIER4_DEF_ARRAY
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def BITBYTE_FOUNDATION_TIER4_DEF_ARRAY
/// \brief
///
#ifdef __cplusplus
  #define BITBYTE_FOUNDATION_TIER4_DEF_ARRAY(_Type, _Name) \
    BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_C(_Type, _Name) \
    BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_CXX(_Type, _Name)
#else // !__cplusplus
  #define BITBYTE_FOUNDATION_TIER4_DEF_ARRAY(_Type, _Name) \
    BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_C(_Type, _Name)
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
}
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus

//===----------------------------------------------------------------------===//

namespace bitbyte {
namespace foundation {
namespace tier4 {

//===----------------------------------------------------------------------===//

template <typename _Type>
class Array {
 private:
  Array();
  Array(const Array &array);
  Array &operator=(const Array &array);
  ~Array();

 public:
  /// TODO(mike): Document this.
  size_t size() const;

  /// TODO(mike): Document this.
  size_t capacity() const;

 public:
  /// TODO(mike): Document this.
  int to_s(char buf[], const size_t buf_sz);
};

// resize
// reserve
// grow
// search
// sort
// any?
// find
// clear
// at
// condense/compact
// each
// empty?
// include?
// insert
// join
// sort
// push/pop
// replace
// fill
// first/last
// front/back
// begin/end
// reverse
// shift/unshift
// slice
// to_s
// count
// delete (del)

//===----------------------------------------------------------------------===//

} // tier4
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER4_ARRAY_H_

//============================================================================//
