#ifndef SPAN_HPP
#define SPAN_HPP

#pragma once

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <vector>

class Span {
public:
    Span(const unsigned int& N = 0);
    Span(const Span& src);
    ~Span();
    Span& operator=(const Span& rhs);

    void addNumber(const unsigned int& number);
    void addNumber(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end);
    void printVector(void) const;
    size_t shortestSpan(void);
    size_t longestSpan(void);

private:
    std::vector<int> m_spanvec;
    size_t m_size;
};

#endif