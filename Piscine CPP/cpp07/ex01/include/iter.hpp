#ifndef ITER_HPP
#define ITER_HPP

#include <cstdlib>
#include <iostream>
#include <typeinfo>

#include "utils.hpp"

// https://www.educative.io/answers/how-to-find-the-length-of-an-array-in-cpp
template <typename Type>
size_t arrsize(const Type* array) { return static_cast<size_t>((*(array + 1) - *array)); }

// https://en.cppreference.com/w/cpp/language/typeid
template <typename Type, typename Size>
void iter(Type* array, const Size& size, void (*fun)(const Type&)) {
    // std::cout << "[ Type of this function parameter is: (" << typeid(Type).name() << ") ]" << std::endl;
    for (Size i(0); i != size; ++i)
        fun(array[i]);
}

template <typename Type>
void template_print_derp(const Type& to_print) {
    bool random = random_number() % 2;
    if (random)
        std::cout << static_cast<char>(toupper(to_print));
    else
        std::cout << to_print;
}

template <typename Type>
void template_print(const Type& to_print) {
    if (not(static_cast<std::string>(typeid(Type).name()).compare("d"))
        or not(static_cast<std::string>(typeid(Type).name()).compare("f")))
        std::cout << to_print << " | ";
    else if (not(static_cast<std::string>(typeid(Type).name()).compare("i")))
        std::cout << to_print << ' ';
    else if (not(static_cast<std::string>(typeid(Type).name()).compare("c")))
        template_print_derp(to_print);
    else
        std::cout << to_print;
}

#endif