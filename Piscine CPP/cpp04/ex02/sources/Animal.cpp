#include "Animal.hpp"
#include "colors.hpp"

Animal::Animal() {
    this->m_type = "Animal";
    std::cout << KYEL "[" << this->m_type << "] Animal class default constructor called" KNRM << std::endl;
}

Animal::Animal(Animal const& src) {
    std::cout << KYEL "Animal class copy constructor called" KNRM << std::endl;

    *this = src;

    return;
}

Animal::~Animal() {
    std::cout << KYEL "[" << m_type << "] Animal class destructor called" KNRM << std::endl;
}

Animal& Animal::operator=(Animal const& rhs) {
    std::cout << "Animal class copy assignment operator called" << std::endl;

    if (this != &rhs)
        this->m_type = rhs.getType();

    return *this;
}

std::string Animal::getType(void) const {
    return this->m_type;
}

void Animal::makeSound(void) const {
    std::cout << KGRN "Animal class makeSound() called: ..." KNRM << std::endl;
}