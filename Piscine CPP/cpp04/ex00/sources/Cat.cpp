#include "Cat.hpp"
#include "colors.hpp"

Cat::Cat()
    : Animal() {
    this->m_type = "Cat";
    std::cout << KYEL "Cat class: [" << this->m_type << "] default constructor called" KNRM << std::endl;
}

Cat::Cat(const Cat& src)
    : Animal() {
    this->m_type = src.m_type;
    std::cout << KYEL "Cat class: [" << m_type << "] Copy constructor called" KNRM << std::endl;
}

Cat::~Cat() {
    std::cout << KYEL "Cat class: [" << m_type << "] Destructor called" KNRM << std::endl;
}

Cat& Cat::operator=(const Cat& rhs) {

    if (this != &rhs)
        this->m_type = rhs.m_type;

    std::cout << KYEL "Cat class: [" << m_type << "] Assignment operator called" KNRM << std::endl;

    return *this;
}

void Cat::makeSound(void) const {
    std::cout << KGRN "Cat class: [" << m_type << "] makeSound() called: Meow" KNRM << std::endl;
}