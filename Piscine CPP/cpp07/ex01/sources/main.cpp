#include "colors.hpp"

#include "iter.hpp"

#include <cstdlib>
#include <iostream>

int main(void) {

    std::cout << KMAG;

    std::cout << KMAG "========================= [ TEST ] Templates ======================" << std::endl
              << std::endl;

    int int_arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    double double_arr[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    float float_arr[] = { 0.0f, 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f };
    char char_arr[] = { "Lorem ipsum dolor" };

    std::cout << "template_print(): Print integers: ";
    iter(int_arr, arrsize(&int_arr), template_print);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "template_print(): Print doubles: ";
    iter(double_arr, arrsize(&double_arr), template_print);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "template_print(): Print floats: ";
    iter(float_arr, arrsize(&float_arr), template_print);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "template_print(): Print derpified characters: ";
    iter(char_arr, arrsize(&char_arr), template_print);
    std::cout << std::endl
              << std::endl;

    std::cout << KNRM;

    return EXIT_SUCCESS;
}
