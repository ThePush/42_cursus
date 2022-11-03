#ifndef MUTANTSTACK_TPP
#define MUTANTSTACK_TPP

#pragma once

#include <iterator>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
public:
    MutantStack();
    MutantStack(const MutantStack& src);
    ~MutantStack();
    MutantStack& operator=(const MutantStack& rhs);

    typedef typename std::stack<T>::container_type::iterator iterator;

    iterator begin(void);
    iterator end(void);

private:
};

template <typename T>
MutantStack<T>::MutantStack() { }

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T>& src)
    : std::stack<T>(src) { }

template <typename T>
MutantStack<T>::~MutantStack() { }

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack<T>& rhs) {
    if (this != &rhs)
        this->c = rhs.c;

    return *this;
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin(void) { return (this->c.begin()); }

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end(void) { return (this->c.end()); }

#endif