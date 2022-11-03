#include "Zombie.hpp"
#include "colors.hpp"

#include <iostream>

/**
 * It creates a horde of zombies with a given name
 * 
 * @param N the number of zombies to create
 * @param name the name of the zombie horde
 * 
 * @return A pointer to an array of Zombie objects.
 */
Zombie* zombieHorde(int N, std::string name) {

    if (N <= 0) {
        std::cerr << KRED "Error:" << std::endl
                  << " • Argument [number_of_zombies] must be a positive and superior to 0 integer" KNRM << std::endl;
        return NULL;
    }

    std::cout << KMAG " Memory allocation for an array of " << N << " zombies:" KNRM << std::endl;
    Zombie* horde = new Zombie[N];

    std::cout << std::endl;

    std::cout << KMAG " Initialization of the zombies:" KNRM << std::endl;
    for (int i(0); i != N; ++i)
        horde[i] = Zombie(name);

    return horde;
};
