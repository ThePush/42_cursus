#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template <typename Type>
Type const& max(const Type& a, const Type& b) { return (a > b ? a : b); }

template <typename Type>
Type const& min(const Type& a, const Type& b) { return (a < b ? a : b); }

template <typename Type>
void swap(Type& a, Type& b) {
    Type tmp = a;
    a = b;
    b = tmp;
}

#endif