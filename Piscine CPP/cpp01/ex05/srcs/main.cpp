#include "Harl.hpp"
#include "colors.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

static void check_arguments(int ac, char** av) {
    if (ac != 2
        or ((std::string(av[1]).compare("DEBUG"))
            and (std::string(av[1]).compare("INFO"))
            and (std::string(av[1]).compare("WARNING"))
            and (std::string(av[1]).compare("ERROR")))) {
        std::cout << KRED " Error:" << std::endl
                  << "  • Wrong argument" << std::endl
                  << std::endl
                  << KGRN " Usage:" << std::endl
                  << "  ./Harl_2.0 [level]" << std::endl
                  << std::endl
                  << "   Please enter one of those levels:" << std::endl
                  << "    • [DEBUG]" << std::endl
                  << "    • [INFO]" << std::endl
                  << "    • [WARNING]" << std::endl
                  << "    • [ERROR]" KNRM << std::endl;

        exit(EXIT_FAILURE);
    }
}

int main(int ac, char** av) {

    check_arguments(ac, av);

    Harl harl;

    harl.complain(std::string(av[1]));

    return EXIT_SUCCESS;
}