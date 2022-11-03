#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"

#include <cstring>
#include <iostream>

class HumanA {
public:
    HumanA(std::string const& name, Weapon& weapon);
    ~HumanA();

    void attack(void);

private:
    std::string _name;
    Weapon& _weapon;
};

#endif