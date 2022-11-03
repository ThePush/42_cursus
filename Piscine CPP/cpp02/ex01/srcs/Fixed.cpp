#include "Fixed.hpp"

Fixed::Fixed()
    : _raw_bits(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const& src) {
    std::cout << "Copy constructor called" << std::endl;

    *this = src;
}

/**
 * It takes an integer as a parameter, multiplies it by 2 to the power of 8 (256), and then sets the
 * raw bits to that value
 *
 * @param integer The integer value to be converted to a fixed point number.
 */
Fixed::Fixed(const int integer) {
    std::cout << "Int constructor called" << std::endl;

    setRawBits(integer * (1 << this->_FRACTIONAL_BITS));
}

/**
 * It takes a floating point number, multiplies it by 2 to the power of 8, and rounds it to the nearest
 * integer
 *
 * @param floating_point_number The floating point number to be converted to a Fixed point number.
 */
Fixed::Fixed(const float floating_point_number) {
    std::cout << "Float constructor called" << std::endl;

    setRawBits(roundf(floating_point_number * (1 << this->_FRACTIONAL_BITS)));
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

Fixed& Fixed::operator=(Fixed const& rhs) {
    std::cout << "Copy assignment operator called" << std::endl;

    if (this != &rhs)
        this->_raw_bits = rhs.getRawBits();

    return *this;
}

int Fixed::getRawBits(void) const { return this->_raw_bits; }
void Fixed::setRawBits(int const raw) { this->_raw_bits = raw; }

/**
 * Convert the fixed point number to a floating point number.
 *
 * @return A float.
 */
float Fixed::toFloat(void) const { return (float)this->_raw_bits / (float)(1 << this->_FRACTIONAL_BITS); }

/**
 * It returns the integer value of the fixed point number.
 *
 * @return The value of the fixed point number.
 */
int Fixed::toInt(void) const { return (this->_raw_bits >> this->_FRACTIONAL_BITS); }

std::ostream& operator<<(std::ostream& output, Fixed const& fixed) {
    output << fixed.toFloat();

    return output;
}