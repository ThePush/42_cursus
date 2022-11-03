#ifndef ARRAY_TPP
#define ARRAY_TPP

#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>

template <typename Type>
class Array {
public:
    Array();
    Array(unsigned int n);
    ~Array();
    Array(const Array& src);

    Array<Type>& operator=(const Array<Type>& rhs);
    Type& operator[](const size_t& index);

    size_t getSize(void);

private:
    Type* m_array;
    size_t m_size;
};

template <typename Type>
Array<Type>::Array()
    : m_array(NULL)
    , m_size(0) { }

template <typename Type>
Array<Type>::Array(unsigned int n)
    : m_array(new Type[n])
    , m_size(n) { }

template <typename Type>
Array<Type>::~Array() { delete[] this->m_array; }

template <typename Type>
Array<Type>::Array(const Array<Type>& src)
    : m_array(new Type[src.m_size])
    , m_size(src.m_size) {
    for (size_t i(0); i != this->m_size; ++i)
        this->m_array[i] = src.m_array[i];
}

template <typename Type>
Array<Type>& Array<Type>::operator=(const Array<Type>& rhs) {
    if (this != &rhs) {
        if (this->m_size)
            delete[] this->m_array;
        this->m_size = rhs.m_size;
        this->m_array = new Type[this->m_size];
        for (size_t i(0); i != this->m_size; ++i)
            this->m_array[i] = rhs.m_array[i];
    }

    return *this;
}

template <typename Type>
Type& Array<Type>::operator[](const size_t& index) {
    if (index >= this->m_size)
        throw std::out_of_range("[ Error: Out of bounds ]");

    return this->m_array[index];
}

template <typename Type>
size_t Array<Type>::getSize(void) { return this->m_size; }

#endif