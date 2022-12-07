#ifndef VECTOR_HPP
#define VECTOR_HPP

#pragma once

#include "../../headers/algorithm/algorithm.hpp"
#include "../../headers/string/string.hpp"
#include "../../headers/type_traits/type_traits.hpp"
#include "../../headers/vector_iterators/vector_iterators.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector {
    /* MEMBER TYPES */
public:
    typedef T value_type;
    typedef Allocator allocator_type;

    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;

    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    typedef T* iterator;
    typedef const T* const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    /* MEMBER VARIABLES/OBJECTS */
private:
    Allocator _alloc;
    size_type _size;
    size_type _capacity;
    pointer _data;

    /* MEMBER FUNCTIONS */
public:
    // Default constructor
    explicit vector(const allocator_type& alloc = allocator_type())
        : _alloc(alloc), _size(0), _capacity(0), _data(NULL) { }

    // Constructor (fill)
    explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
        : _alloc(alloc), _size(n), _capacity(n), _data(_alloc.allocate(n)) {
        for (size_type i(0); i != n; ++i)
            _alloc.construct(_data + i, value);
    }

    // Constructor (range)
    // @brief: enable_if is here for SFINAE with fill constructor
    template <class InputIterator>
    vector(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type())
        : _alloc(alloc), _size(0), _capacity(0), _data(NULL) {
        while (first != last) {
            push_back(*first);
            ++first;
        }
    }

    // Copy constructor
    vector(const vector& x)
        : _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _data(_alloc.allocate(x._capacity)) {
        for (size_type i(0); i != _size; ++i)
            _alloc.construct(_data + i, x._data[i]);
    }

    // Copy assignment
    vector& operator=(const vector& x) {
        if (this != &x) {
            _alloc.deallocate(_data, _capacity);
            _alloc = x._alloc;
            _size = x._size;
            _capacity = x._capacity;
            _data = _alloc.allocate(_capacity);
            for (size_type i(0); i != _size; ++i)
                _alloc.construct(_data + i, x._data[i]);
        }
        return *this;
    }

    // Destructor
    ~vector() { _alloc.deallocate(_data, _capacity); }

    // @brief: Replaces the contents with count copies of value value
    void assign(size_type count, const T& value) {
        clear();
        if (count > _capacity) {
            _alloc.deallocate(_data, _capacity);
            _capacity = count;
            _data = _alloc.allocate(_capacity);
        }
        _size = count;
        for (size_type i(0); i != _size; ++i)
            _alloc.construct(_data + i, value);
    }

    // @brief: the contents with copies of those in the range [first, last); This overload has the same effect as the previous Assign if InputIt is an integral type.
    template <class InputIt>
    void assign(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last) {
        clear();
        insert(begin(), first, last);
    }

    allocator_type get_allocator() const { return _alloc; }

    /* ELEMENT ACCESS */
    // @brief: Returns a reference to the element at position n in the vector container. bounds-checking is performed.
    reference at(size_type pos) {
        if (!(pos < _size))
            throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(pos) + ") " + ">= this->size() (which is " + ft::to_string(_size) + ")");
        return _data[pos];
    }

    const reference at(size_type pos) const {
        if (!(pos < _size))
            throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(pos) + ") " + ">= this->size() (which is " + ft::to_string(_size) + ")");
        return _data[pos];
    }

    // @brief: No bounds checking is performed.
    reference operator[](size_type pos) { return _data[pos]; }
    const_reference operator[](size_type pos) const { return _data[pos]; }

    // @brief: Calling front on an empty container is undefined.
    reference front() { return _data[0]; }
    const_reference front() const { return _data[0]; }

    // @brief: Calling back on an empty container causes undefined behavior.
    reference back() { return _data[_size - 1]; }
    const_reference back() const { return _data[_size - 1]; }

    // @brief: Returns a pointer to the first element in the container. or NULL if the container is empty.
    pointer data() { return _size == 0 ? NULL : _data; }
    const_pointer data() const { return _size == 0 ? NULL : _data; }

    /* ITERATORS */
    iterator begin() { return iterator(_data); }
    const_iterator begin() const { return const_iterator(_data); }
    iterator end() { return iterator(_data + _size); }
    const_iterator end() const { return const_iterator(_data + _size); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    /* CAPACITY */
    bool empty() const { return _size == 0; }
    size_type size() const { return _size; }
    size_type max_size() const { return _alloc.max_size(); }
    size_type capacity() const { return _capacity; }

    // @brief: If an exception is thrown, this function has no effect (strong exception guarantee).
    void reserve(size_type new_capacity) {
        if (new_capacity > _alloc.max_size()) throw std::length_error("vector::reserve");
        if (new_capacity > _capacity) {
            try {
                pointer new_data = _alloc.allocate(new_capacity);
                for (size_type i(0); i != _size; ++i) {
                    _alloc.construct(new_data + i, _data[i]);
                    _alloc.destroy(_data + i);
                }
                _alloc.deallocate(_data, _capacity);
                _data = new_data;
                _capacity = new_capacity;
            } catch (std::exception& e) { throw std::bad_alloc(); }
        }
    }

    /* MODIFIERS */
    // @brief: The capacity is not affected.
    void clear() {
        if (_size != 0) {
            for (size_type i(0); i != _size; ++i)
                _alloc.destroy(&_data[i]);
            _size = 0;
            _data = NULL;
        }
    }

    // @brief: If an exception is thrown when inserting a single element at the end, there are no effects (strong exception guarantee).
    iterator insert(iterator pos, const T& value) {
        if (pos == end()) {
            try {
                push_back(value);
                return end() - 1;
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                return end() - 1;
            }
        }
        size_type position = pos - _data;
        if (_size + 1 > _capacity) try {
                reserve(_size << 1);
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                return end() - 1;
            }
        pointer pointer_to_end = _data + _size;
        pointer pointer_to_position = _data + position;
        while (pointer_to_end != pointer_to_position) {
            _alloc.construct(pointer_to_end, *(pointer_to_end - 1));
            _alloc.destroy(pointer_to_end - 1);
            --pointer_to_end;
        }
        _alloc.construct(_data + position, value);
        ++_size;
        return iterator(_data + position);
    }

    void insert(iterator pos, size_type count, const T& value) {
        if (count == 0) return;
        size_type position = pos - _data;
        if (_size + count > _capacity) try {
                reserve(_size + count);
            } catch (std::exception& e) { std::cout << e.what() << std::endl; };
        pointer pointer_to_end = _data + _size;
        pointer pointer_to_position = _data + position;
        while (pointer_to_end != pointer_to_position) {
            _alloc.construct(pointer_to_end + count - 1, *(pointer_to_end - 1));
            _alloc.destroy(pointer_to_end - 1);
            --pointer_to_end;
        }
        _size += count;
        while (count--)
            _alloc.construct(_data + position + count, value);
    }

    // @brief: This overload has the same effect as the previous insert() if InputIt is an integral type.
    template <class InputIt>
    void insert(iterator pos, InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last) {
        if (first == last) return;
        size_type position = pos - _data;
        size_type count = last - first;
        if (_size + count > _capacity) try {
                reserve(_size + count);
            } catch (std::exception& e) { std::cout << e.what() << std::endl; };
        pointer pointer_to_end = _data + _size;
        pointer pointer_to_position = _data + position;
        while (pointer_to_end != pointer_to_position) {
            _alloc.construct(pointer_to_end + count - 1, *(pointer_to_end - 1));
            _alloc.destroy(pointer_to_end - 1);
            --pointer_to_end;
        }
        for (; first != last; ++first)
            _alloc.construct(_data + position++, *first);
        _size += count;
    }

    iterator erase(iterator pos) {
        size_type position = pos - _data;
        ft::copy(_data + position + 1, _data + _size, _data + position);
        --_size;
        _alloc.destroy(_data + _size);
        return iterator(_data + position);
    }

    iterator erase(iterator first, iterator last) {
        size_type position = first - _data;
        size_type count = last - first;
        ft::copy(_data + position + count, _data + _size, _data + position);
        _size -= count;
        for (size_type i(0); i != count; ++i)
            _alloc.destroy(_data + _size + i);
        return iterator(_data + position);
    }

    // @brief: strong exception guarantee
    void push_back(const_reference value) {
        if (_size << 1 > _alloc.max_size()) throw std::length_error("vector::push_back");
        if (_size == 0) try {
                reserve(1);
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                return;
            }
        else if (_size + 1 > _capacity)
            try {
                reserve(_size << 1);
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                return;
            }
        _alloc.construct(_data + _size, value);
        ++_size;
    }

    // @brief: Calling pop_back on an empty container results in undefined behavior.
    void pop_back() {
        _alloc.destroy(_data + _size - 1);
        --_size;
    }

    // @brief: If an exception is thrown, this function has no effect (strong exception guarantee).
    void resize(size_type count, T value = T()) {
        if (count > _size) {
            try {
                if (count > _alloc.max_size()) throw std::length_error("vector::resize");
                if (count > _capacity) try {
                        reserve(count);
                    } catch (std::exception& e) {
                        std::cout << e.what() << std::endl;
                        return;
                    }
                for (size_type i(0); i != count - _size; ++i)
                    _alloc.construct(_data + _size + i, value);
                _size = count;
            } catch (std::exception& e) { return; }
        } else if (count < _size) {
            for (size_type i(0); i != _size - count; ++i)
                _alloc.destroy(_data + count + i);
            _size = count;
        }
    }

    // @brief: The past-the-end iterator is invalidated.
    void swap(vector& other) {
        if (this != &other) {
            ft::swap(_data, other._data);
            ft::swap(_size, other._size);
            ft::swap(_capacity, other._capacity);
        }
    }

}; // class vector

/* NON-MEMBER FUNCTIONS */
// Relational operators
template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) { return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) { return !(lhs == rhs); }
template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) { return rhs < lhs; }
template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) { return !(rhs < lhs); }
template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) { return !(lhs < rhs); }

// @brief: Specializes the ft::swap algorithm for ft::vector. Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
template <class T, class Alloc>
void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) { lhs.swap(rhs); }

} // namespace ft

#endif // VECTOR_HPP

/* https://www.stroustrup.com/except.pdf */