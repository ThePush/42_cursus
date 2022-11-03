#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#pragma once

namespace ft {

// ft::lexicographical_compare
// @brief: Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2) {
    while (first1 != last1) {
        if (first2 == last2 || *first2 < *first1)
            return false;
        else if (*first1 < *first2)
            return true;
        ++first1;
        ++first2;
    }
    return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2,
    Compare comp) {
    while (first1 != last1) {
        if (first2 == last2 || comp(*first2, *first1))
            return false;
        else if (comp(*first1, *first2))
            return true;
        ++first1;
        ++first2;
    }
    return (first2 != last2);
}

// ft::equal
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    while (first1 != last1) {
        if (!(*first1 == *first2))
            return false;
        ++first1;
        ++first2;
    }
    return true;
}

// @brief: A function that takes two iterators and a predicate and returns true if the predicate is true for all elements in the range.
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, BinaryPredicate pred) {
    while (first1 != last1) {
        if (!pred(*first1, *first2))
            return false;
        ++first1;
        ++first2;
    }
    return true;
}

// ft::swap
template <class value_type>
void swap(value_type& a, value_type& b) {
    value_type tmp(b);
    b = a;
    a = tmp;
}

// ft::copy
template <class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
    for (; first != last; (void)++first, (void)++d_first)
        *d_first = *first;
    return d_first;
}

//// ft::copy_backward
//template <class BidirIt1, class BidirIt2>
//BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last) {
//    while (first != last)
//        *(--d_last) = *(--last);
//    return d_last;
//}

//// ft::fill
//template <class ForwardIt, class T>
//void fill(ForwardIt first, ForwardIt last, const T& value) {
//    for (; first != last; ++first)
//        *first = value;
//}

} // namespace ft

#endif // ALGORITHM_HPP