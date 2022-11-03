#include "Zombie.hpp"

#include <cstdlib>
#include <iostream>

void randomChump(std::string name);
Zombie* newZombie(std::string name);

int main(void) {

    randomChump("stack");

    std::cout << std::endl;

    Zombie* heap = newZombie("heap");
    heap->announce();
    delete heap;

    return EXIT_SUCCESS;
}