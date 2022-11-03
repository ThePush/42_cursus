#include "colors.hpp"

#include "Span.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <unistd.h>
#include <vector>

static unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
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

static int random_number() {
    srand(mix(clock(), time(NULL), getpid()));
    return rand();
}

int main(int ac, char** av) {

    std::cout << KMAG;

    std::cout << KMAG "====================== [ TEST ] Iterators ====================" << std::endl
              << std::endl;

    bool verbose = false;
    if (ac > 1 and not(std::string(av[1]).compare("-v"))) {
        verbose = true;
        std::cout << "Verbose mode: [ON]" << std::endl;
    } else
        std::cout << "Verbose mode: [OFF]" << std::endl;
    std::cout << std::endl;

    std::cout << KMAG "========== Trying longestSpan() on an empty vector: ==========" << std::endl
              << std::endl;

    Span span = Span(5);
    try {
        std::cout << " longestSpan(): " << span.longestSpan() << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl
              << std::endl;
    ;

    std::cout << KMAG "========== Try to add too many values to a vector: ===========" << std::endl
              << std::endl;
    try {
        span.addNumber(random_number());
        span.addNumber(random_number());
        span.addNumber(random_number());
        span.addNumber(random_number());
        span.addNumber(random_number());
        span.addNumber(random_number());
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl
              << std::endl;
    ;

    std::cout << KMAG "==================== Call longestSpan() ======================" << std::endl
              << std::endl;

    if (verbose)
        span.printVector();

    std::cout << std::endl;

    try {
        std::cout << " longestSpan(): " << span.longestSpan() << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl
              << std::endl;

    std::cout << KMAG "==================== Call shortestSpan() =====================" << std::endl
              << std::endl;

    if (verbose)
        span.printVector();

    std::cout << std::endl;

    try {
        std::cout << " shortestSpan(): " << span.shortestSpan() << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl
              << std::endl;

    std::cout << KMAG "=============== Call to overloaded addNumber() ===============" << std::endl
              << std::endl;

    Span fat_span = Span(15000);
    std::vector<int> init_vec(15000);
    std::generate(init_vec.begin(), init_vec.end(), random_number);
    try {
        fat_span.addNumber(init_vec.begin(), init_vec.end());
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl;

    try {
        std::cout << KMAG " shortestSpan(): " << fat_span.shortestSpan() << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    std::cout << std::endl;

    try {
        std::cout << KMAG " longestSpan(): " << fat_span.longestSpan() << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl
              << std::endl;

    std::cout << KMAG "== Try to add too many values to a vector with addNumber(): ==" << std::endl
              << std::endl;

    try {
        fat_span.addNumber(init_vec.begin(), init_vec.end());
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl;

    std::cout << KNRM;

    return EXIT_SUCCESS;
}
