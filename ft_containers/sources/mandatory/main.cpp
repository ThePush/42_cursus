#ifndef STD
#include "../../include/containers/map/map.hpp"
#include "../../include/containers/pair/pair.hpp"
#include "../../include/containers/stack/stack.hpp"
#include "../../include/containers/vector/vector.hpp"
#include "../../include/headers/map_iterators/map_iterators.hpp"
#else
#include <map>
#include <stack>
#include <utility>
#include <vector>
namespace ft = std;
#endif

#include "../../include/colors/colors.hpp"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <unistd.h>

void print_test_time(const std::string test_name, const struct timeval& start) {
    struct timeval end;
    std::string tabbed = "    ";
    tabbed += test_name;
    gettimeofday(&end, NULL);
    std::cout
        << KYEL << tabbed << " tests time: " << (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec) << "us" << KNRM << std::endl;
}

template <typename T>
std::string to_string(T value) { return static_cast<std::ostringstream*>(&(std::ostringstream() << value))->str(); }

//#ifndef STD
// typedef ft::mapNode<ft::pair<const int, int> > Node;
// void printBTree(const std::string& prefix, Node* node, Node* root, Node* leaf, bool isLeft) {
//    if (node != NULL && node != leaf) {
//        if (node == root)
//            std::cout << "R" << std::endl;

//        std::cout << prefix;

//        std::cout << (isLeft ? "├──" : "└──");

//        // print the value of the node
//        std::cout << node->_pair.first << std::endl;

//        // enter the next tree level - left and right branch
//        printBTree(prefix + (isLeft ? "│   " : "    "), node->left, root, leaf, true);
//        printBTree(prefix + (isLeft ? "│   " : "    "), node->right, root, leaf, false);
//    }
//}
//#endif

void stack_tests(bool v, bool t) {

    /////////////////////////////////////////////////////////////////////////////////
    //                    START OF STACK TESTS                                     //
    /////////////////////////////////////////////////////////////////////////////////
    bool verbose = v;
    bool timer = t;
    if (verbose) {
#ifndef STD
        std::cout << std::endl
                  << KYEL << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                              FT::STACK TESTS                               //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << KNRM << std::endl
                  << std::endl;
#else
        std::cout << std::endl
                  << KYEL << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                              STD::STACK TESTS                              //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << KNRM << std::endl
                  << std::endl;
#endif
    }

    struct timeval start;
    gettimeofday(&start, NULL);
    ft::stack<int> stackA;

    if (verbose)
        std::cout << KMAG "    // <stack> member function push():" KNRM << KNRM << std::endl
                  << std::endl;
    for (int i(0); i != 10; ++i) {
        if (verbose) {
            std::cout << "    stackA.push(" << i << ");" << KNRM << std::endl;
        }
        stackA.push(i);
    }

    if (verbose)
        std::cout << std::endl
                  << KMAG "    // <stack> operator=:" KNRM << std::endl
                  << std::endl
                  << KNRM "    ft::stack<int>stackB = stackA" << std::endl;

    ft::stack<int> stackB = stackA;

    if (verbose)
        std::cout << std::endl
                  << KMAG "    // <stack> member functions top() / pop() / size():" KNRM << KNRM << std::endl
                  << std::endl;

    while (stackA.size()) {
        if (verbose) std::cout << "    stackA.size() = " << stackA.size() << std::endl;
        if (verbose) std::cout << "    stackA.top() = " << stackA.top() << std::endl;
        if (verbose) std::cout << "    stackA.pop()" << std::endl;
        stackA.pop();
    }

    if (verbose) {
        std::cout << std::endl
                  << KMAG "    // <stack> relational operators and member function empty():" KNRM << KNRM << std::endl
                  << std::endl;
        std::cout << "    stackA == stackB: " << (stackA == stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA != stackB: " << (stackA != stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA < stackB: " << (stackA < stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA > stackB: " << (stackA > stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA <= stackB: " << (stackA <= stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA >= stackB: " << (stackA >= stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA.empty(): " << (stackA.empty() ? "true" : "false") << std::endl;
        std::cout << std::endl;
    }

#ifndef STD
    if (timer) print_test_time("ft::stack", start);
#else
    if (timer) print_test_time("std::stack", start);
#endif

    /////////////////////////////////////////////////////////////////////////////////
    //                    END OF STACK TESTS                                       //
    /////////////////////////////////////////////////////////////////////////////////
}

void pair_tests(bool v, bool t) {

    /////////////////////////////////////////////////////////////////////////////////
    //                    START OF PAIR TESTS                                      //
    /////////////////////////////////////////////////////////////////////////////////

    bool verbose = v;
    bool timer = t;
    if (verbose) {
#ifndef STD
        std::cout << std::endl
                  << KYEL << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                               FT::PAIR TESTS                                //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << KNRM << std::endl
                  << std::endl;
#else
        std::cout << std::endl
                  << KYEL << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                               STD::PAIR TESTS                               //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << KNRM << std::endl
                  << std::endl;
#endif
    }

    struct timeval start;
    gettimeofday(&start, NULL);
    ft::pair<unsigned int, unsigned int> pairA(1, 2);

    if (verbose)
        std::cout << KMAG "    // <pair> constructors and make_pair():" KNRM << KNRM << std::endl
                  << std::endl;

    ft::pair<unsigned int, unsigned int> pairB = ft::make_pair(3, 4);
    ft::pair<unsigned int, unsigned int> pairC = pairB;
    ft::pair<unsigned int, unsigned int> pairD(pairC);

    if (verbose) {
        std::cout << "    pairA.first: " << pairA.first << std::endl;
        std::cout << "    pairA.second: " << pairA.second << std::endl;
        std::cout << "    pairB.first: " << pairB.first << std::endl;
        std::cout << "    pairB.second: " << pairB.second << std::endl;
        std::cout << "    pairA.first = 3: " << (pairA.first = 3) << std::endl;
        std::cout << "    pairA.second = 4: " << (pairA.second = 4) << std::endl;
        std::cout << "    pairB.first = 5: " << (pairB.first = 5) << std::endl;
        std::cout << "    pairB.second = 6: " << (pairB.second = 6) << std::endl;
        std::cout << std::endl;
    }

    if (verbose) {
        std::cout << KMAG "    // <pair> relational operators:" KNRM << KNRM << std::endl
                  << std::endl;
        std::cout << "    pairA == pairB: " << (pairA == pairD ? "true" : "false") << std::endl;
        std::cout << "    pairA != pairB: " << (pairA != pairB ? "true" : "false") << std::endl;
        std::cout << "    pairA < pairB: " << (pairA < pairC ? "true" : "false") << std::endl;
        std::cout << "    pairA <= pairB: " << (pairA <= pairB ? "true" : "false") << std::endl;
        std::cout << "    pairA > pairB: " << (pairA > pairC ? "true" : "false") << std::endl;
        std::cout << "    pairA >= pairB: " << (pairA >= pairD ? "true" : "false") << std::endl;
        std::cout << std::endl;
    }

#ifndef STD
    if (timer) print_test_time("ft::pair", start);
#else
    if (timer) print_test_time("std::pair", start);
#endif

    /////////////////////////////////////////////////////////////////////////////////
    //                    END OF PAIR TESTS                                        //
    /////////////////////////////////////////////////////////////////////////////////
}

void vector_tests(bool v, bool t) {

    /////////////////////////////////////////////////////////////////////////////////
    //                    START OF VECTOR TESTS                                    //
    /////////////////////////////////////////////////////////////////////////////////

    bool verbose = v;
    bool timer = t;
    if (verbose) {
#ifndef STD
        std::cout << std::endl
                  << KYEL << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                               FT::VECTOR TESTS                              //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << KNRM << std::endl
                  << std::endl;
#else
        std::cout << std::endl
                  << KYEL << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                               STD::VECTOR TESTS                             //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << KNRM << std::endl
                  << std::endl;
#endif
    }

    struct timeval start;
    gettimeofday(&start, NULL);

    if (verbose)
        std::cout << KMAG "    // <vector> constructors:" KNRM << KNRM << std::endl
                  << std::endl;
    ft::vector<int> vectorA(3, 42);
    ft::vector<int> vectorB(vectorA);
    ft::vector<int> vectorC(vectorB.begin(), vectorB.end());
    ft::vector<int> vectorD = vectorC;

    if (verbose) {
        for (unsigned int i(0); i != vectorA.size(); ++i) {
            std::cout << "    vectorA[" << i << "] = " << vectorA[i] << std::endl;
            std::cout << "    vectorB[" << i << "] = " << vectorB[i] << std::endl;
            std::cout << "    vectorC[" << i << "] = " << vectorC[i] << std::endl;
            std::cout << "    vectorD[" << i << "] = " << vectorD[i] << std::endl
                      << std::endl;
        }
    }

    if (verbose)
        std::cout << KMAG "    // <vector> member function push_back():" KNRM << KNRM << std::endl
                  << std::endl;

    for (int i(0); i != 10; ++i) {
        if (verbose) std::cout << "    vectorA.push_back(" << i + 8 << ")" << std::endl;
        vectorA.push_back(i + 8);
    }

    if (verbose) {
        std::cout << std::endl
                  << KMAG "    // <vector> member functions at():" KNRM << KNRM << std::endl
                  << std::endl;

        for (unsigned int i(0); i != vectorB.size(); ++i)
            std::cout << "    vectorB.at(" << i << "): " << vectorB.at(i) << std::endl;
        std::cout << std::endl;
    }

    if (verbose) {
        std::cout << std::endl
                  << KMAG "    // <vector> member functions insert():" KNRM << KNRM << std::endl
                  << std::endl;
    }

    vectorB.insert(vectorB.begin(), 777);
    vectorB.insert(vectorB.begin() + 1, 1, 1337);
    vectorB.insert(vectorB.begin() + 1, vectorA.begin(), vectorA.end());
    vectorB.insert(vectorB.begin() + 2, 22);
    vectorB.insert(vectorB.begin() + 3, 333);
    vectorB.insert(vectorB.begin() + 4, 4444);
    vectorB.insert(vectorB.begin() + 5, 55555);

    if (verbose) {
        for (unsigned int i(0); i != vectorB.size(); ++i)
            std::cout << "    vectorB.at(" << i << "): " << vectorB.at(i) << std::endl;

        std::cout << std::endl
                  << "    Trying to access an out of range value with at():" KNRM << std::endl;
    }

    try {
        vectorB.at(vectorB.size());
    } catch (std::exception& e) {
        if (verbose) std::cout << "    " << e.what() << std::endl;
    }

    if (verbose) {
        std::cout << std::endl
                  << KMAG "    // <vector> member functions size() / capacity() / max_size():" KNRM << KNRM << std::endl
                  << std::endl
                  << "    vectorA.size(): " << vectorA.size() << std::endl;
        std::cout << "    vectorA.capacity(): " << vectorA.capacity() << std::endl;
        std::cout << "    vectorA.max_size(): " << vectorA.max_size() << std::endl;
        std::cout << "    vectorB.size(): " << vectorB.size() << std::endl;
        std::cout << "    vectorB.capacity(): " << vectorB.capacity() << std::endl;
        std::cout << "    vectorB.max_size(): " << vectorB.max_size() << std::endl;

        std::cout << std::endl
                  << KMAG "    // <vector> iterators:" KNRM << std::endl
                  << std::endl;
        std::cout << "    Print vectorA from begin() to end():" KNRM << std::endl;
        for (ft::vector<int>::const_iterator it(vectorA.begin()); it != vectorA.end(); ++it)
            std::cout << "    vectorA[" << (it - vectorA.begin()) << "]: " << *it << std::endl;

        std::cout << std::endl;
        std::cout << "    Print vectorA from rbegin() to rend():" KNRM << std::endl;
        for (ft::vector<int>::const_reverse_iterator it(vectorA.rbegin()); it != vectorA.rend(); ++it)
            std::cout << "    vectorA[" << (it - vectorA.rbegin()) << "]: " << *it << std::endl;

        std::cout << std::endl;
        std::cout << "    Test const_iterator and iterator compatibility:" << KNRM << std::endl;
        ft::vector<int>::const_iterator const_iterator_begin(vectorB.begin());
        ft::vector<int>::iterator iterator_end(vectorB.end());
        for (; const_iterator_begin != iterator_end; ++const_iterator_begin)
            std::cout << "    vectorB[" << (const_iterator_begin - vectorB.begin()) << "]: " << *const_iterator_begin << std::endl;

        std::cout << std::endl;
    }

    if (verbose)
        std::cout << std::endl
                  << KMAG "    // <vector> member function swap():" KNRM << KNRM << std::endl
                  << std::endl;

    vectorB.swap(vectorA);

    if (verbose) {
        std::cout << "    vectorA.size(): " << vectorA.size() << std::endl;
        std::cout << "    vectorA.capacity(): " << vectorA.capacity() << std::endl;
        std::cout << "    vectorA.max_size(): " << vectorA.max_size() << std::endl;
        std::cout << "    vectorB.size(): " << vectorB.size() << std::endl;
        std::cout << "    vectorB.capacity(): " << vectorB.capacity() << std::endl;
        std::cout << "    vectorB.max_size(): " << vectorB.max_size() << std::endl
                  << std::endl;

        for (unsigned int i(0); i != vectorA.size(); ++i)
            std::cout << "    vectorA.[" << i << "]: " << vectorA[i] << std::endl;

        std::cout << std::endl;

        for (unsigned int i(0); i != vectorB.size(); ++i)
            std::cout << "    vectorB.[" << i << "]: " << vectorB[i] << std::endl;
    }

    if (verbose) std::cout << std::endl;

    if (verbose)
        std::cout << std::endl
                  << KMAG "    // <vector> member function erase():" KNRM << KNRM << std::endl
                  << std::endl;
    vectorB.erase(vectorB.begin() + 1, vectorB.end() - vectorB.size() / 2);

    if (verbose) {
        for (unsigned int i(0); i != vectorB.size(); ++i)
            std::cout << "    vectorB.[" << i << "]: " << vectorB[i] << std::endl;
        std::cout << std::endl;
    }

    if (verbose)
        std::cout << KMAG "    // <vector> resize():" KNRM << std::endl
                  << std::endl;

    vectorA.resize(5, 42);
    vectorA.resize(10, 33);
    vectorA.resize(0, 1000);
    vectorA.resize(1, 42);

    if (verbose) {
        for (unsigned int i(0); i != vectorA.size(); ++i)
            std::cout << "    vectorA.[" << i << "]: " << vectorA[i] << std::endl;
        std::cout << std::endl;
    }

    if (verbose)
        std::cout << KMAG "    // <vector> reserve exception with reserve(max_size + 1):" KNRM << std::endl
                  << std::endl;
    try {
        vectorA.reserve(vectorA.max_size() + 1);
    } catch (std::exception& e) {
        if (verbose) std::cout << "    " << e.what() << std::endl
                               << std::endl;
    }

#ifndef STD
    if (timer) print_test_time("ft::vector", start);
#else
    if (timer) print_test_time("std::vector", start);
#endif

    ///////////////////////////////////////////////////////////////////////////////////
    ////                    END OF VECTOR TESTS                                      //
    ///////////////////////////////////////////////////////////////////////////////////
}

void map_tests(bool v, bool t) {

    ///////////////////////////////////////////////////////////////////////////////////
    ////                     START OF MAP TESTS                                      //
    ///////////////////////////////////////////////////////////////////////////////////

    bool verbose = v;
    bool timer = t;
    if (verbose) {
#ifndef STD
        std::cout << std::endl
                  << KYEL << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                            FT::MAP TESTS                                    //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << KNRM << std::endl
                  << std::endl;
#else
        std::cout << std::endl
                  << KYEL << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                            STD::MAP TESTS                                   //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << KNRM << std::endl
                  << std::endl;
#endif
    }

    struct timeval start;
    gettimeofday(&start, NULL);

    if (verbose)
        std::cout << std::endl
                  << KMAG "    // <map> default constructor, insert(pair) and insert(hint, key):" KNRM << std::endl
                  << std::endl;

    ft::map<int, int> mapA;
    for (int i(0); i != 9; ++i) {
        if (verbose)
            std::cout << "    mapA.insert(" << i << ", " << i << ")" << std::endl;
        mapA.insert(ft::make_pair(i, i));
    }

    if (verbose)
        std::cout << "    mapA.insert(mapA.begin(), ft::make_pair(9, 9)); x3" << std::endl;
    mapA.insert(mapA.begin(), ft::make_pair(9, 9));
    mapA.insert(mapA.begin(), ft::make_pair(9, 9));
    mapA.insert(mapA.begin(), ft::make_pair(9, 9));

    if (verbose)
        std::cout << std::endl
                  << KMAG "    // <map> copy constructors and iterators:" KNRM << std::endl
                  << std::endl;

    ft::map<int, int> mapB(mapA);
    ft::map<int, int> mapC(mapB.begin(), mapB.end());
    ft::map<int, int> mapD;
    mapD = mapC;

    // print content of all maps and check iterators compatiblity
    ft::map<int, int>::const_iterator const_iterator_begin = mapA.begin();
    ft::map<int, int>::iterator iterator_end = mapA.end();
    for (; const_iterator_begin != iterator_end; ++const_iterator_begin) {
        if (verbose)
            std::cout << "    mapA[" << const_iterator_begin->first << "]: " << const_iterator_begin->second << std::endl;
    }
    if (verbose)
        std::cout << std::endl;
    for (ft::map<int, int>::const_iterator it(mapB.begin()); it != mapB.end(); ++it) {
        if (verbose)
            std::cout << "    mapB[" << it->first << "]: " << it->second << std::endl;
    }
    if (verbose)
        std::cout << std::endl;
    for (ft::map<int, int>::const_iterator it(mapC.begin()); it != mapC.end(); ++it) {
        if (verbose)
            std::cout << "    mapC[" << it->first << "]: " << it->second << std::endl;
    }
    if (verbose)
        std::cout << std::endl;
    for (ft::map<int, int>::const_iterator it(mapD.begin()); it != mapD.end(); ++it) {
        if (verbose)
            std::cout << "    mapD[" << it->first << "]: " << it->second << std::endl;
    }

    if (verbose) {
        std::cout << std::endl
                  << "    Print MapB in reverse order with iterator--" << std::endl
                  << std::endl;
        for (ft::map<int, int>::iterator it(mapB.end()); it != mapB.begin();) {
            --it;
            std::cout << "    mapB[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    if (verbose) {
        std::cout << KMAG "    // <map> size() and empty():" KNRM << std::endl
                  << std::endl;
        std::cout << "    mapA.size(): " << mapA.size() << std::endl;
        std::cout << "    is mapA empty: " << mapA.empty() << std::endl;
        std::cout << "    mapB.size(): " << mapB.size() << std::endl;
        std::cout << "    is mapB empty: " << mapB.empty() << std::endl;
        std::cout << "    mapC.size(): " << mapC.size() << std::endl;
        std::cout << "    is mapC empty: " << mapC.empty() << std::endl;
        std::cout << "    mapD.size(): " << mapD.size() << std::endl;
        std::cout << "    is mapD empty: " << mapD.empty() << std::endl
                  << std::endl;
    }

    if (verbose)
        std::cout << KMAG "    // <map> erase(key), erase(iterator) and erase(first, last):" KNRM << KNRM << std::endl
                  << std::endl;

    if (verbose) {
        std::cout << "    mapA.erase(3)" << std::endl;
        std::cout << "    mapA.erase(begin())" << std::endl
                  << std::endl;
    }
    mapA.erase(3);
    mapA.erase(mapA.begin());
    if (verbose) {
        std::cout << std::endl
                  << "    mapA.size(): " << mapA.size() << std::endl
                  << "    is mapA empty: " << mapA.empty() << std::endl;
        for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
            std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }
    if (verbose)
        std::cout << "    mapA.erase(begin(), end())" << std::endl;
    mapA.erase(mapA.begin(), mapA.end());
    if (verbose) {
        std::cout << std::endl
                  << "    mapA.size(): " << mapA.size() << std::endl
                  << "    is mapA empty: " << mapA.empty() << std::endl;
        for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
            std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    if (verbose)
        std::cout << KMAG "    // <map> insert(first, last):" KNRM << std::endl
                  << std::endl
                  << "    mapA.insert(mapB.begin(), mapB.end())" << std::endl
                  << std::endl;

    mapA.insert(mapB.begin(), mapB.end());

    if (verbose) {
        std::cout << std::endl
                  << "    mapA.size(): " << mapA.size() << std::endl
                  << "    is mapA empty: " << mapA.empty() << std::endl;
        for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
            std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    if (verbose)
        std::cout << KMAG "    // <map> clear() and swap():" KNRM << std::endl
                  << std::endl
                  << "    Clear mapB and fill it with random number:" KNRM << std::endl;

    mapB.clear();
    for (int i(0); i != 10000; ++i) {
        mapB.insert(ft::make_pair(i, rand() % 10000));
    }

    if (verbose) {
        std::cout << std::endl
                  << "    mapA.size(): " << mapA.size() << std::endl
                  << "    is mapA empty: " << mapA.empty() << std::endl;
        for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
            std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl
                  << "    mapB.size(): " << mapB.size() << std::endl
                  << "    is mapB empty: " << mapB.empty() << std::endl;
        for (ft::map<int, int>::const_iterator it(mapB.begin()); it != mapB.end(); ++it) {
            std::cout << "    mapB[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    if (verbose)
        std::cout << "    mapA.swap(mapB)" << std::endl;
    mapA.swap(mapB);

    if (verbose) {
        std::cout << std::endl
                  << "    mapA.size(): " << mapA.size() << std::endl
                  << "    is mapA empty: " << mapA.empty() << std::endl;
        for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
            std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl
                  << "    mapB.size(): " << mapB.size() << std::endl
                  << "    is mapB empty: " << mapB.empty() << std::endl;
        for (ft::map<int, int>::const_iterator it(mapB.begin()); it != mapB.end(); ++it) {
            std::cout << "    mapB[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    if (verbose)
        std::cout << KMAG "    // filling mapE<char, unsigned int> with letters:" KNRM << std::endl;

    ft::map<char, unsigned int> mapE;
    for (int i(0); i != 26; ++i) {
        char letter = 'a' + i;
        mapE.insert(ft::make_pair(letter, i + 1));
    }

    if (verbose) {
        std::cout << std::endl;
        for (ft::map<char, unsigned int>::const_iterator it(mapE.begin()); it != mapE.end(); ++it) {
            std::cout << "    mapE[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

    if (verbose)
        std::cout << KMAG "    // <map> find() and count():" KNRM << std::endl
                  << std::endl
                  << "    mapB.find(3): " << mapB.find(3)->second << std::endl
                  << "    mapB.count(3): " << mapB.count(3) << std::endl
                  << "    mapB.find(100): " << mapB.find(100)->second << std::endl
                  << "    mapB.count(100): " << mapB.count(100) << std::endl
                  << std::endl;

    if (verbose)
        std::cout << KMAG "    // <map> lower_bound() and upper_bound():" KNRM << std::endl
                  << std::endl
                  << "    mapB.lower_bound(3): " << mapB.lower_bound(3)->second << std::endl
                  << "    mapB.upper_bound(3): " << mapB.upper_bound(3)->second << std::endl
                  << "    mapB.lower_bound(100): " << mapB.lower_bound(100)->second << std::endl
                  << "    mapB.upper_bound(100): " << mapB.upper_bound(100)->second << std::endl
                  << std::endl;

    if (verbose)
        std::cout << KMAG "    // <map> equal_range():" KNRM << std::endl
                  << std::endl
                  << "    mapB.equal_range(3): " << mapB.equal_range(3).first->second << " "
                  << mapB.equal_range(3).second->second << std::endl
                  << "    mapB.equal_range(100): " << mapB.equal_range(100).first->second << " "
                  << mapB.equal_range(100).second->second << std::endl
                  << std::endl;

    if (verbose)
        std::cout << KMAG "    // <map> operator[]:" KNRM << std::endl
                  << std::endl
                  << "    mapB[3]: " << mapB[3] << std::endl
                  << "    mapB[100]: " << mapB[100] << std::endl
                  << std::endl;

    if (verbose)
        std::cout << KMAG "    // <map> relational operators:" KNRM << std::endl
                  << std::endl
                  << "    mapA == mapB: " << (mapA == mapB) << std::endl
                  << "    mapA != mapB: " << (mapA != mapB) << std::endl
                  << "    mapA < mapB: " << (mapA < mapB) << std::endl
                  << "    mapA <= mapB: " << (mapA <= mapB) << std::endl
                  << "    mapA > mapB: " << (mapA > mapB) << std::endl
                  << "    mapA >= mapB: " << (mapA >= mapB) << std::endl
                  << std::endl;

    if (verbose) {
        std::cout << KMAG "    // <map> reverse iterators:" KNRM << std::endl
                  << std::endl;
        for (ft::map<int, int>::reverse_iterator it(mapD.rbegin()); it != mapD.rend(); it++) {
            std::cout << "    mapD[" << it->first << "]: " << it->second << std::endl;
        }
        std::cout << std::endl;
    }

#ifndef STD
    if (timer) print_test_time("ft::map", start);
#else
    if (timer) print_test_time("std::map", start);
#endif

    ///////////////////////////////////////////////////////////////////////////////////
    ////                       END OF MAP TESTS                                      //
    ///////////////////////////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////////
//                      END OF CONTAINER TESTS                                   //
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//                                USER INPUT                                     //
///////////////////////////////////////////////////////////////////////////////////
int main(int ac, char** av) {

    bool verbose = false, timer = false, pair = false, stack = false, vector = false, map = false, all = false;

    if (ac > 1) {
        for (int i(1); i != ac; ++i) {
            if (std::string(av[i]) == "-vv" || std::string(av[i]) == "--verbose")
                verbose = true;
            else if (std::string(av[i]) == "-t" || std::string(av[i]) == "--time")
                timer = true;
            else if (std::string(av[i]) == "-l" || std::string(av[i]) == "--logfile") {
#ifndef STD
                freopen("logfiles/ft_containers.log", "w", stdout);
#else
                freopen("logfiles/std_containers.log", "w", stdout);
#endif
                verbose = true;
            } else if (std::string(av[i]) == "-p" || std::string(av[i]) == "--pair")
                pair = true;
            else if (std::string(av[i]) == "-m" || std::string(av[i]) == "--map")
                map = true;
            else if (std::string(av[i]) == "-s" || std::string(av[i]) == "--stack")
                stack = true;
            else if (std::string(av[i]) == "-v" || std::string(av[i]) == "--vector")
                vector = true;
            else if (std::string(av[i]) == "-a" || std::string(av[i]) == "--all")
                pair = stack = vector = map = all = true;
        }
        struct timeval global_start;
        gettimeofday(&global_start, NULL);
        if (pair) pair_tests(verbose, timer);
        if (stack) stack_tests(verbose, timer);
        if (vector) vector_tests(verbose, timer);
        if (map) map_tests(verbose, timer);

#ifndef STD
        if (timer) print_test_time("ft containers global", global_start);
#else
        if (timer) print_test_time("STL containers global", global_start);
#endif
    } else {
        std::cout << "42Paris ft_containers" << std::endl;
        std::cout << "Usage: " << av[0] << " [-vv | --verbose] [-t | --time] [-l | --logfile] [-p | --pair] [-m | --map] [-s | --stack] [-v | --vector] [-a | --all]" << std::endl;
        std::cout << "GENERAL:" KNRM << std::endl;
        std::cout << "  -vv, --verbose: Print tests on stdout" << std::endl;
        std::cout << "  -t, --time: Print execution time" << std::endl;
        std::cout << "  -l, --logfile: Print tests into a log file";
#ifndef STD
        std::cout << " (ft_containers.log)" << std::endl;
        std::cout << "AVAILABLE TESTS:" KNRM << std::endl;
        std::cout << "  -s, --stack: ft::stack tests" << std::endl;
        std::cout << "  -p, --pair: ft::pair tests" << std::endl;
        std::cout << "  -v, --vector: ft::vector tests" << std::endl;
        std::cout << "  -m, --map: ft::map tests" << std::endl;
        std::cout << "  -a, --all: All tests" << std::endl;
        std::cout << "EXAMPLES:" KNRM << std::endl;
        std::cout << "  " << av[0] << " -vv -t -m" << std::endl;
        std::cout << "  " << av[0] << " -vv -s" << KNRM << std::endl;
        std::cout << "  " << av[0] << " -vv -l -a; ./std_containers -vv -l -a; diff logfiles/ft_containers.log logfiles/std_containers.log" << std::endl;
#else
        std::cout << " (std_containers.log)" << std::endl;
        std::cout << "AVAILABLE TESTS:" KNRM << std::endl;
        std::cout << "  -s, --stack: std::stack tests" << std::endl;
        std::cout << "  -p, --pair: std:pair tests" << std::endl;
        std::cout << "  -v, --vector: std::vector tests" << std::endl;
        std::cout << "  -m, --map: std::map tests" << std::endl;
        std::cout << "  -a, --all: All tests" << std::endl;
        std::cout << "EXAMPLES:" KNRM << std::endl;
        std::cout << "  " << av[0] << " -vv -t -m" << std::endl;
        std::cout << "  " << av[0] << " -vv -s" << KNRM << std::endl;
        std::cout << "  " << av[0] << " -vv -l -a; ./ft_containers -vv -l -a; diff logfiles/ft_containers.log logfiles/std_containers.log" << std::endl;

#endif

        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}