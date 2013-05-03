// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_COMPAT_TYPE_TRAITS_H_
#define _FOUNDATION_COMPAT_TYPE_TRAITS_H_

// Aliases (and provides fallbacks) for C++11 type_trait information.

#include <foundation/detect.h>

#include <type_traits>

namespace foundation {
  // Determines if a type |T| is void.
  template <typename T>
  struct is_void {
    static const bool value = std::is_void<T>; };

  // Determines if a type |T| is an integral type.
  template <typename T>
  struct is_integral {
    static const bool value = std::is_integral<T>; };

  // Determines if a type |T| is a floating-point type.
  template <typename T>
  struct is_floating_point {
    static const bool value = std::is_floating_point<T>; };

  // Determines if a type |T| is an array.
  template <typename T>
  struct is_array {
    static const bool value = std::is_array<T>; };

  // Determines if a type |T| is an enumerator.
  template <typename T>
  struct is_enum {
    static const bool value = std::is_enum<T>; };

  // Determines if a type |T| is an union.
  template <typename T>
  struct is_union {
    static const bool value = std::is_union<T>; };

  // Determines if a type |T| is a class (but not a union).
  template <typename T>
  struct is_class {
    static const bool value = std::is_class<T>; };

  // Determines if a type |T| is a function.
  template <typename T>
  struct is_function {
    static const bool value = std::is_function<T>; };

  // Determines if a type |T| is a pointer.
  template <typename T>
  struct is_pointer {
    static const bool value = std::is_pointer<T>; };

  // Determines if a type |T| is l-value reference.
  template <typename T>
  struct is_lvalue_reference {
    static const bool value = std::is_lvalue_reference<T>; };

  // Determines if a type |T| is a r-value reference.
  template <typename T>
  struct is_rvalue_reference {
    static const bool value = std::is_rvalue_reference<T>; };

  // Determines if a type |T| is a pointer to a non-static member object.
  template <typename T>
  struct is_member_object_pointer {
    static const bool value = std::is_member_object_pointer<T>; };

  // Determines if a type |T| is a pointer to a non-static member function.
  template <typename T>
  struct is_member_function_pointer {
    static const bool value = std::is_member_function_pointer<T>; };

  // Determines if a type |T| is a primitive and qualifierless.
  template <typename T>
  struct is_fundamental {
    static const bool value = std::is_fundamental<T>; };

  // Determines if a type |T| is an integral or floating-point type.
  template <typename T>
  struct is_arithmetic {
    static const bool value = std::is_arithmetic<T>; };

  // Determines if a type |T| is an arithmetic type, enumarator, pointer, or nullptr.
  template <typename T>
  struct is_scalar {
    static const bool value = std::is_scalar<T>; };

  // Determines if a type |T| is a scalar, array, class, or union.
  template <typename T>
  struct is_object {
    static const bool value = std::is_object<T>; };

  // Determines if a type |T| is an array, function, object pointer, function
  // pointer, reference, class, union, or enumerator.
  template <typename T>
  struct is_compound {
    static const bool value = std::is_compound<T>; };

  // Determines if a type |T| is a l-value or r-value reference.
  template <typename T>
  struct is_reference {
    static const bool value = std::is_reference<T>; };

  // Determines if a type |T| is a non-static member object or pointer to a
  // non-static member function.
  template <typename T>
  struct is_member_pointer {
    static const bool value = std::is_member_pointer<T>; };

  // Determines if a type |T| is const-qualified.
  template <typename T>
  struct is_const {
    static const bool value = std::is_const<T>; };

  // Determines if a type |T| is volatile-qualified.
  template <typename T>
  struct is_volatile {
    static const bool value = std::is_volatile<T>; };

  // Determines if a type |T| is trivially copyable.
  template <typename T>
  struct is_trivially_copyable {
    static const bool value =
      std::has_trivial_assign<T>::value &&
      std::has_trivial_constructor<T>::value &&
      std::has_trivial_copy_constructor<T>::value &&
      std::has_trivial_default_constructor<T>::value &&
      std::has_trivial_destructor<T>::value; };

  // Determines if a type |T| is trivial.
  template <typename T>
  struct is_trivial {
    static const bool value = is_trivially_copyable<T>; };

  // Determines if a type |T| is standard layout (no v-tables, et cetra).
  template <typename T>
  struct is_standard_layout {
    static const bool value = std::is_standard_layout<T>; };

  // Determines if a type |T| is plain-old-data.
  template <typename T>
  struct is_pod {
    static const bool value = std::is_pod<T>; };

  // Determines if a type |T| is literal type (trivial destructor, constructor
  // and initializers are constant expressions).
  template <typename T>
  struct is_literal_type {
    static const bool value = std::is_literal_type<T>; };

  // Determines if a type |T| is empty.
  template <typename T>
  struct is_empty {
    static const bool value = std::is_empty<T>; };

  // Determines if a type |T| declares at least one virtual function.
  template <typename T>
  struct is_polymorphic {
    static const bool value = std::is_polymorphic<T>; };

  // Determines if a type |T| is an abstract class (declares or inherits at
  // least one pure virtual function).
  template <typename T>
  struct is_abtract {
    static const bool value = std::is_abtract<T>; };

  // Determines if a type |T| is a signed arithmetic type.
  template <typename T>
  struct is_signed {
    static const bool value = std::is_signed<T>; };

  // Determines if a type |T| is an unsigned arithmetic type.
  template <typename T>
  struct is_unsigned {
    static const bool value = std::is_unsigned<T>; };

  #if !defined(FOUNDATION_COMPILER_SUPPORTS_ALIGNMENT)
    template <class T>
    struct alignment_of {
      struct __helper {
        char __0; T __1;
      };

      static const size_t value =
        (offsetof(alignment_of<T>::__helper, __1));
    };
  #else
    template <class T>
    struct alignment_of {
      static const size_t value = std::alignment_of<T>::value; };
  #endif

  // Typedefs a type |T| if |B| is true.
  template <bool B, typename T>
  struct enable_if {
    typedef typename std::enable_if<B, T>::type type; };
  template <typename T> struct enable_if<false, T> {};

  // Typedefs a type |T| if |B| is false.
  template <bool B, typename T>
  struct disable_if {
    typedef typename std::enable_if<!B, T>::type type; };
  template <typename T> struct disable_if<true, T> {};

  // Typedefs a type |T1| if |B| is true, and |T2| if false.
  template <bool B, typename T1, typename T2>
  struct conditional {
    typedef typename std::conditional<B, T1, T2>::type type; };
} // foundation

#endif // _FOUNDATION_COMPAT_TYPE_TRAITS_H_
