#include "colors.hpp"

#include "whatever.hpp"

#include <cstdlib>
#include <iostream>

int main() {

    std::cout << KMAG;

    std::cout << KMAG "========================= [ TEST ] Templates ======================" << std::endl
              << std::endl;

    std::cout << KMAG "----------------- [ Test with type int ] -----------------" << std::endl
              << std::endl;

    int int_a = 42, int_b = 1337;

    std::cout << " Initial value of a: " << int_a << std::endl
              << " Initial value of b: " << int_b << std::endl
              << std::endl;

    std::cout << " Call to max(a,b): " << max(int_a, int_b) << std::endl;
    std::cout << " Call to min(a, b): " << min(int_a, int_b) << std::endl
              << std::endl;

    std::cout << " Call to swap(a, b)" << std::endl;
    swap(int_a, int_b);

    std::cout << " New value a: " << int_a << std::endl
              << " New value of b: " << int_b << std::endl
              << std::endl;

    std::cout << KMAG "----------------- [ Test with type float ] -----------------" << std::endl
              << std::endl;

    float float_a = 4.2f, float_b = 13.37f;

    std::cout << " Initial value of a: " << float_a << std::endl
              << " Initial value of b: " << float_b << std::endl
              << std::endl;

    std::cout << " Call to max(a,b): " << max(float_a, float_b) << std::endl;
    std::cout << " Call to min(a, b): " << min(float_a, float_b) << std::endl
              << std::endl;

    std::cout << " Call to swap(a, b)" << std::endl;
    swap(float_a, float_b);

    std::cout << " New value a: " << float_a << std::endl
              << " New value of b: " << float_b << std::endl
              << std::endl;

    std::cout << KMAG "----------------- [ Test with type char ] -----------------" << std::endl
              << std::endl;

    char char_a = 'A', char_b = 'Z';

    std::cout << " Initial value of a: " << char_a << std::endl
              << " Initial value of b: " << char_b << std::endl
              << std::endl;

    std::cout << " Call to max(a,b): " << max<char>(char_a, char_b) << std::endl;
    std::cout << " Call to min(a, b): " << min<char>(char_a, char_b) << std::endl
              << std::endl;

    std::cout << " Call to swap(a, b)" << std::endl;
    swap<char>(char_a, char_b);

    std::cout << " New value a: " << char_a << std::endl
              << " New value of b: " << char_b << std::endl
              << std::endl;

    std::cout << KMAG "----------------- [ Test with type string ] -----------------" << std::endl
              << std::endl;

    std::string str_a = "Hello", str_b = "World";

    std::cout << " Initial value of a: " << str_a << std::endl
              << " Initial value of b: " << str_b << std::endl
              << std::endl;

    std::cout << " Call to max(a,b): " << ::max(str_a, str_b) << std::endl;
    std::cout << " Call to min(a, b): " << ::min(str_a, str_b) << std::endl
              << std::endl;

    std::cout << " Call to swap(a, b)" << std::endl;
    swap(str_a, str_b);

    std::cout << " New value a: " << str_a << std::endl
              << " New value of b: " << str_b << std::endl;

    std::cout << KNRM;

    return EXIT_SUCCESS;
}

// Subject's main:

// int main( void ) {
// int a = 2;
// int b = 3;
//::swap( a, b );
// std::cout << "a = " << a << ", b = " << b << std::endl;
// std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
// std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
// std::string c = "chaine1";
// std::string d = "chaine2";
//::swap(c, d);
// std::cout << "c = " << c << ", d = " << d << std::endl;
// std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
// std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
// return 0;
// }