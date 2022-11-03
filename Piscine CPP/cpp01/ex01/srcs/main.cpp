#include "Zombie.hpp"

#include <cstdlib>
#include <iostream>

Zombie* zombieHorde(int N, std::string name);

int main(int ac, char** av) {

    if (ac != 3) {
        std::cerr << KRED " Error:" << std::endl
                  << " • Please enter two arguments" KNRM << std::endl
                  << KGRN " Usage:" << std::endl
                  << "  ./Moar_Brainz [number_of_zombies] [name_of_zombies]" KNRM << std::endl;

        exit(EXIT_FAILURE);
    }

    int nb_zombies = std::atoi(av[1]);
    if (nb_zombies < 1) {
        std::cerr << KRED "Error:" << std::endl
                  << " • Argument [number_of_zombies] must be a positive and superior to 0 integer" KNRM << std::endl;
        exit(EXIT_FAILURE);
    }

    Zombie* horde = zombieHorde(nb_zombies, av[2]);
    if (!horde)
        return EXIT_FAILURE;

    std::cout << std::endl;

    std::cout << KMAG " Call to announce():" KNRM << std::endl;
    for (int i(0); i != nb_zombies; ++i) {
        std::cout << KBLU "[" << i << "] " KNRM;
        horde[i].announce();
    }

    std::cout << std::endl;

    std::cout << KMAG " Destruction of the horde:" KNRM << std::endl;
    delete[] horde;

    return EXIT_SUCCESS;
}