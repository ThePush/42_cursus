#include "WrongAnimal.hpp"
#include "colors.hpp"

WrongAnimal::WrongAnimal()
    : m_type("WrongAnimal") {
    std::cout << KYEL "WrongAnimal class: [" << this->m_type << "] default constructor called" KNRM << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& src)
    : m_type(src.m_type) {
    std::cout << KYEL "WrongAnimal class: [" << m_type << "] Copy constructor called" KNRM << std::endl;
}

WrongAnimal::~WrongAnimal() {
    std::cout << KYEL "WrongAnimal class: [" << m_type << "] Destructor called" KNRM << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& rhs) {

    if (this != &rhs)
        this->m_type = rhs.m_type;

    std::cout << KYEL "WrongAnimal class: [" << m_type << "] Assignment operator called" KNRM << std::endl;

    return *this;
}

std::string WrongAnimal::getType(void) const {
    return this->m_type;
}

void WrongAnimal::makeSound(void) const {
    std::cout << KGRN "WrongAnimal class: [" << m_type << "] makeSound() called: ..." KNRM << std::endl;
}