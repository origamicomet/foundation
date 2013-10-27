/* ========================================================================== */
/*                                                                            */
/* This file is part of Foundation.                                           */
/*                                                                            */
/* Author(s):                                                                 */
/*                                                                            */
/*   Michael Williams <devbug@bitbyte.ca>                                     */
/*                                                                            */
/* This is free and unencumbered software released into the public domain.    */
/*                                                                            */
/* Anyone is free to copy, modify, publish, use, compile, sell, or distribute */
/* this software, either in source code form or as a compiled binary, for any */
/* purpose, commercial or non-commercial, and by any means.                   */
/*                                                                            */
/* In jurisdictions that recognize copyright laws, the author or authors of   */
/* this software dedicate any and all copyright interest in the software to   */
/* the public domain. We make this dedication for the benefit of the public   */
/* large and to the detriment of our heirs and successors. We intend this     */
/* dedication to be an overt act of relinquishment in perpetuity of all       */
/* present and future rights to this software under copyright law.            */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   */
/* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR      */
/* OTHER DEALINGS IN THE SOFTWARE.                                            */
/*                                                                            */
/* For more information, please refer to <http://unlicense.org/>              */
/*                                                                            */
/* ========================================================================== */
/*! @file include/foundation/array.h
     Provides a typed resizable array (aka a vector).                         */
/* ========================================================================== */

#ifndef _FOUNDATION_ARRAY_H_
#define _FOUNDATION_ARRAY_H_

#include <foundation/config.h>
#include <foundation/compat/stdbool.h>
#include <foundation/allocator.h>

/* ========================================================================== */
/*  Allocator:                                                                */
/*   * "C" (fnd_array_t);                                                     */
/*   * C++ (foundation::array).                                               */
/* ========================================================================== */

/* ========================================================================== */
/*  "C" (fnd_array_t):                                                        */
/* ========================================================================== */

#ifdef __cplusplus

/*! A typed resizable array (aka a vector). */
template <typename _Elem>
struct fnd_array_t {
  /* ======================================================================== */
  struct copy {
    size_t refs;
    fnd_allocator_t *allocator;
    size_t size;
    size_t reserved;
    _Elem *elements;
  };
  /* ======================================================================== */
  copy *copy_;
  bool copy_on_write_ : 1;
};

/* ========================================================================== */

/*! */
template <typename _Elem>
void fnd_array_create(fnd_array_t<_Elem> *array) {
  fnd_assert(debug, array != NULL);
  array->copy_ = NULL;
  array->copy_on_write_ = false;
}

/*! */
template <typename _Elem>
void fnd_array_create(fnd_array_t<_Elem> *array, fnd_allocator_t *allocator) {
  fnd_assert(debug, array != NULL);
  fnd_assert(debug, allocator != NULL);
  array->copy_ = (fnd_array_t<_Elem>::copy *)
    fnd_allocator_alloc(
      allocator,
      sizeof(fnd_array_t<_Elem>::copy),
      fnd_alignof(fnd_array_t<_Elem>::copy));
  array->copy_->refs = 1;
  array->copy_->allocator = allocator;
  array->copy_->size = array->copy_->reserved = 0;
  array->copy_->elements = (_Elem *)NULL;
  array->copy_on_write_ = false;
}

/*! */
template <typename _Elem>
void fnd_array_create(fnd_array_t<_Elem> *array, fnd_allocator_t *allocator, const size_t reserve) {
  fnd_assert(debug, array != NULL);
  fnd_assert(debug, allocator != NULL);
  array->copy_ = (fnd_array_t<_Elem>::copy *)
    fnd_allocator_alloc(
      allocator,
      sizeof(fnd_array_t<_Elem>::copy),
      fnd_alignof(fnd_array_t<_Elem>::copy));
  array->copy_->refs = 1;
  array->copy_->allocator = allocator;
  array->copy_->size = 0;
  array->copy_->reserved = reserve;
  if (reserve) {
    array->copy_->elements = (_Elem *)
      fnd_allocator_alloc(
        allocator,
        reserve * sizeof(_Elem),
        fnd_alignof(_Elem));
  } else {
    array->copy_->elements = (_Elem *)NULL;
  }
  array->copy_on_write_ = false;
}

/*! */
template <typename _Elem>
void fnd_array_destroy(fnd_array_t<_Elem> *array) {
  fnd_assert(debug, array != NULL);
  if (array->copy_) {
    if ((--array->copy_->refs) == 0) {
      fnd_allocator_free(
        array->copy_->allocator,
        (void *)array->copy_->elements);
      fnd_allocator_free(
        array->copy_->allocator,
        (void *)array->copy_);
    }
    array->copy_ = NULL;
  }
  array->copy_on_write_ = false;
}

/* ========================================================================== */

/*! */
template <typename _Elem>
_Elem *fnd_array_at(fnd_array_t<_Elem> *array, const size_t index) {
  fnd_assert(debug, array != NULL);
  if (!array->copy_)
    return NULL;
  /* Can't guarantee no writes will be made. */
  fnd_array_deepen(array);
  if (index >= array->copy_->size)
    return NULL;
  return &array->copy_->elements[index];
}

/*! */
template <typename _Elem>
const _Elem *fnd_array_at(const fnd_array_t<_Elem> *array, const size_t index) {
  fnd_assert(debug, array != NULL);
  if (!array->copy_)
    return NULL;
  if (index >= array->copy_->size)
    return NULL;
  return &array->copy_->elements[index];
}

/* ========================================================================== */

/*! */
template <typename _Elem>
void fnd_array_copy(const fnd_array_t<_Elem> *array, fnd_array_t<_Elem> *copy) {
  fnd_assert(debug, array != NULL);
  fnd_assert(debug, copy != NULL);
  fnd_assert(debug, copy->copy_ == NULL);
  copy->copy_ = array->copy_;
  if (array->copy_)
    array->copy_++;
  copy->copy_on_write_ = true;
}

/*! */
template <typename _Elem>
void fnd_array_deepen(fnd_array_t<_Elem> *array) {
  fnd_assert(debug, array != NULL);
  if (!array->copy_ || !array->copy_on_write_)
    return;
  if (array->copy_->refs == 1) {
    /* Not referenced anywhere else, so just drop the flag. */
    array->copy_on_write_ = false;
    return;
  }
  fnd_array_t<_Elem>::copy *copy = (fnd_array_t<_Elem>::copy *)
    fnd_allocator_alloc(
      array->copy_->allocator,
      sizeof(fnd_array_t<_Elem>::copy),
      fnd_alignof(fnd_array_t<_Elem>::copy));
  copy->refs = 1;
  copy->allocator = array->copy_->allocator;
  copy->size = copy->reserved = array->copy_->size;
  copy->elements = (_Elem *)
    fnd_allocator_alloc(
      array->copy_->allocator,
      array->copy_->size * sizeof(_Elem),
      fnd_alignof(_Elem));
  /* TODO(mtwilliams): Use non_pod_aware_copy<T> to support non-POD. */
  memcpy(
    (void *)copy->elements,
    (const void *)array->copy_->elements,
    array->copy_->size);
  array->copy_->refs--;
  array->copy_ = copy;
  array->copy_on_write_ = false;
}

/*! */
template <typename _Elem>
void fnd_array_copy_on_write(const fnd_array_t<_Elem> *array) {
  fnd_assert(debug, array != NULL);
  return array->copy_on_write_;
}

/* ========================================================================== */

/*! */
template <typename _Elem>
void fnd_array_clear(fnd_array_t<_Elem> *array) {
  fnd_assert(debug, array != NULL);
  if (!array->copy_)
    return;
  if (array->copy_on_write_) {
    if (array->copy_->refs == 1) {
      /* Not referenced anywhere else, so just drop the flag. */
      array->copy_on_write_ = false;
    } else {
      array->copy_->refs--;
      fnd_array_t<_Elem>::copy *copy = (fnd_array_t<_Elem>::copy *)
        fnd_allocator_alloc(
          array->copy_->allocator,
          sizeof(fnd_array_t<_Elem>::copy),
          fnd_alignof(fnd_array_t<_Elem>::copy));
      copy->allocator = array->copy_->allocator;
      copy->size = copy->reserved = 0;
      copy->elements = (_Elem *)NULL;
      array->copy_ = copy;
      array->copy_on_write_ = false;
    }
  } else {
    /* TODO(mtwilliams): Use non_pod_aware_destruct<T> to support non-POD. */
    fnd_allocator_free(
      array->copy_->allocator,
      (void *)array->copy_->elements);
    array->copy_->size = array->copy_->reserved = 0;
    array->copy_->elements = NULL;
  }
}

/*! */
template <typename _Elem>
void fnd_array_coup_(fnd_array_t<_Elem> *array) {
  if (array->copy_on_write_) {
    if (array->copy_->refs == 1) {
      /* Not referenced anywhere else, so just drop the flag. */
      array->copy_on_write_ = false;
    } else {
      array->copy_->refs--;
      fnd_array_t<_Elem>::copy *copy = (fnd_array_t<_Elem>::copy *)
        fnd_allocator_alloc(
          array->copy_->allocator,
          sizeof(fnd_array_t<_Elem>::copy),
          fnd_alignof(fnd_array_t<_Elem>::copy));
      copy->refs = 1;
      copy->allocator = array->copy_->allocator;
      copy->size = array->copy_->size;
      copy->reserved = array->copy_->reserved;
      copy->elements = array->copy_->elements;
      array->copy_ = copy;
      array->copy_on_write_ = false;
    }
  }
}

/*! */
template <typename _Elem>
void fnd_array_shift_(fnd_array_t<_Elem> *array, const _Elem *prefixes, const size_t prefixes_sz) {
  fnd_assert(paranoid, array != NULL);
  fnd_assert(paranoid, array->copy_ != NULL);
  fnd_assert(paranoid, prefixes != NULL);
  fnd_assert(paranoid, prefixes_sz != 0);
  fnd_array_coup_(array);
  const size_t min = array->copy_->size + prefixes_sz;
  if (array->copy_->size < min) {
    _Elem *elements = (_Elem *)
      fnd_allocator_alloc(
        array->copy_->allocator,
        min * sizeof(_Elem),
        fnd_alignof(_Elem));
    memcpy(
      (void *)&elements[0],
      (const void *)prefixes,
      prefixes_sz * sizeof(_Elem));
    memcpy(
      (void *)&elements[prefixes_sz],
      (const void *)array->copy_->elements,
      array->copy_->size);
    fnd_allocator_free(
      array->copy_->allocator,
      (void *)array->copy_->elements);
    array->copy_->size = array->copy_->reserved = min;
    array->copy_->elements = elements;
  } else {
    memmove(
      (void *)&array->copy_->elements[prefixes_sz],
      (const void *)&array->copy_->elements[0],
      array->copy_->size * sizeof(_Elem));
    memcpy(
      (void *)&array->copy_->elements[0],
      (const void *)prefixes,
      prefixes_sz * sizeof(_Elem));
    array->copy_->size += prefixes_sz;
  }
}

/*! */
template <typename _Elem>
void fnd_array_prepend(fnd_array_t<_Elem> *array, const _Elem *prefix) {
  fnd_assert(debug, array != NULL);
  fnd_assert(debug, array->copy_ != NULL);
  fnd_array_deepen(array);
  fnd_array_shift_(array, prefix, 1);
}

/*! */
template <typename _Elem>
void fnd_array_prepend(fnd_array_t<_Elem> *array, const fnd_array_t<_Elem> *prefix) {
  fnd_assert(debug, array != prefix);
  fnd_assert(debug, array != NULL);
  fnd_assert(debug, array->copy_ != NULL);
  if (!prefix->copy_ || (prefix->copy_->size == 0))
    return;
  fnd_array_deepen(array);
  fnd_array_shift_(array, prefix->copy_->elements, prefix->copy_->size);
}

/*! */
template <typename _Elem>
void fnd_array_rshift_(fnd_array_t<_Elem> *array, const _Elem *suffixes, const size_t suffixes_sz) {
  fnd_assert(paranoid, array != NULL);
  fnd_assert(paranoid, array->copy_ != NULL);
  fnd_assert(paranoid, suffixes != NULL);
  fnd_assert(paranoid, suffixes_sz != 0);
  fnd_array_coup_(array);
  const size_t min = array->copy_->size + suffixes_sz;
  if (array->copy_->size < min) {
    _Elem *elements = (_Elem *)
      fnd_allocator_alloc(
        array->copy_->allocator,
        min * sizeof(_Elem),
        fnd_alignof(_Elem));
    memcpy(
      (void *)&elements[0],
      (const void *)array->copy_->elements,
      array->copy_->size);
    memcpy(
      (void *)&elements[array->copy_->size],
      (const void *)suffixes,
      suffixes_sz * sizeof(_Elem));
    fnd_allocator_free(
      array->copy_->allocator,
      (void *)array->copy_->elements);
    array->copy_->size = array->copy_->reserved = min;
    array->copy_->elements = elements;
  } else {
    memcpy(
      (void *)&array->copy_->elements[array->copy_->size],
      (const void *)suffixes,
      suffixes_sz * sizeof(_Elem));
    array->copy_->size += suffixes_sz;
  }
}

/*! */
template <typename _Elem>
void fnd_array_append(fnd_array_t<_Elem> *array, const _Elem *suffix) {
  fnd_assert(debug, array != NULL);
  fnd_assert(debug, array->copy_ != NULL);
  fnd_array_deepen(array);
  fnd_array_rshift_(array, suffix, 1);
}

/*! */
template <typename _Elem>
void fnd_array_append(fnd_array_t<_Elem> *array, const fnd_array_t<_Elem> *suffix) {
  fnd_assert(debug, array != suffix);
  fnd_assert(debug, array != NULL);
  fnd_assert(debug, array->copy_ != NULL);
  if (!suffix->copy_ || (suffix->copy_->size == 0))
    return;
  fnd_array_deepen(array);
  fnd_array_rshift_(array, suffix->copy_->elements, suffix->copy_->size);
}

/* ========================================================================== */

/*! */
template <typename _Elem>
size_t fnd_array_size(const fnd_array_t<_Elem> *array) {
  fnd_assert(debug, array != NULL);
  return (array->copy_ ? array->copy_->size : 0);
}

/*! */
template <typename _Elem>
void fnd_array_resize(fnd_array_t<_Elem> *array, const size_t size) {
  fnd_assert(debug, array != NULL);
  fnd_assert(debug, array->copy_ != NULL);
  fnd_array_deepen(array);
  /* TODO(mtwilliams): Use non_pod_aware_destruct<T> to support non-POD. */
  fnd_allocator_realloc(
    array->copy_->allocator,
    (void *)array->copy_->elements,
    size * sizeof(_Elem),
    fnd_alignof(_Elem));
  array->copy_->size = array->copy_->reserved = size;
}

/*! */
template <typename _Elem>
size_t fnd_array_reserved(const fnd_array_t<_Elem> *array) {
  fnd_assert(debug, array != NULL);
  return (array->copy_ ? array->copy_->reserved : 0);
}

/*! */
template <typename _Elem>
void fnd_array_reserve(fnd_array_t<_Elem> *array, const size_t additional) {
  fnd_assert(debug, array != NULL);
  fnd_assert(debug, array->copy_ != NULL);
  fnd_array_deepen(array);
  /* TODO(mtwilliams): Use non_pod_aware_destruct<T> to support non-POD. */
  fnd_allocator_realloc(
    array->copy_->allocator,
    (void *)array->copy_->elements,
    (array->copy_->reserved + additional) * sizeof(_Elem),
    fnd_alignof(_Elem));
  array->copy_->reserved += additional;
}

#endif

/* ========================================================================== */
/*  C++ (foundation::array):                                                  */
/* ========================================================================== */

#ifdef __cplusplus
namespace foundation {
  /*! @copydoc fnd_array_t */
  template <typename _Elem>
  class array : private fnd_array_t<_Elem> {
    private:
      array(const array &);
      array &operator= (const array &);
    public:
      array();
      array(allocator *allocator);
      array(allocator *allocator, const size_t reserve);
      ~array();
    public:
      _Elem &at(const size_t index);
      _Elem &operator [](const size_t index);
      const _Elem &at(const size_t index) const;
      const _Elem &operator [](const size_t index) const;
    public:
      void copy(array<_Elem> &copy) const;
      void deepen();
      bool copy_on_write() const;
    public:
      void clear();
      void prepend(const _Elem &prefix);
      void prepend(const array<_Elem> &prefix);
      void append(const _Elem &suffix);
      void append(const array<_Elem> &suffix);
    public:
      size_t size() const;
      void resize(const size_t size);
      size_t reserved() const;
      void reserve(const size_t additional);
  };

  #include <foundation/array.inl>
} /* foundation */
#endif

#endif /* _FOUNDATION_ARRAY_H_ */
