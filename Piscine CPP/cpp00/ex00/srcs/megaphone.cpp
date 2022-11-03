#include <iostream>
#include <cstdlib>

/**
 * It takes a list of strings as input, and prints them in uppercase
 * 
 * @param ac the number of arguments passed to the program
 * @param av array of strings
 * 
 * @return The program is returning the exit status of the program.
 */
int main(int ac, char** av) {

    if (ac == 1) {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    } else {
        for (int i(1); i != ac; ++i)
            for (size_t j(0); j != static_cast<std::string>(av[i]).length(); ++j)
                std::cout << static_cast<char>(toupper(av[i][j]));
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
