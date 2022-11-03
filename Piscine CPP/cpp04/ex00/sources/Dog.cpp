#include "Dog.hpp"
#include "colors.hpp"

Dog::Dog()
    : Animal() {
    this->m_type = "Dog";
    std::cout << KYEL "Dog class: [" << this->m_type << "] default constructor called" KNRM << std::endl;
}

Dog::Dog(const Dog& src)
    : Animal() {
    this->m_type = src.m_type;
    std::cout << KYEL "Dog class: [" << m_type << "] Copy constructor called" KNRM << std::endl;
}

Dog::~Dog() {
    std::cout << KYEL "Dog class: [" << m_type << "] Destructor called" KNRM << std::endl;
}

Dog& Dog::operator=(const Dog& rhs) {

    if (this != &rhs)
        this->m_type = rhs.m_type;

    std::cout << KYEL "Dog class: [" << m_type << "] Assignment operator called" KNRM << std::endl;

    return *this;
}

void Dog::makeSound(void) const {
    std::cout << KGRN "Dog class: [" << m_type << "] makeSound() called: Bark" KNRM << std::endl;
}