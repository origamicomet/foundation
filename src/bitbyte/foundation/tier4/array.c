//===-- bitbyte/foundation/tier4/array.c ------------------------*- C++ -*-===//
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

#include "bitbyte/foundation/tier4/array.h"

//============================================================================//

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//===----------------------------------------------------------------------===//

void
_bitbyte_foundation_tier4_array_init(
  /* const size_t _Type_size, */
  /* const size_t _Type_alignment, */
  bitbyte_foundation_tier4_array_t *_This,
  bitbyte_foundation_tier4_allocator_t *allocator)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(allocator != NULL);
#endif
  _This->_allocator = allocator;
  _This->_storage.start = (uintptr_t)NULL;
  _This->_storage.finish = (uintptr_t)NULL;
  _This->_storage.end = (uintptr_t)NULL;
}

//===----------------------------------------------------------------------===//

void
_bitbyte_foundation_tier4_array_destroy(
  /* const size_t _Type_size, */
  /* const size_t _Type_alignment, */
  bitbyte_foundation_tier4_array_t *_This)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
#endif
  if (_This->_storage.start != (uintptr_t)NULL)
    _This->_allocator->free(_This->_allocator, (void *)_This->_storage.start);
#ifdef BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  // Hopefully this will help catch stupid bugs.
  _This->_allocator = NULL;
  _This->_storage.start = (uintptr_t)NULL;
  _This->_storage.finish = (uintptr_t)NULL;
  _This->_storage.end = (uintptr_t)NULL;
#endif
}

//===----------------------------------------------------------------------===//

void
_bitbyte_foundation_tier4_array_move(
  /* const size_t _Type_size, */
  /* const size_t _Type_alignment, */
  bitbyte_foundation_tier4_array_t *_This,
  bitbyte_foundation_tier4_array_t *rhs)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(rhs != NULL);
#endif
  _This->_allocator = rhs->_allocator;
  _This->_storage.start = rhs->_storage.start;
  _This->_storage.finish = rhs->_storage.finish;
  _This->_storage.end = rhs->_storage.end;
  rhs->_allocator = NULL;
  rhs->_storage.start = rhs->_storage.finish = rhs->_storage.end = (uintptr_t)NULL;
}

//===----------------------------------------------------------------------===//

void
_bitbyte_foundation_tier4_array_dup(
  /* const size_t _Type_size, */
  const size_t _Type_alignment,
  bitbyte_foundation_tier4_array_t *_This,
  const bitbyte_foundation_tier4_array_t *rhs)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
  bitbyte_foundation_tier2_assert(rhs != NULL);
#endif
  const size_t size_in_bytes = (size_t)(rhs->_storage.finish - rhs->_storage.start);
  const size_t capacity_in_bytes = (size_t)(rhs->_storage.end - rhs->_storage.start);
  _This->_allocator = rhs->_allocator;
  _This->_storage.start = (uintptr_t)rhs->_allocator->alloc(rhs->_allocator,
                                                            capacity_in_bytes,
                                                            _Type_alignment);
  _This->_storage.finish = _This->_storage.start + size_in_bytes;
  _This->_storage.end = _This->_storage.start + capacity_in_bytes;
}

//===----------------------------------------------------------------------===//

size_t
_bitbyte_foundation_tier4_array_size(
  const size_t _Type_size,
  /* const size_t _Type_alignment, */
  const bitbyte_foundation_tier4_array_t *_This)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
#endif
  const size_t size_in_bytes = (size_t)(_This->_storage.finish - _This->_storage.start);
  return (size_in_bytes / _Type_size);
}

//===----------------------------------------------------------------------===//

size_t
_bitbyte_foundation_tier4_array_capacity(
  const size_t _Type_size,
  /* const size_t _Type_alignment, */
  const bitbyte_foundation_tier4_array_t *_This)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
#endif
  const size_t capacity_in_bytes = (size_t)(_This->_storage.end - _This->_storage.start);
  return (capacity_in_bytes / _Type_size);
}
//===----------------------------------------------------------------------===//

bool
_bitbyte_foundation_tier4_array_empty(
  /* const size_t _Type_size, */
  /* const size_t _Type_alignment, */
  const bitbyte_foundation_tier4_array_t *_This)
{
#if BITBYTE_FOUNDATION_CONFIGURATION == BITBYTE_FOUNDATION_CONFIGURATION_DEBUG
  bitbyte_foundation_tier2_assert(_This != NULL);
#endif
  return (_This->_storage.start == _This->_storage.finish);
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

// ...

//===----------------------------------------------------------------------===//

} // bitbyte
} // foundation
} // tier4

//===----------------------------------------------------------------------===//

#endif // __cplusplus

//============================================================================//
