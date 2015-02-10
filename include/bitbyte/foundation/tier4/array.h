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

/// \brief
///
typedef struct bitbyte_foundation_tier4_array {
  bitbyte_foundation_tier4_allocator_t *_allocator; ///<
  struct {
    uintptr_t start; ///<
    uintptr_t finish; ///<
    uintptr_t end; ///<
  } _storage;
} bitbyte_foundation_tier4_array_t;

/// \copydoc bitbyte_foundation_tier4_array_t
typedef bitbyte_foundation_tier4_array_t bitbyte_foundation_array_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_array_t
  typedef bitbyte_foundation_array_t foundation_array_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_array_init
/// \copydoc bitbyte_foundation_array_init
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_array_init bitbyte_foundation_array_init
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_array_init
/// \copydoc bitbyte_foundation_tier4_array_init
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_array_init bitbyte_foundation_tier4_array_init
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_tier4_array_init
/// \param _Type
///
#define bitbyte_foundation_tier4_array_init(_Type) \
  _bitbyte_foundation_tier4_array__##_Type##__init

/// \brief
/// \param _This
/// \param allocator
///
extern
BITBYTE_FOUNDATION_TIER4_EXPORT
void
_bitbyte_foundation_tier4_array_init(
  /* const size_t _Type_size, */
  /* const size_t _Type_alignment, */
  bitbyte_foundation_tier4_array_t *_This,
  bitbyte_foundation_tier4_allocator_t *allocator);

//===----------------------------------------------------------------------===//

/// \def foundation_array_destroy
/// \copydoc bitbyte_foundation_array_destroy
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_array_destroy bitbyte_foundation_array_destroy
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_array_destroy
/// \copydoc bitbyte_foundation_tier4_array_destroy
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_array_destroy bitbyte_foundation_tier4_array_destroy
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_tier4_array_destroy
/// \param _Type
///
#define bitbyte_foundation_tier4_array_destroy(_Type) \
  _bitbyte_foundation_tier4_array__##_Type##__destroy

/// \brief
/// \param _This
/// \param allocator
///
extern
BITBYTE_FOUNDATION_TIER4_EXPORT
void
_bitbyte_foundation_tier4_array_destroy(
  /* const size_t _Type_size, */
  /* const size_t _Type_alignment, */
  bitbyte_foundation_tier4_array_t *_This);

//===----------------------------------------------------------------------===//

/// \def foundation_array_move
/// \copydoc bitbyte_foundation_array_move
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_array_move bitbyte_foundation_array_move
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_array_move
/// \copydoc bitbyte_foundation_tier4_array_move
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_array_move bitbyte_foundation_tier4_array_move
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_tier4_array_move
/// \param _Type
///
#define bitbyte_foundation_tier4_array_move(_Type) \
  _bitbyte_foundation_tier4_array__##_Type##__move

/// \brief
/// \param _This
/// \param allocator
///
extern
BITBYTE_FOUNDATION_TIER4_EXPORT
void
_bitbyte_foundation_tier4_array_move(
  /* const size_t _Type_size, */
  /* const size_t _Type_alignment, */
  bitbyte_foundation_tier4_array_t *_This,
  bitbyte_foundation_tier4_array_t *rhs);

//===----------------------------------------------------------------------===//

/// \def foundation_array_dup
/// \copydoc bitbyte_foundation_array_dup
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_array_dup bitbyte_foundation_array_dup
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_array_dup
/// \copydoc bitbyte_foundation_tier4_array_dup
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_array_dup bitbyte_foundation_tier4_array_dup
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_tier4_array_dup
/// \param _Type
///
#define bitbyte_foundation_tier4_array_dup(_Type) \
  _bitbyte_foundation_tier4_array__##_Type##__dup

/// \brief
/// \param _This
/// \param allocator
///
extern
BITBYTE_FOUNDATION_TIER4_EXPORT
void
_bitbyte_foundation_tier4_array_dup(
  /* const size_t _Type_size, */
  const size_t _Type_alignment,
  bitbyte_foundation_tier4_array_t *_This,
  const bitbyte_foundation_tier4_array_t *rhs);

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
  /* ... */
};

//===----------------------------------------------------------------------===//

} // tier4
} // foundation
} // bitbyte

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

/// \def FOUNDATION_ARRAY_C
/// \copydoc BITBYTE_FOUNDATION_ARRAY_C
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define FOUNDATION_ARRAY_C BITBYTE_FOUNDATION_ARRAY_C
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def BITBYTE_FOUNDATION_ARRAY_C
/// \copydoc BITBYTE_FOUNDATION_TIER4_ARRAY_C
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define BITBYTE_FOUNDATION_ARRAY_C BITBYTE_FOUNDATION_TIER4_ARRAY_C
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def
/// \brief
/// \param
///
#define BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type) \
  _bitbyte_foundation_tier4_array__##_Type##__t

//===----------------------------------------------------------------------===//

/// \def FOUNDATION_ARRAY_CXX
/// \copydoc BITBYTE_FOUNDATION_ARRAY_CXX
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define FOUNDATION_ARRAY_CXX BITBYTE_FOUNDATION_ARRAY_CXX
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def BITBYTE_FOUNDATION_ARRAY_CXX
/// \copydoc BITBYTE_FOUNDATION_TIER4_ARRAY_CXX
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define BITBYTE_FOUNDATION_ARRAY_CXX BITBYTE_FOUNDATION_TIER4_ARRAY_CXX
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def
/// \brief
/// \param
///
#define BITBYTE_FOUNDATION_TIER4_ARRAY_CXX(_Type) \
  ::bitbyte::foundation::tier4::Array<##_Type##>

//===----------------------------------------------------------------------===//

#define _BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type) \
  typedef struct BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type) { \
    /* Wrap the underlying generic type for increased type-saftey. */ \
    bitbyte_foundation_tier4_array_t __array__; \
  } BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type); \
 \
  /*BITBYTE_FOUNDATION_TIER2_FORCE_INLINE*/ void _bitbyte_foundation_tier4_array__##_Type##__init(BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type) *_This, \
                                                                                                  bitbyte_foundation_tier4_allocator_t *allocator) { \
    _bitbyte_foundation_tier4_array_init(/* sizeof(##_Type##), */ \
                                         /* _Alignof(##_Type##), */ \
                                         &_This->__array__, \
                                         allocator); \
  } \
 \
  /*BITBYTE_FOUNDATION_TIER2_FORCE_INLINE*/ void _bitbyte_foundation_tier4_array__##_Type##__destroy(BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type) *_This) { \
    _bitbyte_foundation_tier4_array_destroy(/* sizeof(##_Type##), */ \
                                            /* _Alignof(##_Type##), */ \
                                            &_This->__array__); \
  } \
 \
  /*BITBYTE_FOUNDATION_TIER2_FORCE_INLINE*/ void _bitbyte_foundation_tier4_array__##_Type##__move(BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type) *_This, \
                                                                                                  BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type) *rhs) { \
    _bitbyte_foundation_tier4_array_move(/* sizeof(##_Type##), */ \
                                         /* _Alignof(##_Type##), */ \
                                         &_This->__array__, \
                                         &rhs->__array__); \
  } \
 \
  /*BITBYTE_FOUNDATION_TIER2_FORCE_INLINE*/ void _bitbyte_foundation_tier4_array__##_Type##__dup(BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type) *_This, \
                                                                                                 const BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type) *rhs) { \
    _bitbyte_foundation_tier4_array_dup(/* sizeof(##_Type##), */ \
                                        _Alignof(##_Type##), \
                                        &_This->__array__, \
                                        &rhs->__array__); \
  }

#define _BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_CXX(_Type) \
  template <> \
  class BITBYTE_FOUNDATION_TIER4_ARRAY_CXX(_Type) { \
   public: \
    typedef BITBYTE_FOUNDATION_TIER4_ARRAY_C(_Type) _Array_c; \
    typedef BITBYTE_FOUNDATION_TIER4_ARRAY_CXX(_Type) _Array_cxx; \
   public: \
    explicit Array(); \
    /*BITBYTE_FOUNDATION_TIER2_FORCE_INLINE*/ explicit Array(::bitbyte::foundation::tier4::Allocator *allocator) { bitbyte_foundation_tier4_array_init(_Type)(&this->_This, allocator->to_c()); } \
    /*BITBYTE_FOUNDATION_TIER2_FORCE_INLINE*/ explicit Array(const _Array_cxx &rhs) { bitbyte_foundation_tier4_array_dup(_Type)(&this->_This, &rhs._This); } \
    /*BITBYTE_FOUNDATION_TIER2_FORCE_INLINE*/ explicit Array(_Array_cxx &&rhs) { bitbyte_foundation_tier4_array_move(_Type)(&this->_This, &rhs._This); } \
    /*BITBYTE_FOUNDATION_TIER2_FORCE_INLINE*/ _Array_cxx &operator=(const _Array_cxx &rhs) { \
      bitbyte_foundation_tier4_array_dup(_Type)(&this->_This, &rhs._This); return *this; } \
    /*BITBYTE_FOUNDATION_TIER2_FORCE_INLINE*/ ~Array() { bitbyte_foundation_tier4_array_destroy(_Type)(&this->_This); } \
   private: \
    _Array_c _This; \
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
/// \params
///
#ifdef __cplusplus
  #define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY(_Type) \
    extern "C" { \
      _BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type) \
    } \
    _BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_CXX(_Type)
#else // !__cplusplus
  #define BITBYTE_FOUNDATION_TIER4_DECL_ARRAY(_Type) \
    _BITBYTE_FOUNDATION_TIER4_DECL_ARRAY_C(_Type)
#endif // __cplusplus

//===----------------------------------------------------------------------===//

#define _BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_C(_Type)
  /* ... */

#define _BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_CXX(_Type)
  /* ... */

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
  #define BITBYTE_FOUNDATION_TIER4_DEF_ARRAY(_Type) \
    extern "C" { \
      _BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_C(_Type) \
    } \
    _BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_CXX(_Type)
#else // !__cplusplus
  #define BITBYTE_FOUNDATION_TIER4_DEF_ARRAY(_Type) \
    _BITBYTE_FOUNDATION_TIER4_DEF_ARRAY_C(_Type)
#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER4_ARRAY_H_

//============================================================================//
