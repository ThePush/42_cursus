#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

#include <cstring>
#include <iostream>

class HumanB {
public:
    HumanB(std::string const& name = "Default");
    ~HumanB();

    void attack(void);
    void setWeapon(Weapon& weapon);

private:
    std::string _name;
    Weapon* _weapon;
};

#endif