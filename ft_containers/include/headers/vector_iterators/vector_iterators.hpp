#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#pragma once

#include "../iterator/iterator_traits.hpp"

namespace ft {
template <class T>
class vector_iterator {
private:
    /* MEMBER VARIABLES */
    T* _current;

public:
    /* MEMBER TYPES */
    typedef typename iterator_traits<T*>::difference_type difference_type;
    typedef typename iterator_traits<T*>::value_type value_type;
    typedef typename iterator_traits<T*>::pointer pointer;
    typedef typename iterator_traits<T*>::reference reference;
    typedef typename iterator_traits<T*>::iterator_category iterator_category;

    /* MEMBER FUNCTIONS */
    vector_iterator()
        : _current(NULL) { }

    vector_iterator(const vector_iterator<value_type>& other)
        : _current(&(*other)) { }

    vector_iterator(pointer ptr)
        : _current(ptr) { }

    vector_iterator(const reference ref) { _current = &ref; }

    ~vector_iterator() { }

    vector_iterator& operator=(const vector_iterator<T>& other) {
        if (this != &other)
            _current = &(*other);
        return (*this);
    }

    /* OPERATORS */
    bool operator==(const vector_iterator<T>& other) { return (_current == &(*other)); }
    bool operator==(const vector_iterator<const T>& other) const { return (_current == &(*other)); }
    bool operator!=(const vector_iterator<T>& other) { return (_current != &(*other)); }
    bool operator!=(const vector_iterator<const T>& other) const { return (_current != &(*other)); }
    bool operator>=(const vector_iterator<T>& other) { return (_current >= &(*other)); }
    bool operator>=(const vector_iterator<const T>& other) const { return (_current >= &(*other)); }
    bool operator<=(const vector_iterator<T>& other) { return (_current <= &(*other)); }
    bool operator<=(const vector_iterator<const T>& other) const { return (_current <= &(*other)); }
    bool operator>(const vector_iterator<T>& other) { return (_current > &(*other)); }
    bool operator>(const vector_iterator<const T>& other) const { return (_current > &(*other)); }
    bool operator<(const vector_iterator<T>& other) { return (_current < &(*other)); }
    bool operator<(const vector_iterator<const T>& other) const { return (_current < &(*other)); }

    reference operator*() const { return (*_current); }

    pointer operator->() const { return (_current); }

    reference operator[](const std::size_t n) { return (*(_current + n)); }

    /* ARITHMETIC OPERATORS */
    vector_iterator operator+(difference_type n) const { return (vector_iterator(_current + n)); }

    difference_type operator+(const vector_iterator& other) const {
        return (reinterpret_cast<long>(_current)
            + reinterpret_cast<long>(&(*other)));
    }

    vector_iterator& operator+=(const int n) {
        _current += n;
        return (*this);
    }

    friend vector_iterator operator+(difference_type n, vector_iterator& other) { return (vector_iterator(n + other._current)); }

    vector_iterator operator-(const int n) const { return (vector_iterator(_current - n)); }

    difference_type operator-(const vector_iterator& other) const { return (_current - &(*other)); }

    vector_iterator& operator-=(const int n) {
        _current -= n;
        return (*this);
    }

    friend vector_iterator operator-(difference_type n, vector_iterator& other) { return (vector_iterator(n - other._current)); }

    /* INCREMENT/DECREMENT */
    vector_iterator& operator++() {
        ++_current;
        return (*this);
    }

    vector_iterator operator++(int) {
        vector_iterator tmp(*this);
        _current++;
        return (tmp);
    }

    vector_iterator operator--(int) {
        vector_iterator tmp(*this);
        _current--;
        return (tmp);
    }

    vector_iterator& operator--() {
        --_current;
        return (*this);
    }
}; // class vector_iterator

template <class Iter>
class reverse_iterator {
protected:
    /* MEMBER OBJECT */
    Iter current;

public:
    /* MEMBER TYPES */
    typedef Iter iterator_type;

    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef typename iterator_traits<Iter>::pointer pointer;
    typedef typename iterator_traits<Iter>::reference reference;
    typedef typename iterator_traits<Iter>::value_type value_type;
    typedef typename iterator_traits<Iter>::iterator_category iterator_category;

    /* MEMBER FUNCTIONS */
    // Constructors
    // Default
    reverse_iterator() {};

    // Copy
    explicit reverse_iterator(iterator_type x)
        : current(x) {};

    template <class U>
    reverse_iterator(const reverse_iterator<U>& other)
        : current(other.base()) {};

    // Assignment
    template <class U>
    reverse_iterator& operator=(const reverse_iterator<U>& other) {
        current = other.base();
        return *this;
    };

    // Access
    iterator_type base() const { return current; };

    // Dereference
    reference operator*() const {
        Iter tmp(current);
        return *--tmp;
    }

    // Return pointer to the element
    pointer operator->() const { return &(operator*()); }

    // subscript operator
    reference operator[](difference_type n) const { return current[-n - 1]; }

    // pre-increment
    reverse_iterator& operator++() {
        --current;
        return *this;
    }

    // post-increment
    reverse_iterator operator++(int) {
        reverse_iterator tmp(*this);
        --current;
        return tmp;
    }

    // pre-decrement
    reverse_iterator& operator--() {
        ++current;
        return *this;
    }

    // post-decrement
    reverse_iterator operator--(int) {
        reverse_iterator tmp(*this);
        ++current;
        return tmp;
    }

    // Add n to iterator
    reverse_iterator& operator+=(difference_type n) {
        current -= n;
        return *this;
    }

    // Subtract n from iterator
    reverse_iterator& operator-=(difference_type n) {
        current += n;
        return *this;
    }

    reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); } // add n to iterator
    reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); } // subtract n from iterator
    difference_type operator+(const reverse_iterator& other) const { return (-(current + other.base())); } // difference between two iterators
    difference_type operator-(const reverse_iterator& other) const { return (other.base() - current); } // difference between two iterators

}; // class reverse_iterator

/* NON-MEMBER FUNCTIONS */
// Relational operators
template <class Iterator1, class Iterator2>
bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() == rhs.base(); }
template <class Iterator1, class Iterator2>
bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return !(lhs.base() == rhs.base()); }
template <class Iterator1, class Iterator2>
bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() > rhs.base(); }
template <class Iterator1, class Iterator2>
bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() < rhs.base(); }
template <class Iterator1, class Iterator2>
bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() >= rhs.base(); }
template <class Iterator1, class Iterator2>
bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return lhs.base() <= rhs.base(); }

// Arithmetic operators
// Returns the iterator it incremented by n
template <class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it) { return it.base() - n; }

// Returns the distance between two iterator adaptors
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return rhs.base() - lhs.base(); }

} // namespace ft

#endif // REVERSE_ITERATOR_HPP