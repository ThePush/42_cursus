#include "Zombie.hpp"

#include <iostream>

/**
 * NewZombie() returns a pointer to a Zombie object.
 * 
 * @param name The name of the zombie.
 * 
 * @return A pointer to a Zombie object.
 */
Zombie* newZombie(std::string name) {
	return new Zombie(name);
}