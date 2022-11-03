#include "Fixed.hpp"

#include <iostream>

int main(void) {
    Fixed a;
    Fixed const b(Fixed(5.05f) * Fixed(2));
    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max(a, b) << std::endl;

    std::cout << std::endl;
    std::cout << "=================== Additional tests ======================" << std::endl
              << std::endl;
    Fixed c(50);
    Fixed d(2);
    std::cout << "c: " << c << std::endl
              << "d: " << d << std::endl
              << std::endl;
    std::cout << "[Operator +] (c + d) = " << std::endl
              << c + d << std::endl
              << std::endl;
    std::cout << "[Operator *] (c * d) = " << std::endl
              << c * d << std::endl
              << std::endl;
    try {
        std::cout << "[Operator /] (c / d) = " << std::endl
                  << c / d << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "[Operator -] (c - d) = " << std::endl
              << c - d << std::endl
              << std::endl;
    std::cout << "[Operator ==] (c == d) = " << (c == d ? "True" : "False") << std::endl
              << std::endl;
    std::cout << "[Operator >=] (c >= d) = " << (c >= d ? "True" : "False") << std::endl
              << std::endl;
    std::cout << "[Operator <=] (c <= d) = " << (c <= d ? "True" : "False") << std::endl
              << std::endl;
    std::cout << "[Operator !=] (c != d) = " << (c != d ? "True" : "False") << std::endl
              << std::endl;

    return 0;
}