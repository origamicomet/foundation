//===-- bitbyte/foundation/tier4/allocator.h --------------------*- C++ -*-===//
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
/// \brief Provides an interface for allocating, reallocating, and freeing
/// memory as well as query various metrics.
///
//===----------------------------------------------------------------------===//

#ifndef _BITBYTE_FOUNDATION_TIER4_ALLOCATOR_H_
#define _BITBYTE_FOUNDATION_TIER4_ALLOCATOR_H_

//============================================================================//

#include "bitbyte/foundation/tier1/stdint.h"
#include "bitbyte/foundation/tier4/linkage.h"

//===----------------------------------------------------------------------===//

#ifdef __cplusplus
  #include <new>
#endif // __cplusplus

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

/// \brief QQQ
///
typedef void *(*bitbyte_foundation_tier4_allocator_alloc_fn)(
  struct bitbyte_foundation_tier4_allocator *allocator,
  const size_t sz,
  const size_t alignment);

/// \copydoc bitbyte_foundation_tier4_allocator_alloc_fn
typedef bitbyte_foundation_tier4_allocator_alloc_fn bitbyte_foundation_allocator_alloc_fn;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_allocator_alloc_fn
  typedef bitbyte_foundation_allocator_alloc_fn foundation_allocator_alloc_fn;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \brief QQQ
///
typedef void *(*bitbyte_foundation_tier4_allocator_realloc_fn)(
  struct bitbyte_foundation_tier4_allocator *allocator,
  void *ptr,
  const size_t sz,
  const size_t alignment);

/// \copydoc bitbyte_foundation_tier4_allocator_realloc_fn
typedef bitbyte_foundation_tier4_allocator_realloc_fn bitbyte_foundation_allocator_realloc_fn;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_allocator_realloc_fn
  typedef bitbyte_foundation_allocator_realloc_fn foundation_allocator_realloc_fn;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \brief QQQ
///
typedef void *(*bitbyte_foundation_tier4_allocator_free_fn)(
  struct bitbyte_foundation_tier4_allocator *allocator,
  void *ptr);

/// \copydoc bitbyte_foundation_tier4_allocator_free_fn
typedef bitbyte_foundation_tier4_allocator_free_fn bitbyte_foundation_allocator_free_fn;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_allocator_free_fn
  typedef bitbyte_foundation_allocator_free_fn foundation_allocator_free_fn;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \brief QQQ
///
typedef struct bitbyte_foundation_tier4_allocator {
  /// \copdoc bitbyte_foundation_tier4_allocator_alloc_fn
  bitbyte_foundation_tier4_allocator_alloc_fn alloc;
  /// \copydoc bitbyte_foundation_tier4_allocator_realloc_fn
  bitbyte_foundation_tier4_allocator_realloc_fn realloc;
  /// \copydoc bitbyte_foundation_tier4_allocator_free_fn
  bitbyte_foundation_tier4_allocator_free_fn free;
} bitbyte_foundation_tier4_allocator_t;

/// \copydoc bitbyte_foundation_tier4_allocator_t
typedef bitbyte_foundation_tier4_allocator_t bitbyte_foundation_allocator_t;

#ifdef __BITBYTE_FOUNDATION_IMPORT__
  /// \copydoc bitbyte_foundation_allocator_t
  typedef bitbyte_foundation_allocator_t foundation_allocator_t;
#endif // __BITBYTE_FOUNDATION_IMPORT__

//===----------------------------------------------------------------------===//

/// \def foundation_allocator_to_s
/// \copydoc bitbyte_foundation_allocator_to_s
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_allocator_to_s bitbyte_foundation_allocator_to_s
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_allocator_to_s
/// \copydoc bitbyte_foundation_tier4_allocator_to_s
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_allocator_to_s bitbyte_foundation_tier4_allocator_to_s
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \brief QQQ
///
extern
BITBYTE_FOUNDATION_TIER4_EXPORT
int
bitbyte_foundation_tier4_allocator_to_s(
  const bitbyte_foundation_allocator_t *allocator,
  char buf[],
  const size_t buf_sz);

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

/// \copydoc ::bitbyte_foundation_tier4_allocator_t
class BITBYTE_FOUNDATION_TIER4_EXPORT Allocator
{
 protected:
  Allocator();
  Allocator(const Allocator &allocator);
  Allocator &operator= (const Allocator &allocator);
  virtual ~Allocator();

 public:
  /// \copydoc ::bitbyte_foundation_tier4_alloc
  virtual void *alloc(const size_t sz, const size_t alignment) = 0;

  /// \copydoc ::bitbyte_foundation_tier4_realloc
  virtual void *realloc(void *ptr, const size_t sz, const size_t alignment) = 0;

  /// \copydoc ::bitbyte_foundation_tier4_free
  virtual void *free(void *ptr) = 0;

 public:
  /// \copydoc ::bitbyte_foundation_tier4_allocator_to_s
  int to_s(char buf[], const size_t buf_sz);

 private:
  bitbyte_foundation_tier4_allocator_t __allocator__;
  Allocator *__self__;
};

//===----------------------------------------------------------------------===//

/// \def foundation_allocator_new
/// \copydoc bitbyte_foundation_allocator_new
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_allocator_new bitbyte_foundation_allocator_new
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_allocator_new
/// \copydoc bitbyte_foundation_tier4_allocator_new
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_allocator_new bitbyte_foundation_tier4_allocator_new
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_tier4_allocator_new
/// \brief Uses placement new syntax to allocate and initialize an object of a
/// |_Type| using |_Allocator|->alloc.
///
#define bitbyte_foundation_tier4_allocator_new(_Allocator, _Type) \
  new ((_Allocator)->alloc(sizeof(_Type), _Alignof(_Type))) _Type

//===----------------------------------------------------------------------===//

/// \def foundation_allocator_delete
/// \copydoc bitbyte_foundation_allocator_delete
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define foundation_allocator_delete bitbyte_foundation_allocator_delete
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_allocator_delete
/// \copydoc bitbyte_foundation_tier4_allocator_delete
#ifdef __BITBYTE_FOUNDATION_IMPORT__
  #define bitbyte_foundation_allocator_delete bitbyte_foundation_tier4_allocator_delete
#endif // __BITBYTE_FOUNDATION_IMPORT__

/// \def bitbyte_foundation_tier4_allocator_delete
/// \brief Explicitly calls the destructor (specified implicitly by |_Type|) on
/// |_Instance| prior to freeing the object using |_Allocator|->free.
///
#define bitbyte_foundation_tier4_allocator_delete(_Allocator, _Type, _Instance ) \
  do { (_Instance)->~_Type(); (_Allocator)->free((void*)(_Instance)); } while (0, 0)

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier4

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//

#endif // _BITBYTE_FOUNDATION_TIER4_ALLOCATOR_H_

//============================================================================//
