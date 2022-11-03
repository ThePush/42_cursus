#include "HumanA.hpp"
#include "Weapon.hpp"
#include <cstring>
#include <iostream>

HumanA::HumanA(std::string const& name, Weapon& weapon)
    : _name(name)
    , _weapon(weapon) { }

HumanA::~HumanA() { }

void HumanA::attack(void) {
    std::cout << this->_name << " attacks with their weapon " << this->_weapon.getType() << std::endl;
}