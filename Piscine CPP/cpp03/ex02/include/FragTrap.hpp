#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

#include <iostream>

class FragTrap : public ClapTrap {
public:
    FragTrap(std::string const& name = "DefaultFrag");
    FragTrap(FragTrap const& src);
    ~FragTrap();
    FragTrap& operator=(const FragTrap& rhs);

    void attack(const std::string& target);
    void highFivesGuys(void);
};

#endif