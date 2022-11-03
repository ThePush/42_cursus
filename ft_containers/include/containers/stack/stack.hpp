#ifndef STACK_HPP
#define STACK_HPP

#pragma once

#include "../vector/vector.hpp"
// ft::stack must be compatible with std::deque and std::list
//#include <deque>
//#include <list>

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {

    /* MEMBER OBJECT */
protected:
    Container c;

    /* MEMBER TYPES */
public:
    typedef Container container_type;

    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

    /* MEMBER FUNCTIONS */
    // constructor
    explicit stack(const container_type& ctnr = container_type())
        : c(ctnr) {};

    // destructor
    ~stack() {};

    // copy assign constructor
    stack& operator=(const stack& other) {
        c = other.c;
        return *this;
    }

    /* ELEMENT ACCESS */
    value_type& top() { return c.back(); }
    const value_type& top() const { return c.back(); }

    /* MODIFIERS */
    void push(const value_type& value) { c.push_back(value); }
    void pop() { c.pop_back(); }

    /* CAPACITY */
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }

    // Non-member functions declarations with friend keyword
    template <class Type, class Container_>
    friend bool operator==(const ft::stack<Type, Container_>& lhs, const ft::stack<Type, Container_>& rhs);
    template <class Type, class Container_>
    friend bool operator!=(const ft::stack<Type, Container_>& lhs, const ft::stack<Type, Container_>& rhs);
    template <class Type, class Container_>
    friend bool operator<(const ft::stack<Type, Container_>& lhs, const ft::stack<Type, Container_>& rhs);
    template <class Type, class Container_>
    friend bool operator<=(const ft::stack<Type, Container_>& lhs, const ft::stack<Type, Container_>& rhs);
    template <class Type, class Container_>
    friend bool operator>(const ft::stack<Type, Container_>& lhs, const ft::stack<Type, Container_>& rhs);
    template <class Type, class Container_>
    friend bool operator>=(const ft::stack<Type, Container_>& lhs, const ft::stack<Type, Container_>& rhs);

}; // class stack

/* NON-MEMBER FUNCTIONS */
template <class T, class C>
bool operator==(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) { return lhs.c == rhs.c; }
template <class T, class C>
bool operator!=(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) { return !(lhs == rhs); }
template <class T, class C>
bool operator<(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) { return lhs.c < rhs.c; }
template <class T, class C>
bool operator<=(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) { return lhs.c <= rhs.c; }
template <class T, class C>
bool operator>(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) { return lhs.c > rhs.c; }
template <class T, class C>
bool operator>=(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) { return lhs.c >= rhs.c; }

} // namespace ft

#endif // STACK_HPP