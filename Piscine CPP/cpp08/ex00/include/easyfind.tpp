#ifndef EASYFIND_TPP
#define EASYFIND_TPP

#pragma once

#include <algorithm>

// A template function that takes a container and a needle and returns the iterator of the needle in the container.
template <typename T>
typename T::iterator easyfind(T& hay, int needle) {
    if (hay.empty() or (find(hay.begin(), hay.end(), needle) == hay.end()))
        throw std::exception();
    return find(hay.begin(), hay.end(), needle);
}

#endif