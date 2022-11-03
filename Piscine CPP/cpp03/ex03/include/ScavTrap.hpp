#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

#include <iostream>

class ScavTrap : virtual public ClapTrap {
public:
    ScavTrap(std::string const& name = "DefaultScav");
    ScavTrap(const ScavTrap& src);
    ~ScavTrap();
    ScavTrap& operator=(const ScavTrap& rhs);

    void attack(const std::string& target);
    void guardGate(void);
};

#endif