#ifndef FIXED_HPP
#define FIXED_HPP

#include <cmath>
#include <iostream>

class Fixed {
public:
    Fixed();
    Fixed(Fixed const& src);
    Fixed(const int integer);
    Fixed(const float floating_point_number);
    ~Fixed();

    Fixed& operator=(Fixed const& rhs);

    int getRawBits(void) const;
    void setRawBits(int const raw);
    float toFloat(void) const;
    int toInt(void) const;

private:
    int _raw_bits;
    static const int _FRACTIONAL_BITS = 8;
};

std::ostream& operator<<(std::ostream& output, Fixed const& fixed);

#endif