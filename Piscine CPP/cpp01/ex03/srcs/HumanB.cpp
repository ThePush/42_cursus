#include "HumanB.hpp"
#include "Weapon.hpp"

#include <cstring>
#include <iostream>

HumanB::HumanB(std::string const& name)
    : _name(name) { }

HumanB::~HumanB() { }

void HumanB::attack(void) {
    std::cout << this->_name << " attacks with their weapon ";

    if (not(this->_weapon))
        std::cout << "....wait, actually " << this->_name << " does not have any weapon" << std::endl;
    else
        std::cout << this->_weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon& weapon) {
    this->_weapon = &weapon;
}