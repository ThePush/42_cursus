#include "Weapon.hpp"
#include <cstring>
#include <iostream>

Weapon::Weapon(std::string const& type)
    : _type(type) {}

Weapon::~Weapon() {}


std::string const Weapon::getType(void) const { return _type; }

void Weapon::setType(std::string const& newtype) { this->_type = newtype; }