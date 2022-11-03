#include <cstdlib>
#include <cstring>
#include <iostream>

int main(void) {

    std::string string = "HI THIS IS BRAIN";

    std::string* stringPTR = &string;
    std::string& stringREF = string;

    std::cout << std::endl
              << " memory adress of the string variable: " << &string << std::endl;
    std::cout << " memory adress held by stringPTR: " << stringPTR << std::endl;
    std::cout << " memory adress held by stringREF: " << &stringREF << std::endl
              << std::endl;

    std::cout << " value of the string variable: " << string << std::endl;
    std::cout << " value pointed to by stringPTR: " << *stringPTR << std::endl;
    std::cout << " value pointed to by stringREF: " << stringREF << std::endl
              << std::endl;

    return EXIT_SUCCESS;
}