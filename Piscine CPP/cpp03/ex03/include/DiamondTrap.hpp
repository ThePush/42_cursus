#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

#include <iostream>

class DiamondTrap : public ScavTrap, public FragTrap {
public:
    DiamondTrap(std::string const& name = "DefaultDiamond");
    DiamondTrap(const DiamondTrap& src);
    ~DiamondTrap();
    DiamondTrap& operator=(const DiamondTrap& rhs);

    void attack(const std::string& target);
    void whoAmI(void);

private:
    std::string m_name;
};

#endif