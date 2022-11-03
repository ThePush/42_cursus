#include "Zombie.hpp"

Zombie::Zombie(std::string name)
    : _name(name) {
    std::cout << KGRN << this->_name << ": has been created" KNRM << std::endl;
}

Zombie::~Zombie() {
    std::cout << KRED << this->_name << ": has been destructed" KNRM << std::endl;
}

void Zombie::announce(void) const {
    std::cout << KBLU << this->_name << ": BraiiiiiiinnnzzzZ..." KNRM << std::endl;
}