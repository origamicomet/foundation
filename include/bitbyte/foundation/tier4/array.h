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
  bitbyte_foundation_tier4_allocator_t *_allocator;
  /// \defgroup Storage TODO(mike): Describe this.
  /// @{
  uintptr_t _start, _finish, _end_of_storage;
  /// @}
} bitbyte_foundation_tier4_array_t;

/// \copydoc bitbyte_foundation_tier4_array_t
typedef bitbyte_foundation_tier4_array_t bitbyte_foundation_array_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_array_t
  typedef bitbyte_foundation_array_t foundation_array_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

#define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type, _Name)                  \
  typedef struct _Name {                                                     \
    bitbyte_foundation_tier4_array_t __array__;                              \
  } _Name##_t;                                                               \
                                                                             \
  extern void _Name##_init(_Name##_t *_This,                                 \
                           bitbyte_foundation_tier4_allocator_t *allocator); \
                                                                             \
  extern void _Name##_destroy(_Name##_t *_This);                             \
                                                                             \
  extern void _Name##_dup(const _Name##_t *_This,                            \
                          _Name##_t *duplicate);                             \
                                                                             \
  extern size_t _Name##_size(const _Name##_t *_This);                        \
                                                                             \
  extern size_t _Name##_capacity(const _Name##_t *_This);                    \
                                                                             \
  extern void _Name##_resize(_Name##_t *_This,                               \
                             const size_t new_size);                         \
                                                                             \
  extern void _Name##_reserve(_Name##_t *_This,                              \
                              const size_t additional);                      \
                                                                             \
  extern void _Name##_grow(_Name##_t *_This,                                 \
                           const size_t by);                                 \
                                                                             \
  extern _Type *##_Name##_at(const _Name##_t *_This,                         \
                           const size_t idx);                                \
                                                                             \
  extern int _Name##_to_s(const _Name##_t *_This,                            \
                          char buf[],                                        \
                          const size_t buf_sz);

#define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_CXX(_Type, _Name) \
  template <> \
  class ::bitbyte::foundation::tier4::Array<##_Type##> : private _Name##_t { \
   public: \
    typedef _Name##_t _Array_c; \
    typedef ::bitbyte::foundation::tier4::Array<##_Type##> _Array_cxx; \
   public: \
    explicit Array(::bitbyte::foundation::tier4::Allocator *allocator) { _Name##_init((_Array_c *)this, allocator->to_c()); } \
    explicit Array(const _Array_cxx &array) { _Name##_dup((const _Array_c *)&array, (_Array_c *)this); } \
    Array &operator=(const _Array_cxx &array) { _Name##_dup((const _Array_c *)&array, (_Array_c *)this); return *this; } \
    ~Array() { _Name##_destroy((_Array_c *)this); } \
   public: \
    /*operator _Name##_t ()       { return (      _Array_c *)this; }*/ \
    /*operator _Name##_t () const { return (const _Array_c *)this; }*/ \
   public: \
    size_t size() const { return _Name##_size((const _Array_c *)this); } \
    size_t capacity() const  { return _Name##_capacity((const _Array_c *)this); } \
   public: \
     void resize(const size_t new_size) { return _Name##_resize((_Array_c *)this, new_size); } \
     void reserve(const size_t additional) { return _Name##_reserve((_Array_c *)this, additional); } \
     void grow(const size_t by) { return _Name##_grow((_Array_c *)this, by); } \
   public: \
     _Type &at(const size_t idx) { \
       _Type *E = _Name##_at((_Array_c *)this, idx); \
       bitbyte_foundation_tier2_assert(E != NULL); \
       return *E; } \
     const _Type &at(const size_t idx) const { \
       const _Type *E = (const _Type *)##_Name##_at((_Array_c *)this, idx); \
       bitbyte_foundation_tier2_assert(E != NULL); \
       return *E; } \
     _Type &operator[](const size_t idx) { return at(idx); } \
     const _Type &operator[](const size_t idx) const { return at(idx); } \
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
    extern "C" { \
      BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type, _Name) \
    } \
    BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_CXX(_Type, _Name)
#else // !__cplusplus
  #define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY(_Type, _Name) \
    BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type, _Name)
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#define BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_C(_Type, _Name)                                               \
  void _Name##_init(_Name##_t *_This,                                                                    \
                    bitbyte_foundation_tier4_allocator_t *allocator) {                                   \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    bitbyte_foundation_tier2_assert(allocator != NULL);                                                  \
    _This->__array__._allocator = allocator;                                                             \
    _This->__array__._start = _This->__array__._finish = _This->__array__._end_of_storage = NULL;        \
  }                                                                                                      \
                                                                                                         \
  void _Name##_destroy(_Name##_t *_This) {                                                               \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    bitbyte_foundation_tier2_assert(_This->__array__._allocator != NULL);                                \
    if (_This->__array__._start != NULL)                                                                 \
      _This->__array__._allocator->free(_This->__array__._allocator, (void *)_This->__array__._start);   \
  }                                                                                                      \
                                                                                                         \
  void _Name##_dup(const _Name##_t *_This,                                                               \
                   _Name##_t *duplicate) {                                                               \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    bitbyte_foundation_tier2_assert(duplicate != NULL);                                                  \
    bitbyte_foundation_tier4_allocator_t *allocator = _This->__array__._allocator;                       \
    duplicate->__array__._allocator = _This->__array__._allocator;                                       \
    const size_t size_in_bytes = _This->__array__._finish - _This->__array__._start;                     \
    const size_t capacity_in_bytes = _This->__array__._end_of_storage - _This->__array__._start;         \
    duplicate->__array__._start = (uintptr_t)allocator->alloc(allocator,                                 \
                                                              capacity_in_bytes,                         \
                                                              _Alignof(_Type));                          \
    duplicate->__array__._finish = duplicate->__array__._start + size_in_bytes;                          \
    duplicate->__array__._end_of_storage = duplicate->__array__._start + capacity_in_bytes;              \
    memcpy((void *)duplicate->__array__._start,                                                          \
           (const void *)_This->__array__._start,                                                        \
           size_in_bytes);                                                                               \
  }                                                                                                      \
                                                                                                         \
  size_t _Name##_size(const _Name##_t *_This) {                                                          \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    return (_This->__array__._finish - _This->__array__._start)/sizeof(_Type);                           \
  }                                                                                                      \
                                                                                                         \
  size_t _Name##_capacity(const _Name##_t *_This) {                                                      \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    return (_This->__array__._end_of_storage - _This->__array__._start)/sizeof(_Type);                   \
  }                                                                                                      \
                                                                                                         \
  /* TODO(mike): Don't take into account capacity--reduces code complexity. */                           \
  void _Name##_resize(_Name##_t *_This,                                                                  \
                      const size_t new_size) {                                                           \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    const size_t new_size_in_bytes = new_size * sizeof(_Type);                                           \
    const size_t cur_size_in_bytes = (_This->__array__._start - _This->__array__._finish);               \
    if (new_size_in_bytes > cur_size_in_bytes) {                                                         \
      const size_t cur_capacity_in_bytes = (_This->__array__._end_of_storage - _This->__array__._start); \
      if (cur_capacity_in_bytes > new_size_in_bytes) {                                                   \
        _This->__array__._finish = _This->__array__._start + new_size_in_bytes;                          \
      } else {                                                                                           \
        const size_t new_capacity_in_bytes = new_size_in_bytes;                                          \
        _This->__array__._start =                                                                        \
          (uintptr_t)_This->__array__._allocator->realloc(_This->__array__._allocator,                   \
                                                          (void *)_This->__array__._start,               \
                                                          new_capacity_in_bytes,                         \
                                                          _Alignof(_Type));                              \
        _This->__array__._finish = _This->__array__._start + new_size_in_bytes;                          \
        _This->__array__._end_of_storage = _This->__array__._start + new_capacity_in_bytes;              \
      }                                                                                                  \
    } else {                                                                                             \
      const size_t new_capacity_in_bytes = new_size_in_bytes;                                            \
      _This->__array__._start =                                                                          \
        (uintptr_t)_This->__array__._allocator->realloc(_This->__array__._allocator,                     \
                                                        (void *)_This->__array__._start,                 \
                                                        new_capacity_in_bytes,                           \
                                                        _Alignof(_Type));                                \
      _This->__array__._finish = _This->__array__._start + new_size_in_bytes;                            \
      _This->__array__._end_of_storage = _This->__array__._start + new_capacity_in_bytes;                \
    }                                                                                                    \
  }                                                                                                      \
                                                                                                         \
  void _Name##_reserve(_Name##_t *_This,                                                                 \
                       const size_t additional) {                                                        \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    if (additional > 0) {                                                                                \
      const size_t cur_size_in_bytes = (_This->__array__._start - _This->__array__._finish);             \
      const size_t cur_capacity_in_bytes = (_This->__array__._end_of_storage - _This->__array__._start); \
      const size_t new_capacity_in_bytes = cur_capacity_in_bytes + (additional * sizeof(_Type));         \
      _This->__array__._start =                                                                          \
        (uintptr_t)_This->__array__._allocator->realloc(_This->__array__._allocator,                     \
                                                        (void *)_This->__array__._start,                 \
                                                        new_capacity_in_bytes,                           \
                                                        _Alignof(_Type));                                \
      _This->__array__._finish = _This->__array__._start + cur_size_in_bytes;                            \
      _This->__array__._end_of_storage = _This->__array__._start + new_capacity_in_bytes;                \
    }                                                                                                    \
  }                                                                                                      \
                                                                                                         \
  void _Name##_grow(_Name##_t *_This,                                                                    \
                  const size_t by) {                                                                     \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    const size_t cur_size_in_bytes = (_This->__array__._start - _This->__array__._finish);               \
    const size_t new_size_in_bytes = cur_size_in_bytes + (by * sizeof(_Type));                           \
    const size_t cur_capacity_in_bytes = (_This->__array__._end_of_storage - _This->__array__._start);   \
    if (cur_capacity_in_bytes > new_size_in_bytes) {                                                     \
      _This->__array__._finish = _This->__array__._start + new_size_in_bytes;                            \
    } else {                                                                                             \
      const size_t new_capacity_in_bytes = new_size_in_bytes;                                            \
      _This->__array__._start =                                                                          \
        (uintptr_t)_This->__array__._allocator->realloc(_This->__array__._allocator,                     \
                                                        (void *)_This->__array__._start,                 \
                                                        new_capacity_in_bytes,                           \
                                                        _Alignof(_Type));                                \
      _This->__array__._finish = _This->__array__._start + new_size_in_bytes;                            \
      _This->__array__._end_of_storage = _This->__array__._start + new_capacity_in_bytes;                \
    }                                                                                                    \
  }                                                                                                      \
                                                                                                         \
  _Type *##_Name##_at(const _Name##_t *_This,                                                            \
                      const size_t idx) {                                                                \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    const size_t idx_in_bytes = idx * sizeof(_Type);                                                     \
    const size_t cur_size_in_bytes = (_This->__array__._start - _This->__array__._finish);               \
    bitbyte_foundation_tier2_assert(cur_size_in_bytes > idx_in_bytes);                                   \
    return (_Type *)(_This->__array__._start + idx_in_bytes);                                            \
  }                                                                                                      \
                                                                                                         \
  int _Name##_to_s(const _Name##_t *_This, char buf[], const size_t buf_sz) {                            \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                      \
    return snprintf(&buf[0], buf_sz, "#%s_t<%p>", #_Name, _This);                                        \
  }

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
    extern "C" { \
      BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_C(_Type, _Name) \
    } \
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
  void resize(const size_t new_size);

  /// TODO(mike): Document this.
  void reserve(const size_t additional);

  /// TODO(mike): Document this.
  void grow(const size_t by);

 public:
  /// \defgroup at TODO(mike): Document this.
  /// @{
  _Type &at(const size_t idx);
  const _Type &at(const size_t idx) const;
  /// @}

  /// \copydoc ::bitbyte::foundation::tier4::Array::at
  _Type &operator[](const size_t idx);
  const _Type &operator[](const size_t idx) const;

 public:
  /// TODO(mike): Document this.
  int to_s(char buf[], const size_t buf_sz);
};


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
