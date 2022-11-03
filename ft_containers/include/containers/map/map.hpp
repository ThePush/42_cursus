#ifndef MAP_HPP
#define MAP_HPP

#pragma once

#include "../../headers/algorithm/algorithm.hpp"
#include "../../headers/functional/functional.hpp"
#include "../../headers/map_iterators/map_iterators.hpp"
#include "../pair/pair.hpp"

#include <iostream>
#include <memory>
namespace ft {
template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:
    /* MEMBER TYPES */
    typedef Key key_type;
    typedef T mapped_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;

    typedef ft::pair<const Key, T> value_type;
    typedef ft::mapNode<value_type> Node;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    typedef typename Allocator::template rebind<Node>::other node_allocator_type;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;

    typedef map_iterator<value_type> iterator;
    typedef map_iterator<value_type> const_iterator;
    typedef map_reverse_iterator<iterator> reverse_iterator;
    typedef map_reverse_iterator<const_iterator> const_reverse_iterator;

    /* MEMBER VARIABLES/OBJECTS */
protected:
    Node* _root;
    Node* _leaf;

    allocator_type _pairAlloc;
    node_allocator_type _nodeAlloc;

    size_type _size;
    Compare _comp;

    /* MEMBER CLASS */
public:
    class value_compare : public ft::binary_function<value_type, value_type, bool> {
        friend class ft::map<Key, T, Compare, Allocator>;

    protected:
        Compare comp;

        value_compare(Compare c)
            : comp(c) { }

    public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

        bool operator()(const value_type& lhs, const value_type& rhs) const { return comp(lhs.first, rhs.first); }
    }; // class value_compare

    /* MEMBER FUNCTIONS */
    // Constructors
    // (1) default (empty container)
    explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : _pairAlloc(alloc), _nodeAlloc(), _size(0), _comp(comp) {
        _root = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_root, Node());
        _leaf = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_leaf, Node());
        _root->right = _leaf;
        _leaf->parent = _root;
    }

    // (2) range
    template <class InputIt>
    map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : _pairAlloc(alloc), _nodeAlloc(), _size(0), _comp(comp) {
        _root = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_root, Node());
        _leaf = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_leaf, Node());
        _root->right = _leaf;
        _leaf->parent = _root;
        insert(first, last);
    }

    // (3) copy
    map(const map& other)
        : _pairAlloc(other._pairAlloc), _nodeAlloc(other._nodeAlloc), _size(0), _comp(other._comp) {
        _root = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_root, Node());
        _leaf = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_leaf, Node());
        _root->right = _leaf;
        _leaf->parent = _root;
        insert(other.begin(), other.end());
    }

    // Destructor
    ~map() {
        clear();
        _nodeAlloc.destroy(_leaf);
        _nodeAlloc.deallocate(_leaf, 1);
        _nodeAlloc.destroy(_root);
        _nodeAlloc.deallocate(_root, 1);
    }

    // Assignment operator
    map& operator=(const map& other) {
        if (this != &other) {
            clear();
            map tmp(other);
            swap(tmp);
        }
        return *this;
    }

    allocator_type get_allocator() const { return _pairAlloc; }
    // accessers needed to print the tree
    // Node* getRoot() { return _root; }
    // Node* getLeaf() { return _leaf; }

    /* ELEMENT ACCESS */
    T& operator[](const Key& key) { return insert(ft::make_pair(key, T())).first->second; }

    /* ITERATORS */
    iterator begin(void) { return _size == 0 ? iterator(end()) : iterator(findMin(_root)); }

    const_iterator begin(void) const {
        if (_size == 0)
            return const_iterator(end());
        Node* min = _root;
        while (min->left != NULL)
            min = min->left;
        return const_iterator(min);
    }

    reverse_iterator rbegin(void) { return reverse_iterator(end()); }
    const_reverse_iterator rbegin(void) const { return const_reverse_iterator(end()); }

    iterator end(void) { return iterator(_leaf); }
    const_iterator end(void) const { return const_iterator(_leaf); }

    reverse_iterator rend(void) { return reverse_iterator(begin()); }
    const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }

    /* CAPACITY */
    bool empty() const { return begin() == end(); }
    size_type size() const { return _size; }
    size_type max_size() const { return _nodeAlloc.max_size(); }

    /* MODIFIERS */
private:
    // Helper functions for insert and erase

    /*  AVL Tree Datastructure
    **  The difference between the depth of right and left sub-trees cannot be more than one.
    **  This difference is called the balance factor.
    **  The balance factor of a node is the difference between the height of the right sub-tree and the height of the left sub-tree.
    **  The balance factor of a node can be -1, 0, or 1.
    **   # If there is an imbalance in the left child's right sub-tree, perform a left-right rotation (LR)
    **   # If there is an imbalance in the left child's left sub-tree, perform a right rotation (RR)
    **   # If there is an imbalance in the right child's right sub-tree, perform a left rotation (LL)
    **   # If there is an imbalance in the right child's left sub-tree, perform a right-left rotation (RL)
    **  http://www.btechsmartclass.com/data_structures/avl-trees.html
    */
    Node* rebalanceTree(Node* node) {
        int balance_factor = getBalanceFactor(node);
        if (balance_factor > 1)
            return getBalanceFactor(node->left) > 0 ? rightRotation(node) : leftRightRotation(node);
        else if (balance_factor < -1)
            return getBalanceFactor(node->right) > 0 ? rightLeftRotation(node) : leftRotation(node);
        return node;
    }

    Node* leftRotation(Node* node) {
        Node* upward = node->right;
        Node* downward = upward->left;

        upward->left = node;
        node->right = downward;
        if (downward)
            downward->parent = node;
        upward->parent = node->parent;
        node->parent = upward;
        node->_height = getNodeHeight(node);
        upward->_height = getNodeHeight(upward);

        return upward;
    }

    Node* rightRotation(Node* node) {
        Node* upward = node->left;
        Node* downward = upward->right;

        upward->right = node;
        node->left = downward;
        if (downward)
            downward->parent = node;
        upward->parent = node->parent;
        node->parent = upward;
        node->_height = getNodeHeight(node);
        upward->_height = getNodeHeight(upward);

        return upward;
    }

    Node* leftRightRotation(Node* node) {
        Node* stick = node->left;
        Node* upward = stick->right;

        stick->right = upward->left;
        if (upward->left)
            upward->left->parent = stick;

        node->left = upward->right;
        if (upward->right)
            upward->right->parent = node;

        upward->right = node;
        upward->parent = node->parent;
        node->parent = upward;
        upward->left = stick;
        stick->parent = upward;

        stick->_height = getNodeHeight(stick);
        node->_height = getNodeHeight(node);
        upward->_height = getNodeHeight(upward);
        return upward;
    }

    Node* rightLeftRotation(Node* node) {
        Node* stick = node->right;
        Node* upward = stick->left;

        stick->left = upward->right;
        if (upward->right)
            upward->right->parent = stick;

        node->right = upward->left;
        if (upward->left)
            upward->left->parent = node;

        upward->left = node;
        upward->parent = node->parent;
        node->parent = upward;
        upward->right = stick;
        stick->parent = upward;

        stick->_height = getNodeHeight(stick);
        node->_height = getNodeHeight(node);
        upward->_height = getNodeHeight(upward);
        return upward;
    }

    // @brief: returns the value of the highest child + 1
    size_t getNodeHeight(Node* node) {
        size_t left_height = node->left != NULL ? node->left->_height : 0;
        size_t right_height = node->right != NULL ? node->right->_height : 0;

        return (left_height >= right_height ? left_height : right_height) + 1;
    }

    // @brief: subtracts the height of the right child from the height of the left child
    int getBalanceFactor(Node* node) { return (node->left != NULL ? node->left->_height : 0) - (node->right != NULL ? node->right->_height : 0); }

    // https://www.delftstack.com/howto/cpp/binary-tree-insert-in-cpp/
    Node* insertNode(const value_type& value, Node* node, Node*& nodeToInsert, Node* parent) {
        // found the end of the tree or tree is empty: insertion
        if (node == NULL || _size == 0) {
            if (_size == 0) {
                _pairAlloc.construct(&_root->_pair, value);
                ++_size;
                return _root;
            }
            nodeToInsert = _nodeAlloc.allocate(1);
            _nodeAlloc.construct(nodeToInsert, Node());
            _pairAlloc.construct(&nodeToInsert->_pair, value);
            nodeToInsert->right = NULL;
            nodeToInsert->left = NULL;
            nodeToInsert->parent = parent;
            ++_size;
            return nodeToInsert;
        }

        // going to the end of the correct branch to insert the new node
        if (_comp(value.first, node->_pair.first))
            node->left = insertNode(value, node->left, nodeToInsert, node);
        else
            node->right = insertNode(value, node->right, nodeToInsert, node);

        node->_height = getNodeHeight(node);
        return rebalanceTree(node);
    }

public:
    // @brief: return an iterator to the inserted element and a bool indicating if the insertion was successful
    ft::pair<iterator, bool> insert(const value_type& value) {
        iterator check_duplicate = find(value.first);
        if (check_duplicate != end())
            return ft::make_pair(iterator(check_duplicate), false);
        Node* nodeToInsert = NULL;

        // _leaf needs to be disconnected to avoid infinite loop in deleteNode
        _root->right = _leaf->left;
        if (_leaf->left)
            _leaf->left->parent = _root;

        // core
        _root = insertNode(value, _root, nodeToInsert, NULL);

        // reconnect _leaf
        _leaf->left = _root->right;
        if (_root->right)
            _root->right->parent = _leaf;
        _root->right = _leaf;
        _leaf->parent = _root;

        return ft::make_pair(iterator(nodeToInsert), true);
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        while (first != last) {
            insert(*first);
            first++;
        }
    }

    iterator insert(iterator hint, const value_type& value) {
        while (hint != end() && _comp(hint->first, value.first))
            hint++;
        while (hint != end() && !_comp(hint->first, value.first))
            hint--;
        if (hint == end() || hint->first != value.first) {
            insert(value);
            return (iterator(findNode(_root, value.first)));
        } 
            return (hint);
    }

private:
    // helper function for clear
    void clearNodes(Node* tmp) {
        if (tmp->left)
            clearNodes(tmp->left);
        if (tmp->right)
            clearNodes(tmp->right);
        if (tmp) {
            _nodeAlloc.destroy(tmp);
            _nodeAlloc.deallocate(tmp, 1);
        }
    }

public:
    void clear(void) {
        clearNodes(_root);
        _leaf = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_leaf, Node());
        _root = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_root, Node());
        _root->right = _leaf;
        _leaf->parent = _root;
        _size = 0;
    }

private:
    // helper functions for erase
    Node* findMin(Node* node) {
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    Node* findMax(Node* node) {
        while (node->right != NULL)
            node = node->right;
        return node;
    }

    // https://helloacm.com/how-to-delete-a-node-from-a-binary-search-tree/
    Node* deleteNode(Node* node, const Key& key) {
        if (node == NULL)
            return node;
        if (_comp(key, node->_pair.first)) { // key is in the left subtree
            node->left = deleteNode(node->left, key);
        } else if (_comp(node->_pair.first, key)) { // key is in the right subtree
            node->right = deleteNode(node->right, key);
        } else {
            // case 2 :only one right child
            if (node->left == NULL) {
                Node* tmp = node->right;
                if (node->right)
                    tmp->parent = node->parent;
                _nodeAlloc.destroy(node);
                _nodeAlloc.deallocate(node, 1);
                return tmp;
                // case 3: only one left child
            } else if (node->right == NULL) {
                Node* tmp = node->left;
                tmp->parent = node->parent;
                _nodeAlloc.destroy(node);
                _nodeAlloc.deallocate(node, 1);
                return tmp;
                // case 4: two children: we switch the value of the minimum value in the right subtree with the current node
                // case 4: two children: we switch the value of the maximum value in the left subtree with the current node
            } else {
                // Node* min = findMin(node->right); // find the minimum node in the right subtree
                //_pairAlloc.destroy(&node->_pair);
                //_pairAlloc.construct(&node->_pair, min->_pair); // copy the value of the minimum node to the current node
                // node->right = deleteNode(node->right, min->_pair.first); // delete the minimum node in the right subtree
                Node* max = findMax(node->left); // find the maximum node in the left subtree
                _pairAlloc.destroy(&node->_pair);
                _pairAlloc.construct(&node->_pair, max->_pair); // copy the value of the maximum node to the current node
                node->left = deleteNode(node->left, max->_pair.first); // delete the maximum node in the left subtree
            }
        }
        node->_height = getNodeHeight(node);
        return rebalanceTree(node);
    }

public:
    // @brief: removes specified element(s) from the container.
    void erase(iterator position) {
        // case 0: empty tree
        if (position.getNode() == NULL || _size == 0)
            return;
        // case 1: tree has only one node
        if (_size == 1) {
            clear();
            return;
        }

        // _leaf needs to be disconnected to avoid infinite loop in deleteNode
        _root->right = _leaf->left;
        if (_leaf->left != NULL)
            _leaf->left->parent = _root;

        // core
        _root = deleteNode(_root, position.getNode()->_pair.first);
        --_size;

        // reconnect _leaf
        _leaf->left = _root->right;
        if (_root->right != NULL)
            _root->right->parent = _leaf;
        _root->right = _leaf;
        _leaf->parent = _root;
    }

    void erase(iterator first, iterator last) {
        while (first != last) {
            iterator previous(first);
            ++first;
            erase(previous);
        }
    }

    // @brief: returns 1 if the key has been found and removed, 0 otherwise.
    size_type erase(const key_type& key) { return find(key) != end() ? (erase(find(key)), 1) : 0; }

    void swap(map& other) {
        ft::swap(_root, other._root);
        ft::swap(_leaf, other._leaf);
        ft::swap(_size, other._size);
        ft::swap(_comp, other._comp);
        ft::swap(_nodeAlloc, other._nodeAlloc);
        ft::swap(_pairAlloc, other._pairAlloc);
    }

private:
    // helper function for find
    Node* findNode(Node* node, const Key& key) const {
        if (node == NULL)
            return (_leaf);
        if (node->_pair.first == key)
            return (node);
        if (node == _leaf)
            return (findNode(node->left, key));
        if (!_comp(node->_pair.first, key) && !_comp(key, node->_pair.first))
            return node;
        if (_comp(node->_pair.first, key))
            return (findNode(node->right, key));
        return (findNode(node->left, key));
    }

public:
    /* LOOKUP */
    // @brief: returns an iterator to the element if the element is found, otherwise returns end()
    iterator find(const Key& key) { return _size == 0 ? end() : iterator(findNode(_root, key)); }
    const_iterator find(const Key& key) const { return _size == 0 ? end() : const_iterator(findNode(_root, key)); }

    // @brief: returns 1 if the container contains an element whose key is equivalent to the argument, or zero otherwise.
    size_type count(const Key& key) const { return find(key) != end(); }

    // @brief: returns an iterator to the first element that is not less than key (while it < key)
    iterator lower_bound(const Key& key) {
        iterator it = begin();
        while (it != end() && _comp(it->first, key))
            it++;
        return it;
    }

    const_iterator lower_bound(const Key& key) const {
        const_iterator it = begin();
        while (it != end() && _comp(it->first, key))
            it++;
        return it;
    }

    // @brief: returns an iterator to the first element that is greater than key (while it <= key)
    iterator upper_bound(const Key& key) {
        iterator it = begin();
        while (it != end() && !_comp(key, it->first))
            it++;
        return it;
    }

    const_iterator upper_bound(const Key& key) const {
        const_iterator it = begin();
        while (it != end() && !_comp(key, it->first))
            it++;
        return it;
    }

    // @brief: returns a pair of iterators containing lower_bound and upper_bound
    ft::pair<iterator, iterator> equal_range(const Key& key) { return ft::make_pair(lower_bound(key), upper_bound(key)); }
    ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const { return ft::make_pair(lower_bound(key), upper_bound(key)); }

    /* OBSERVERS */
    // @brief: returns the comparison object used by the container to compare keys
    key_compare key_comp() const { return _comp; }

    // @brief: returns the comparison object used by the container to compare values
    value_compare value_comp() const { return value_compare(_comp); }
};

/*NON-MEMBER FUNCTIONS*/
// relational operators
template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    typename ft::map<Key, T, Compare, Alloc>::const_iterator it = lhs.begin();
    typename ft::map<Key, T, Compare, Alloc>::const_iterator it2 = rhs.begin();
    while (it != lhs.end()) {
        if (it->first != it2->first || it->second != it2->second)
            return false;
        it++;
        it2++;
    }
    return true;
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return !(lhs == rhs); }

template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return (!(lhs < rhs) && !(lhs == rhs)); }

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return (!(lhs > rhs)); }

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return (!(lhs < rhs)); }

// swap
// @brief: specializes the ft::swap algorithm
template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs) { lhs.swap(rhs); }

} // namespace ft
#endif