#ifndef PAIR_HPP
#define PAIR_HPP

#pragma once

namespace ft {

template <class T1, class T2>
struct pair {
    /* MEMBER TYPES */
    typedef T1 first_type;
    typedef T2 second_type;

    /* MEMBER OBJECTS */
    first_type first;
    second_type second;

    /* MEMBER FUNCTIONS */
    pair()
        : first(), second() { }

    pair(const pair& p)
        : first(p.first), second(p.second) { }

    pair(const first_type& x, const second_type& y)
        : first(x), second(y) { }

    template <class U1, class U2>
    pair(const pair<U1, U2>& p)
        : first(p.first), second(p.second) { }

    pair& operator=(const pair& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
}; // struct pair

/* NON-MEMBER FUNCTIONS */
// @brief: Return a pair of type T1 and T2.
template <class T1, class T2>
ft::pair<T1, T2> make_pair(T1 t, T2 u) { return pair<T1, T2>(t, u); }

// Relational operators
template <class T1, class T2>
bool operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; }
template <class T1, class T2>
bool operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return !(lhs == rhs); }
template <class T1, class T2>
bool operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }
template <class T1, class T2>
bool operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return rhs < lhs; }
template <class T1, class T2>
bool operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return !(rhs < lhs); }
template <class T1, class T2>
bool operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return !(lhs < rhs); }

} // namespace ft

#endif // PAIR_HPP