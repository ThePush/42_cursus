#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

#pragma once

namespace ft {

// ft::binary_function
template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
}; // struct binary_function

// ft::less
template <class T>
struct less : ft::binary_function<T, T, bool> {
    typedef bool result_type;
    typedef T first_argument_type;
    typedef T second_argument_type;

    bool operator()(const T& lhs, const T& rhs) const { return lhs < rhs; }
}; // struct less

} // namespace ft

#endif // FUNCTIONAL_HPP