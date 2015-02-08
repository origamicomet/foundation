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

#define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type, _Name)                                               \
  typedef struct _Name {                                                                                  \
    bitbyte_foundation_tier4_array_t __array__;                                                           \
  } _Name##_t;                                                                                            \
                                                                                                          \
  inline void _Name##_init(_Name##_t *_This,                                                              \
                    bitbyte_foundation_tier4_allocator_t *allocator) {                                    \
    bitbyte_foundation_tier4_array_init(&_This->__array__, allocator);                                    \
  }                                                                                                       \
                                                                                                          \
  inline void _Name##_destroy(_Name##_t *_This) {                                                         \
    bitbyte_foundation_tier4_array_destroy(&_This->__array__);                                            \
  }                                                                                                       \
                                                                                                          \
  inline void _Name##_move(_Name##_t *_This,                                                              \
                           _Name##_t *lhs) {                                                              \
    bitbyte_foundation_tier4_array_move(&_This->__array__, &lhs->__array__);                              \
  }                                                                                                       \
                                                                                                          \
  inline void _Name##_dup(const _Name##_t *_This,                                                         \
                          _Name##_t *lhs) {                                                               \
    bitbyte_foundation_tier4_array_dup(&_This->__array__, &lhs->__array__);                               \
  }                                                                                                       \
                                                                                                          \
  inline size_t _Name##_size(const _Name##_t *_This) {                                                    \
    return bitbyte_foundation_tier4_array_size(&_This->__array__, sizeof(_Type));                         \
  }                                                                                                       \
                                                                                                          \
  inline size_t _Name##_capacity(const _Name##_t *_This) {                                                \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                       \
    return bitbyte_foundation_tier4_array_capacity(&_This->__array__, sizeof(_Type));                     \
  }                                                                                                       \
                                                                                                          \
  /* TODO(mike): Don't take into account capacity--reduces code complexity. */                            \
  inline void _Name##_resize(_Name##_t *_This,                                                            \
                             const size_t new_size) {                                                     \
    const size_t new_size_in_bytes = new_size * sizeof(_Type);                                            \
    bitbyte_foundation_tier4_array_resize(&_This->__array__, new_size_in_bytes);                          \
  }                                                                                                       \
                                                                                                          \
  inline void _Name##_reserve(_Name##_t *_This,                                                           \
                              const size_t additional) {                                                  \
    const size_t additional_in_bytes = additional * sizeof(_Type);                                        \
    bitbyte_foundation_tier4_array_reserve(&_This->__array__, additional_in_bytes);                       \
  }                                                                                                       \
                                                                                                          \
  inline void _Name##_grow(_Name##_t *_This,                                                              \
                           const size_t by) {                                                             \
    const size_t by_in_bytes = by * sizeof(_Type);                                                        \
    bitbyte_foundation_tier4_array_grow(&_This->__array__, by_in_bytes);                                  \
  }                                                                                                       \
                                                                                                          \
  inline _Type *##_Name##_at(_Name##_t *_This,                                                            \
                             const size_t idx) {                                                          \
    return (_Type *)bitbyte_foundation_tier4_array_at(&_This->__array__, sizeof(_Type), idx);             \
  }                                                                                                       \
                                                                                                          \
  inline const _Type *##_Name##_at_const(const _Name##_t *_This,                                          \
                                   const size_t idx) {                                                    \
    return (const _Type *)bitbyte_foundation_tier4_array_at_const(&_This->__array__, sizeof(_Type), idx); \
  }                                                                                                       \
                                                                                                          \
  inline int _Name##_to_s(const _Name##_t *_This, char buf[], const size_t buf_sz) {                      \
    bitbyte_foundation_tier2_assert(_This != NULL);                                                       \
    return snprintf(&buf[0], buf_sz, "#%s_t<%p>", #_Name, _This);                                         \
  }

#define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_CXX(_Type, _Name) \
  template <> \
  class ::bitbyte::foundation::tier4::Array<##_Type##> : private _Name##_t { \
   public: \
    typedef _Name##_t _Array_c; \
    typedef ::bitbyte::foundation::tier4::Array<##_Type##> _Array_cxx; \
   public: \
    inline explicit Array(::bitbyte::foundation::tier4::Allocator *allocator) { _Name##_init((_Array_c *)this, allocator->to_c()); } \
    inline explicit Array(const _Array_cxx &array) { _Name##_dup((const _Array_c *)&array, (_Array_c *)this); } \
    inline Array &operator=(const _Array_cxx &array) { _Name##_dup((const _Array_c *)&array, (_Array_c *)this); return *this; } \
    inline ~Array() { _Name##_destroy((_Array_c *)this); } \
   public: \
    /*inline operator _Name##_t ()       { return (      _Array_c *)this; }*/ \
    /*inline operator _Name##_t () const { return (const _Array_c *)this; }*/ \
   public: \
    inline size_t size() const { return _Name##_size((const _Array_c *)this); } \
    inline size_t capacity() const  { return _Name##_capacity((const _Array_c *)this); } \
   public: \
     inline void resize(const size_t new_size) { return _Name##_resize((_Array_c *)this, new_size); } \
     inline void reserve(const size_t additional) { return _Name##_reserve((_Array_c *)this, additional); } \
     inline void grow(const size_t by) { return _Name##_grow((_Array_c *)this, by); } \
   public: \
     inline _Type &at(const size_t idx) { \
       _Type *E = _Name##_at((_Array_c *)this, idx); \
       bitbyte_foundation_tier2_assert(E != NULL); \
       return *E; } \
     inline const _Type &at(const size_t idx) const { \
       const _Type *E = ##_Name##_at_const((_Array_c *)this, idx); \
       bitbyte_foundation_tier2_assert(E != NULL); \
       return *E; } \
     inline _Type &operator[](const size_t idx) { return at(idx); } \
     inline const _Type &operator[](const size_t idx) const { return at(idx); } \
   public: \
    inline int to_s(char buf[], const size_t buf_sz) { return _Name##_to_s((const _Array_c *)this, buf, buf_sz); } \
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

#define BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_C(_Type, _Name)
  // ...

#define BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_CXX(_Type, _Name)
  // ...

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

/// \brief TODO(mike): Document this.
///
static
void bitbyte_foundation_tier4_array_init(
  bitbyte_foundation_tier4_array_t *_This,
  bitbyte_foundation_tier4_allocator_t *allocator)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(allocator != NULL);
#endif
  _This->_allocator = allocator;
  _This->_start = _This->_finish = _This->_end_of_storage = NULL;
}

/// \brief TODO(mike): Document this.
///
static
void
bitbyte_foundation_tier4_array_destroy(
  bitbyte_foundation_tier4_array_t *_This)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(_This->_allocator != NULL);
#endif
  if (_This->_start)
    _This->_allocator->free(_This->_allocator, (void *)_This->_start);
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  _This->_allocator = NULL;
  _This->_start = _This->_finish = _This->_end_of_storage = NULL;
#endif
}

/// \brief TODO(mike): Document this.
///
static
void
bitbyte_foundation_tier4_array_move(
  bitbyte_foundation_tier4_array_t *_This,
  bitbyte_foundation_tier4_array_t *lhs)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(lhs != NULL);
#endif
  lhs->_allocator = lhs->_allocator;
  lhs->_start = lhs->_start;
  lhs->_finish = lhs->_finish;
  lhs->_end_of_storage = lhs->_end_of_storage;
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  _This->_allocator = NULL;
  _This->_start = _This->_finish = _This->_end_of_storage = NULL;
#endif
}

/// \brief TODO(mike): Document this.
///
static
void
bitbyte_foundation_tier4_array_dup(
  const bitbyte_foundation_tier4_array_t *_This,
  bitbyte_foundation_tier4_array_t *lhs)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(lhs != NULL);
#endif
  lhs->_allocator = _This->_allocator;
  // TODO(mike): Guess alignment with count trailing zeros.
  lhs->_start = (uintptr_t)lhs->_allocator->alloc(lhs->_allocator,
                                                  (size_t)(_This->_finish - _This->_start),
                                                  (size_t)0x4u);
  lhs->_finish = lhs->_end_of_storage = lhs->_start + (_This->_finish - _This->_start);
  memcpy((void *)lhs->_start, (const void *)_This->_start, (_This->_finish - _This->_start));
}

/// \brief TODO(mike): Document this.
///
static
inline
size_t
bitbyte_foundation_tier4_array_size(
  const bitbyte_foundation_tier4_array_t *_This,
  const size_t _Size_of_individual_elements)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(_Size_of_individual_elements > 0);
#endif
  return (_This->_finish - _This->_start) / _Size_of_individual_elements;
}

/// \brief TODO(mike): Document this.
///
static
inline
size_t
bitbyte_foundation_tier4_array_capacity(
  const bitbyte_foundation_tier4_array_t *_This,
  const size_t _Size_of_individual_elements)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(_Size_of_individual_elements > 0);
#endif
  return (_This->_end_of_storage - _This->_start) / _Size_of_individual_elements;
}

/// \brief TODO(mike): Document this.
///
static
void
bitbyte_foundation_tier4_array_resize(
  bitbyte_foundation_tier4_array_t *_This,
  const size_t new_size_in_bytes)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
#endif
  const size_t cur_size_in_bytes = (_This->_finish - _This->_start);
  if (new_size_in_bytes > cur_size_in_bytes) {
    const size_t cur_capacity_in_bytes = (_This->_end_of_storage - _This->_start);
    if (cur_capacity_in_bytes > new_size_in_bytes) {
      _This->_finish = _This->_start + new_size_in_bytes;
    } else {
      const size_t new_capacity_in_bytes = new_size_in_bytes;
      // TODO(mike): Guess alignment with count trailing zeros.
      _This->_start =
        (uintptr_t)_This->_allocator->realloc(_This->_allocator,
                                              (void *)_This->_start,
                                              new_capacity_in_bytes,
                                              (size_t)0x4u);
      _This->_finish = _This->_start + new_size_in_bytes;
      _This->_end_of_storage = _This->_start + new_capacity_in_bytes;
    }
  } else {
    const size_t new_capacity_in_bytes = new_size_in_bytes;
    // TODO(mike): Guess alignment with count trailing zeros.
    _This->_start =
      (uintptr_t)_This->_allocator->realloc(_This->_allocator,
                                            (void *)_This->_start,
                                            new_capacity_in_bytes,
                                            (size_t)0x4u);
    _This->_finish = _This->_start + new_size_in_bytes;
    _This->_end_of_storage = _This->_start + new_capacity_in_bytes;
  }
}

/// \brief TODO(mike): Document this.
///
static
void
bitbyte_foundation_tier4_array_reserve(
  bitbyte_foundation_tier4_array_t *_This,
  const size_t additional_in_bytes)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
#endif
  if (additional_in_bytes > 0) {
    const size_t cur_size_in_bytes = (_This->_finish - _This->_start);
    const size_t cur_capacity_in_bytes = (_This->_end_of_storage - _This->_start);
    const size_t new_capacity_in_bytes = cur_capacity_in_bytes + additional_in_bytes;
    // TODO(mike): Guess alignment with count trailing zeros.
    _This->_start =
      (uintptr_t)_This->_allocator->realloc(_This->_allocator,
                                                      (void *)_This->_start,
                                                      new_capacity_in_bytes,
                                                      (size_t)0x4u);
    _This->_finish = _This->_start + cur_size_in_bytes;
    _This->_end_of_storage = _This->_start + new_capacity_in_bytes;
  }
}

/// \brief TODO(mike): Document this.
///
static
void
bitbyte_foundation_tier4_array_grow(
  bitbyte_foundation_tier4_array_t *_This,
  const size_t by_in_bytes)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
#endif
  const size_t cur_size_in_bytes = (_This->_finish - _This->_start);
  const size_t new_size_in_bytes = cur_size_in_bytes + (by_in_bytes);
  const size_t cur_capacity_in_bytes = (_This->_end_of_storage - _This->_start);
  if (cur_capacity_in_bytes > new_size_in_bytes) {
    _This->_finish = _This->_start + new_size_in_bytes;
  } else {
    const size_t new_capacity_in_bytes = new_size_in_bytes;
    // TODO(mike): Guess alignment with count trailing zeros.
    _This->_start =
      (uintptr_t)_This->_allocator->realloc(_This->_allocator,
                                            (void *)_This->_start,
                                            new_capacity_in_bytes,
                                            (size_t)0x4u);
    _This->_finish = _This->_start + new_size_in_bytes;
    _This->_end_of_storage = _This->_start + new_capacity_in_bytes;
  }
}

/// \brief TODO(mike): Document this.
///
static
inline
void *
bitbyte_foundation_tier4_array_at(
  bitbyte_foundation_tier4_array_t *_This,
  const size_t _Size_of_individual_elements,
  const size_t idx)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(idx < bitbyte_foundation_tier4_array_size(_This, _Size_of_individual_elements));
  bitbyte_foundation_tier2_assert(_Size_of_individual_elements > 0);
#endif
  return (void *)(_This->_start + (idx * _Size_of_individual_elements));
}

/// \brief TODO(mike): Document this.
///
static
inline
const void *
bitbyte_foundation_tier4_array_at_const(
  const bitbyte_foundation_tier4_array_t *_This,
  const size_t _Size_of_individual_elements,
  const size_t idx)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(idx < bitbyte_foundation_tier4_array_size(_This, _Size_of_individual_elements));
  bitbyte_foundation_tier2_assert(_Size_of_individual_elements > 0);
#endif
  return (const void *)(_This->_start + (idx * _Size_of_individual_elements));
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
  /// \copydoc ::bitbyte_foundation_tier4_array_size
  size_t size() const;

  /// \copydoc ::bitbyte_foundation_tier4_array_capacity
  size_t capacity() const;

 public:
  /// \copydoc ::bitbyte_foundation_tier4_array_resize
  void resize(const size_t new_size);

  /// \copydoc ::bitbyte_foundation_tier4_array_reserve
  void reserve(const size_t additional);

  /// \copydoc ::bitbyte_foundation_tier4_array_grow
  void grow(const size_t by);

 public:
  /// \defgroup at
  /// \copydoc ::bitbyte_foundation_tier4_array_at
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
