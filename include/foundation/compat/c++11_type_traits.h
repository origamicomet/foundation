#include <type_traits>

namespace foundation {
  // Primary type categories:
  template <typename T> struct is_void { static const bool value = std::is_void<T>; };
  template <typename T> struct is_integral { static const bool value = std::is_integral<T>; };
  template <typename T> struct is_floating_point { static const bool value = std::is_floating_point<T>; };
  template <typename T> struct is_array { static const bool value = std::is_array<T>; };
  template <typename T> struct is_enum { static const bool value = std::is_enum<T>; };
  template <typename T> struct is_union { static const bool value = std::is_union<T>; };
  template <typename T> struct is_class { static const bool value = std::is_class<T>; };
  template <typename T> struct is_function { static const bool value = std::is_function<T>; };
  template <typename T> struct is_pointer { static const bool value = std::is_pointer<T>; };
  template <typename T> struct is_lvalue_reference { static const bool value = std::is_lvalue_reference<T>; };
  template <typename T> struct is_rvalue_reference { static const bool value = std::is_rvalue_reference<T>; };
  template <typename T> struct is_member_object_pointer { static const bool value = std::is_member_object_pointer<T>; };
  template <typename T> struct is_member_function_pointer { static const bool value = std::is_member_function_pointer<T>; };

  // Composite type categories:
  template <typename T> struct is_fundamental { static const bool value = std::is_fundamental<T>; };
  template <typename T> struct is_arithmetic { static const bool value = std::is_arithmetic<T>; };
  template <typename T> struct is_scalar { static const bool value = std::is_scalar<T>; };
  template <typename T> struct is_object { static const bool value = std::is_object<T>; };
  template <typename T> struct is_compound { static const bool value = std::is_compound<T>; };
  template <typename T> struct is_reference { static const bool value = std::is_reference<T>; };
  template <typename T> struct is_member_pointer { static const bool value = std::is_member_pointer<T>; };

  // Type properties:
  template <typename T> struct is_const { static const bool value = std::is_const<T>; };
  template <typename T> struct is_volatile { static const bool value = std::is_volatile<T>; };
  
  template <typename T> struct is_trivially_copyable;
  template <typename T> struct is_trivial { static const bool value = is_trivially_copyable<T>; };
  
  template <typename T>
  struct is_trivially_copyable {
    static const bool value =
      std::has_trivial_assign<T>::value &&
      std::has_trivial_constructor<T>::value &&
      std::has_trivial_copy_constructor<T>::value &&
      std::has_trivial_default_constructor<T>::value &&
      std::has_trivial_destructor<T>::value;
  };

  template <typename T> struct is_standard_layout { static const bool value = std::is_standard_layout<T>; };
  template <typename T> struct is_pod { static const bool value = std::is_pod<T>; };
  template <typename T> struct is_literal_type { static const bool value = std::is_literal_type<T>; };
  template <typename T> struct is_empty { static const bool value = std::is_empty<T>; };
  template <typename T> struct is_polymorphic { static const bool value = std::is_polymorphic<T>; };
  template <typename T> struct is_abtract { static const bool value = std::is_abtract<T>; };
  template <typename T> struct is_signed { static const bool value = std::is_signed<T>; };
  template <typename T> struct is_unsigned { static const bool value = std::is_unsigned<T>; };

  template <bool B, typename T>
  struct enable_if {
    typedef std::enable_if<B, T> type;
  };
} // foundation