#include "Fixed.hpp"

Fixed::Fixed()
    : _raw_bits(0) { std::cout << "Default constructor called" << std::endl; }

Fixed::Fixed(Fixed const& src) {
    std::cout << "Copy constructor called" << std::endl;

    *this = src;

}

/**
 * It takes an integer as a parameter, multiplies it by 2 to the power of 8, and then sets the value of
 * _raw_bits to the result of that multiplication
 * 
 * @param integer the integer value to be converted to a Fixed point number
 */
Fixed::Fixed(const int integer) {
    std::cout << "Int constructor called" << std::endl;

    setRawBits(integer * (1 << _FRACTIONAL_BITS));
    // std::cout << _raw_bits << std::endl;
}

/**
 * It takes a floating point number, multiplies it by 2 to the power of 8, and rounds it to the nearest
 * integer
 * 
 * @param floating_point_number The floating point number to be converted to a Fixed point number.
 */
Fixed::Fixed(const float floating_point_number) {
    std::cout << "Float constructor called" << std::endl;

    setRawBits(roundf(floating_point_number * (1 << _FRACTIONAL_BITS)));
    // std::cout << _raw_bits << std::endl;
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

Fixed& Fixed::operator=(Fixed const& rhs) {
    std::cout << "Copy assignment operator called" << std::endl;

    if (this != &rhs)
        this->_raw_bits = rhs.getRawBits();

    return *this;
}

int Fixed::getRawBits(void) const { return _raw_bits; }
void Fixed::setRawBits(int const raw) { _raw_bits = raw; }

float Fixed::toFloat(void) const { return (float)_raw_bits / (float)(1 << _FRACTIONAL_BITS); }
int Fixed::toInt(void) const { return _raw_bits >> _FRACTIONAL_BITS; }

bool Fixed::operator==(const Fixed& rhs) const { return _raw_bits == rhs._raw_bits; }
bool Fixed::operator>(const Fixed& rhs) const { return _raw_bits > rhs._raw_bits; }
bool Fixed::operator>=(const Fixed& rhs) const { return _raw_bits >= rhs._raw_bits; }
bool Fixed::operator<(const Fixed& rhs) const { return _raw_bits < rhs._raw_bits; }
bool Fixed::operator<=(const Fixed& rhs) const { return _raw_bits <= rhs._raw_bits; }
bool Fixed::operator!=(const Fixed& rhs) const { return _raw_bits != rhs._raw_bits; }

Fixed Fixed::operator+(const Fixed& rhs) const {
    Fixed result;
    result._raw_bits = _raw_bits + rhs._raw_bits;

    return result;
}

Fixed Fixed::operator-(const Fixed& rhs) const {
    Fixed result;
    result._raw_bits = _raw_bits - rhs._raw_bits;

    return result;
}

Fixed Fixed::operator*(const Fixed& rhs) const {
    Fixed result;
    result._raw_bits = ((u_int64_t(_raw_bits) * u_int64_t(rhs.getRawBits())) / (1 << _FRACTIONAL_BITS));

    return result;
}

Fixed Fixed::operator/(const Fixed& rhs) const {
    if (rhs.toInt() != 0) {
        Fixed result;
        result._raw_bits = (((int64_t(_raw_bits) * (1 << _FRACTIONAL_BITS)) / rhs.getRawBits()));
        return result;
    } else
        throw std::logic_error("Error: division by 0");
}

Fixed& Fixed::operator++(void) {
    ++_raw_bits;

    return *this;
}

Fixed& Fixed::operator--(void) {
    --_raw_bits;

    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed tmp(*this);
    _raw_bits++;

    return tmp;
}

Fixed Fixed::operator--(int) {
    Fixed tmp(*this);
    _raw_bits--;

    return tmp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) { return (a < b ? a : b); }
Fixed& Fixed::max(Fixed& a, Fixed& b) { return (a > b ? a : b); }
const Fixed Fixed::min(const Fixed& a, const Fixed& b) { return (a < b ? a : b); }
const Fixed Fixed::max(const Fixed& a, const Fixed& b) { return (a > b ? a : b); }

std::ostream& operator<<(std::ostream& output, Fixed const& fixed) {
    output << fixed.toFloat();

    return output;
}
