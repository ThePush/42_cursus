#include "Harl.hpp"
#include "colors.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

static void check_arguments(int ac) {
    if (ac != 2) {
        std::cout << KRED " Error:" << std::endl
                  << "  • Only one argument needed" << std::endl
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

    check_arguments(ac);

    Harl harl;

    harl.complain(std::string(av[1]));

    return EXIT_SUCCESS;
}