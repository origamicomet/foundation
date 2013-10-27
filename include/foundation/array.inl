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
/*! @file include/foundation/array.inl
     Aliases foundation::array's constructor, destructors, and methods.       */
/* ========================================================================== */

#ifndef _FOUNDATION_ARRAY_INL_
#define _FOUNDATION_ARRAY_INL_

/*! @copydoc fnd_array_create */
template <typename _Elem>
array<_Elem>::array() {
  fnd_array_create((fnd_array_t<_Elem> *)this);
}

/*! @copydoc fnd_array_create */
template <typename _Elem>
array<_Elem>::array(allocator *allocator) {
  fnd_array_create((fnd_array_t<_Elem> *)this, (fnd_allocator_t *)allocator);
}

/*! @copydoc fnd_array_create */
template <typename _Elem>
array<_Elem>::array(allocator *allocator, const size_t reserve) {
  fnd_array_create((fnd_array_t<_Elem> *)this, (fnd_allocator_t *)allocator, reserve);
}

/*! @copydoc fnd_array_destroy */
template <typename _Elem>
array<_Elem>::~array() {
  fnd_array_destroy((fnd_array_t<_Elem> *)this);
}

/*! @copydoc fnd_array_at */
template <typename _Elem>
_Elem &array<_Elem>::at(const size_t index) {
  return *fnd_array_at((fnd_array_t<_Elem> *)this, index);
}

/*! @copydoc fnd_array_at */
template <typename _Elem>
_Elem &array<_Elem>::operator [](const size_t index) {
  return at(index);
}

/*! @copydoc fnd_array_at */
template <typename _Elem>
const _Elem &array<_Elem>::at(const size_t index) const {
  return *fnd_array_at((const fnd_array_t<_Elem> *)this, index);
}

/*! @copydoc fnd_array_at */
template <typename _Elem>
const _Elem &array<_Elem>::operator [](const size_t index) const {
  return at(index);
}

/*! @copydoc fnd_array_copy */
template <typename _Elem>
void array<_Elem>::copy(array<_Elem> &copy) const {
  fnd_array_copy((const fnd_array_t<_Elem> *)this, (fnd_array_t<_Elem> *)&copy);
}

/*! @copydoc fnd_array_deepen */
template <typename _Elem>
void array<_Elem>::deepen() {
  fnd_array_deepen((fnd_array_t<_Elem> *)this);
}

/*! @copydoc fnd_array_copy_on_write */
template <typename _Elem>
bool array<_Elem>::copy_on_write() const {
  return fnd_array_copy_on_write((const fnd_array_t<_Elem> *)this);
}

/*! @copydoc fnd_array_clear */
template <typename _Elem>
void array<_Elem>::clear() {
  return fnd_array_clear((fnd_array_t<_Elem> *)this);
}

/*! @copydoc fnd_array_prepend */
template <typename _Elem>
void array<_Elem>::prepend(const _Elem &prefix) {
  return fnd_array_prepend((fnd_array_t<_Elem> *)this, &prefix);
}

/*! @copydoc fnd_array_prepend */
template <typename _Elem>
void array<_Elem>::prepend(const array<_Elem> &prefix) {
  return fnd_array_prepend((fnd_array_t<_Elem> *)this, (const fnd_array_t<_Elem> *)&prefix);
}

/*! @copydoc fnd_array_append */
template <typename _Elem>
void array<_Elem>::append(const _Elem &suffix) {
  return fnd_array_append((fnd_array_t<_Elem> *)this, &suffix);
}

/*! @copydoc fnd_array_append */
template <typename _Elem>
void array<_Elem>::append(const array<_Elem> &suffix) {
  return fnd_array_append((fnd_array_t<_Elem> *)this, (const fnd_array_t<_Elem> *)&suffix);
}

/*! @copydoc fnd_array_size */
template <typename _Elem>
size_t array<_Elem>::size() const {
  return fnd_array_size((const fnd_array_t<_Elem> *)this);
}

/*! @copydoc fnd_array_resize */
template <typename _Elem>
void array<_Elem>::resize(const size_t size) {
  fnd_array_resize((fnd_array_t<_Elem> *)this, size);
}

/*! @copydoc fnd_array_reserved */
template <typename _Elem>
size_t array<_Elem>::reserved() const {
  return fnd_array_reserved((const fnd_array_t<_Elem> *)this);
}

/*! @copydoc fnd_array_reserve */
template <typename _Elem>
void array<_Elem>::reserve(const size_t additional) {
  fnd_array_reserve((fnd_array_t<_Elem> *)this, additional);
}

#endif /* _FOUNDATION_ARRAY_INL_ */
