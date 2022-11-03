#include "Animal.hpp"
#include "colors.hpp"

Animal::Animal()
    : m_type("Animal") {
    std::cout << KYEL "Animal class: [" << this->m_type << "] default constructor called" KNRM << std::endl;
}

Animal::Animal(const Animal& src)
    : m_type(src.m_type) {
    std::cout << KYEL "Animal class: [" << m_type << "] Copy constructor called" KNRM << std::endl;
}

Animal::~Animal() {
    std::cout << KYEL "Animal class: [" << m_type << "] Destructor called" KNRM << std::endl;
}

Animal& Animal::operator=(const Animal& rhs) {
    std::cout << KYEL "Animal class: [" << m_type << "] Assignment operator called" KNRM << std::endl;

    if (this != &rhs)
        this->m_type = rhs.m_type;

    return *this;
}

std::string Animal::getType(void) const {
    return this->m_type;
}

void Animal::makeSound(void) const {
    std::cout << KGRN "Animal class: [" << m_type << "] makeSound() called: ..." KNRM << std::endl;
}