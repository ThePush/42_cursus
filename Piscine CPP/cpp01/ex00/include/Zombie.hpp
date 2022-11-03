#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "colors.hpp"
#include <iostream>

class Zombie {
public:
	Zombie(std::string name = "Default");
    ~Zombie();

    void announce(void) const;

private:
    std::string _name;
};

#endif