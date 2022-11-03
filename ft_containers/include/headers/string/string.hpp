#ifndef STRING_HPP
#define STRING_HPP

#pragma once

#include <sstream>
#include <string>

namespace ft {

// ft::to_string
// template <typename T>
// std::string to_string(T value) { return static_cast<std::ostringstream*>(&(std::ostringstream() << value))->str(); }

template <typename T>
std::string to_string(T Number) {
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

} // namespace ft

#endif // STRING_HPP