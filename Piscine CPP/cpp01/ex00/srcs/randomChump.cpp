#include "Zombie.hpp"

#include <iostream>

/**
 * "Create a Zombie object, call its announce method, and then let the object go out of scope."
 * 
 * The Zombie object is created on the stack, and when the function ends, the object is destroyed
 * 
 * @param name The name of the zombie.
 */
void randomChump(std::string name) {
    Zombie zombie(name);
    zombie.announce();
}