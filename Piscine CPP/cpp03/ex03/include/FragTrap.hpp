#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

#include <iostream>

class FragTrap : virtual public ClapTrap {
public:
    FragTrap(std::string const& name = "DefaultFrag");
    FragTrap(const FragTrap& src);
    ~FragTrap();
    FragTrap& operator=(const FragTrap& rhs);

    void attack(const std::string& target);
    void highFivesGuys(void);
};

#endif