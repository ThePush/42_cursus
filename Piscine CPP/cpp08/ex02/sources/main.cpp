#include "colors.hpp"

#include "MutantStack.tpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <list>
#include <unistd.h>
#include <vector>

int main() {

    std::cout << KMAG;

    std::cout << KMAG "================ [ TEST ] Template and iterators =============" << std::endl
              << std::endl;

    std::cout << KMAG "======================== MutantStack =========================" << std::endl
              << std::endl;

    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << "mstack.top(): " << mstack.top() << std::endl;
    mstack.pop();
    std::cout << "mstack.size(): " << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    std::cout << "Print MustantStack's values:" << std::endl;
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);

    std::cout << std::endl
              << std::endl;

    std::cout << KMAG "======================== List comparison =====================" << std::endl
              << std::endl;

    std::list<int> list;
    list.push_back(5);
    list.push_back(17);
    std::cout << "list.back(): " << list.back() << std::endl;
    list.pop_back();
    std::cout << "list.size(): " << list.size() << std::endl;
    list.push_back(3);
    list.push_back(5);
    list.push_back(737);
    list.push_back(0);
    std::list<int>::iterator lit = list.begin();
    std::list<int>::iterator lite = list.end();
    ++lit;
    --lit;
    std::cout << "Print list's values:" << std::endl;
    while (lit != lite) {
        std::cout << *lit << std::endl;
        ++lit;
    }
    std::list<int> ls(list);

    std::cout << std::endl
              << std::endl;

    std::cout << KMAG "======================= Vector comparison ====================" << std::endl
              << std::endl;

    std::vector<int> vector;
    vector.push_back(5);
    vector.push_back(17);
    std::cout << "vector.back(): " << vector.back() << std::endl;
    vector.pop_back();
    std::cout << "vector.size(): " << vector.size() << std::endl;
    vector.push_back(3);
    vector.push_back(5);
    vector.push_back(737);
    vector.push_back(0);
    std::vector<int>::iterator vit = vector.begin();
    std::vector<int>::iterator vite = vector.end();
    ++vit;
    --vit;
    std::cout << "Print vector's values:" << std::endl;
    while (vit != vite) {
        std::cout << *vit << std::endl;
        ++vit;
    }
    std::vector<int> vs(vector);

    std::cout << KNRM;

    return EXIT_SUCCESS;
}