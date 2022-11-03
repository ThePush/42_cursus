#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#pragma once

namespace ft {

// ft::is_integral
template <class T>
struct is_integral { static const bool value = false; };
template <>
struct is_integral<bool> { static const bool value = true; };
template <>
struct is_integral<char> { static const bool value = true; };
template <>
struct is_integral<signed char> { static const bool value = true; };
template <>
struct is_integral<unsigned char> { static const bool value = true; };
template <>
struct is_integral<wchar_t> { static const bool value = true; };
template <>
struct is_integral<short> { static const bool value = true; };
template <>
struct is_integral<unsigned short> { static const bool value = true; };
template <>
struct is_integral<int> { static const bool value = true; };
template <>
struct is_integral<unsigned int> { static const bool value = true; };
template <>
struct is_integral<long> { static const bool value = true; };
template <>
struct is_integral<unsigned long> { static const bool value = true; };
template <>
struct is_integral<long long> { static const bool value = true; };
template <>
struct is_integral<unsigned long long> { static const bool value = true; };

// ft::enable_if
// @brief: A template that is only defined if the boolean is true.
template <bool B, class T = void>
struct enable_if { };

// @brief: Defining a type `type` that is the same as `T` if the boolean is true.
template <class T>
struct enable_if<true, T> { typedef T type; };

} // namespace ft

#endif // TYPE_TRAITS_HPP