#ifndef FIXED_HPP
#define FIXED_HPP

#include <cmath>
#include <exception>
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

    bool operator>(const Fixed& rhs) const;
    bool operator<(const Fixed& rhs) const;
    bool operator>=(const Fixed& rhs) const;
    bool operator<=(const Fixed& rhs) const;
    bool operator==(const Fixed& rhs) const;
    bool operator!=(const Fixed& rhs) const;

    Fixed operator+(const Fixed& rhs) const;
    Fixed operator-(const Fixed& rhs) const;
    Fixed operator*(const Fixed& rhs) const;
    Fixed operator/(const Fixed& rhs) const;

    Fixed& operator++(void);
    Fixed& operator--(void);
    Fixed operator++(int);
    Fixed operator--(int);

    static Fixed& min(Fixed& a, Fixed& b);
    static Fixed& max(Fixed& a, Fixed& b);
    static const Fixed min(const Fixed& a, const Fixed& b);
    static const Fixed max(const Fixed& a, const Fixed& b);

private:
    int _raw_bits;
    static const int _FRACTIONAL_BITS = 8;
};

std::ostream& operator<<(std::ostream& output, Fixed const& fixed);

#endif