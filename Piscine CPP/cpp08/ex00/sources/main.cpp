#include "colors.hpp"

#include "easyfind.tpp"

#include <cstdlib>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

#define CONT_BEGIN -10
#define CONT_END 10
#define NEEDLE 5

int main() {

    std::cout << KMAG;

    std::cout << KMAG "====================== [ TEST ] STL ======================" << std::endl
              << std::endl;

    std::cout << KMAG "======================= [ VECTOR ] =======================" << std::endl
              << std::endl;

    std::vector<int> intvec;
    for (int i(CONT_BEGIN); i != CONT_END; ++i)
        intvec.push_back(i);

    for (std::vector<int>::const_iterator i(intvec.begin()); i != intvec.end(); ++i)
        std::cout << " " << *i << std::endl;

    std::cout << std::endl;

    try {
        std::cout << KMAG " Looking for: " KMAG << NEEDLE << std::endl
                  << std::endl;
        easyfind(intvec, NEEDLE);
        std::cout << KGRN " Needle Found" KNRM << std::endl
                  << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED " Needle not found" KNRM << std::endl
                  << std::endl;
    }

    std::cout << KMAG "========================= [ LIST ] =======================" << std::endl
              << std::endl;

    std::list<int> intlist;
    for (int i(CONT_BEGIN); i != CONT_END; ++i)
        intlist.push_back(i);

    for (std::list<int>::const_iterator i(intlist.begin()); i != intlist.end(); ++i)
        std::cout << " " << *i << std::endl;

    std::cout << std::endl;

    try {
        std::cout << KMAG " Looking for: " KMAG << NEEDLE << std::endl
                  << std::endl;
        easyfind(intlist, NEEDLE);
        std::cout << KGRN " Needle Found" KNRM << std::endl
                  << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED " Needle not found" KNRM << std::endl
                  << std::endl;
    }

    std::cout << KMAG "========================= [ STACK ] ======================" << std::endl
              << std::endl;

    std::stack<int> intstack;
    for (int i(CONT_BEGIN); i != CONT_END; ++i)
        intstack.push(i);

    for (int i(CONT_BEGIN); i != CONT_END; ++i)
        std::cout << " " << i << std::endl;

    std::cout << std::endl;

    try {
        std::cout << KMAG " Looking for: " KMAG << NEEDLE << std::endl
                  << std::endl;
        easyfind(intlist, NEEDLE);
        std::cout << KGRN " Needle Found" KNRM << std::endl
                  << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED " Needle not found" KNRM << std::endl
                  << std::endl;
    }

    std::cout << KNRM;

    return EXIT_SUCCESS;
}
