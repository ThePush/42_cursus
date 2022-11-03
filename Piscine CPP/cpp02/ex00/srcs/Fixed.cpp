#include "Fixed.hpp"

Fixed::Fixed()
    : _raw_bits(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const& src) {
    std::cout << "Copy constructor called" << std::endl;

    *this = src;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;

    return this->_raw_bits;
}

Fixed& Fixed::operator=(Fixed const& rhs) {
    std::cout << "Copy assignment operator called" << std::endl;

    if (this != &rhs)
        this->_raw_bits = rhs.getRawBits();

    return *this;
}

void Fixed::setRawBits(int const raw) {
    this->_raw_bits = raw;
}