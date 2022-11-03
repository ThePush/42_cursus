#include "colors.hpp"

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"

#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <unistd.h>

// Robert Jenkins' 96 bit Mix Function
// https://en.wikipedia.org/wiki/Robert_John_Jenkins_Junior
// https://en.wikipedia.org/wiki/Pseudorandom_number_generator
unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
    a = a - b;
    a = a - c;
    a = a ^ (c >> 13);
    b = b - c;
    b = b - a;
    b = b ^ (a << 8);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 13);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 12);
    b = b - c;
    b = b - a;
    b = b ^ (a << 16);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 5);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 3);
    b = b - c;
    b = b - a;
    b = b ^ (a << 10);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 15);
    return c;
}

Base* generate(void) {

    unsigned long seed = mix(clock(), time(NULL), getpid());
    srand(seed);

    switch (rand() % 3) {
    case 0:
        std::cout << " generate(): Instantiation of class A" << std::endl;
        return new A;
    case 1:
        std::cout << " generate(): Instantiation of class B" << std::endl;
        return new B;
    default:
        std::cout << " generate(): Instantiation of class C" << std::endl;
        return new C;
    }
}

// cast will return a NULL pointer if it fails
void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << " identify(Base* p): Identified class A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << " identify(Base* p): Identified class B" << std::endl;
    else
        std::cout << " identify(Base* p): Identified class C" << std::endl;
}

// NULL reference is impossible so we use try/catch
void identify(Base& p) {
    try {
        A& a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << " identify(Base& p): Identified class A" << std::endl;
        return;
    } catch (std::exception& e) {
}

    try {
        B& b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << " identify(Base& p): Identified class B" << std::endl;
        return;
    } catch (std::exception& e) {
        std::cout << " identify(Base& p): Identified class C" << std::endl;
    }
}

int main(void) {

    std::cout << KMAG;

    std::cout << KMAG "============================= [ TEST ] dynamic_cast ========================" << std::endl
              << std::endl;

    std::cout << KMAG "[ Random class Instantiation ]" << std::endl;
    Base* base = generate();
    std::cout << std::endl;

    std::cout << KMAG "[ Identification by pointer ]" << std::endl;
    identify(base);
    std::cout << std::endl;

    std::cout << KMAG "[ Identification by reference ]" << std::endl;
    identify(*base);

    delete base;

    std::cout << KNRM;

    return EXIT_SUCCESS;
}

// RTTI
// https://www.geeksforgeeks.org/rtti-run-time-type-information-in-cpp/