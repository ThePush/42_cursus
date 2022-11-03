#include "WrongCat.hpp"
#include "colors.hpp"

WrongCat::WrongCat()
    : WrongAnimal() {
    this->m_type = "WrongCat";
    std::cout << KYEL "WrongCat class: [" << this->m_type << "] default constructor called" KNRM << std::endl;
}

WrongCat::WrongCat(const WrongCat& src)
    : WrongAnimal() {
    this->m_type = src.m_type;
    std::cout << KYEL "WrongCat class: [" << m_type << "] Copy constructor called" KNRM << std::endl;
}

WrongCat::~WrongCat() {
    std::cout << KYEL "WrongCat class: [" << m_type << "] Destructor called" KNRM << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& rhs) {
    std::cout << KYEL "WrongCat class: [" << m_type << "] Assignment operator called" KNRM << std::endl;

    if (this != &rhs)
        this->m_type = rhs.m_type;

    return *this;
}

void WrongCat::makeSound(void) const {
    std::cout << KGRN "WrongCat class: [" << m_type << "] makeSound() called: Meow" KNRM << std::endl;
}