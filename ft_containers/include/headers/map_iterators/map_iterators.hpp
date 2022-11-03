#ifndef MAP_ITERATORS_HPP
#define MAP_ITERATORS_HPP

#pragma once

#include "../iterator/iterator_traits.hpp"

namespace ft {

template <class T>
struct mapNode {
    /* MEMBER OBJECTS */
    typedef T value_type;
    typedef mapNode Node;

    /* MEMBER OBJECTS */
    value_type _pair;
    Node* parent;
    Node* left;
    Node* right;
    size_t _height;

    mapNode()
        : _pair(), parent(NULL), left(NULL), right(NULL), _height(0) { }
}; // struct Node

template <class T>
class map_iterator {
public:
    /* MEMBER TYPES */
    typedef typename iterator_traits<T*>::difference_type difference_type;
    typedef typename iterator_traits<T*>::pointer pointer;
    typedef typename iterator_traits<T*>::reference reference;
    typedef typename iterator_traits<T*>::value_type value_type;
    typedef typename iterator_traits<T*>::iterator_category iterator_category;
    typedef mapNode<value_type> Node;

    /* MEMBER VARIABLES/OBJECTS */
private:
    Node* _node;

public:
    /* MEMBER FUNCTIONS */
    map_iterator(Node* node = NULL)
        : _node(node) { }

    map_iterator(const map_iterator& other)
        : _node(other.getNode()) { }

    map_iterator& operator=(const map_iterator& other) {
        if (this != &other)
            _node = other.getNode();
        return *this;
    }

    ~map_iterator() { }

    /* MEMBER OPERATORS */
    reference operator*() const { return _node->_pair; }
    pointer operator->() const { return &(_node->_pair); }

    map_iterator& operator++() {
        if (_node->right != NULL) {
            _node = _node->right;
            while (_node->left != NULL && _node->parent != NULL)
                _node = _node->left;
        } else {
            while (_node->parent != NULL && _node == _node->parent->right)
                _node = _node->parent;
            _node = _node->parent;
        }
        return *this;
    }

    map_iterator operator++(int) {
        map_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    map_iterator& operator--() {
        if (_node->left != NULL) {
            _node = _node->left;
            while (_node->right != NULL && _node->right->parent != NULL)
                _node = _node->right;
        } else {
            while (_node->parent != NULL && _node == _node->parent->left)
                _node = _node->parent;
            _node = _node->parent;
        }
        return *this;
    }

    map_iterator operator--(int) {
        map_iterator tmp(*this);
        --(*this);
        return tmp;
    }

    Node* getNode() const { return _node; }

    bool operator==(const map_iterator& other) const { return _node == other.getNode(); }
    bool operator!=(const map_iterator& other) const { return _node != other.getNode(); }

}; // class map_iterator

//////////////////////////////////////////////////////////
//                MAP REVERSE ITERATOR                  //
//////////////////////////////////////////////////////////

template <class T>
class map_reverse_iterator {
public:
    /* MEMBER TYPES */
    typedef T iterator_type;
    typedef typename iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename iterator_traits<iterator_type>::pointer pointer;
    typedef typename iterator_traits<iterator_type>::reference reference;
    typedef typename iterator_traits<iterator_type>::value_type value_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

private:
    /* MEMBER VARIABLES */
    iterator_type _current;

public:
    /* MEMBER FUNCTIONS */
    map_reverse_iterator() { _current = iterator_type(); }
    explicit map_reverse_iterator(iterator_type other) { _current = other; }

    template <class Iter>
    map_reverse_iterator<T>(const map_reverse_iterator<Iter>& other)
        : _current(other.base()) { }

    map_reverse_iterator<T>& operator=(const map_reverse_iterator<T>& other) {
        if (this != &other) {
            _current = other.base();
        }
        return *this;
    }

    ~map_reverse_iterator() { }

    /* MEMBER OPERATORS */
    reference operator*() const {
        iterator_type tmp(_current);
        return *--tmp;
    }

    pointer operator->() const { return &(operator*()); }

    map_reverse_iterator& operator++() {
        --_current;
        return *this;
    }

    map_reverse_iterator operator++(int) {
        map_reverse_iterator tmp(*this);
        --_current;
        return tmp;
    }

    map_reverse_iterator& operator--() {
        ++_current;
        return *this;
    }

    map_reverse_iterator operator--(int) {
        map_reverse_iterator tmp(*this);
        ++_current;
        return tmp;
    }

    iterator_type base() const { return _current; }
    bool operator==(const map_reverse_iterator& other) const { return _current == other.base(); }
    bool operator!=(const map_reverse_iterator& other) const { return _current != other.base(); }

}; // class map_reverse_iterator

} // namespace ft

#endif // MAP_ITERATORS_HPP