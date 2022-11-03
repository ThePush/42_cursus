#include "colors.hpp"

#include "Array.tpp"

#include <cstdlib>
#include <iostream>
#include <unistd.h>

static bool str_isdigit(const std::string& str) {
    for (unsigned int i(0); i != str.length(); ++i) {
        if (not(std::isdigit(str[i])))
            return false;
    }
    return true;
}

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

static char random_char() {
    int ret = random_number() % 126;

    while (ret < 33) {
        ret += (random_number() % 126);
        ret %= 126;
    }
    return static_cast<char>(ret);
}

int main(int ac, char** av) {

    std::cout << KMAG;

    std::cout << KMAG "=================== [ TEST ] Template class =================" << std::endl
              << std::endl;

    bool verbose = false;
    if (ac > 1 and not(std::string(av[1]).compare("-v"))) {
        verbose = true;
        std::cout << "Verbose mode: [ON]" << std::endl;
    } else
        std::cout << "Verbose mode: [OFF]" << std::endl;

    size_t arrlen;
    if (ac > 1 and str_isdigit(std::string(av[1])))
        arrlen = std::atoi(av[1]);
    else if (ac > 2 and str_isdigit(std::string(av[2])))
        arrlen = std::atoi(av[2]);
    else
        arrlen = 10;
    std::cout << "Array size: " << arrlen << std::endl
              << std::endl;

    std::cout << KMAG "========================= [ INTEGERS ] ======================" << std::endl
              << std::endl;

    Array<int> array_source(arrlen);
    int* array_check = new int[arrlen];
    std::cout << " [ Filling an array_source with random integers... ] ";
    for (size_t i(0); i != arrlen; ++i) {
        array_source[i] = random_number();
        array_check[i] = array_source[i];
        if (verbose) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_source[" << i << "]: " << array_source[i] << std::endl;
        }
    }
    std::cout << KGRN "[ OK ]" KMAG << std::endl;
    std::cout << std::endl;

    std::cout << " [ Copying array_source to array_copy... ] ";
    Array<int> array_copy(array_source);
    if (verbose) {
        for (size_t i(0); i != arrlen; ++i) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_copy[" << i << "]: " << array_copy[i] << std::endl;
        }
    }
    std::cout << KGRN "[ OK ]" KMAG << std::endl;
    std::cout << std::endl;

    std::cout << " [ Filling array_source with new random integers... ] ";
    for (size_t i(0); i != arrlen; ++i) {
        array_source[i] = random_char();
        if (verbose) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_source[" << i << "]: " << array_source[i] << std::endl;
        }
    }
    std::cout << KGRN "[ OK ]" KMAG << std::endl;
    std::cout << std::endl;

    std::cout << " [ Check if array_copy has been modified... ] ";
    bool check = true;
    for (size_t i(0); i != arrlen; ++i) {
        if (array_check[i] != array_copy[i]) {
            std::cerr << KRED " Error: array_copy has been modified" KMAG << std::endl;
            check = false;
        }
    }

    if (verbose) {
        for (size_t i(0); i != arrlen; ++i) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_copy[" << i << "]:  " << array_copy[i] << std::endl;
            std::cout << "array_check[" << i << "]: " << array_check[i] << std::endl;
            if (array_copy[i] == array_check[i])
                std::cout << KGRN "[ OK ]" KMAG << std::endl;
            else
                std::cerr << KRED "[ FAILED ]" KMAG << std::endl;
            std::cout << std::endl;
        }
    } else if (check)
        std::cout << KGRN "[ OK ]" KMAG << std::endl
                  << std::endl;
    else
        std::cerr << KRED "[ FAILED ]" KMAG << std::endl
                  << std::endl;

    std::cout << KMAG " [ Trying to access a value in array_copy ] ";
    try {
        std::cout << std::endl
                  << "array_copy[arrlen - 1]: ";
        std::cout << array_copy[arrlen - 1];
        std::cout << KGRN " [ OK ]" KMAG << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl;

    std::cout << KMAG " [ Trying to access an out of bounds value in array_copy ] ";
    try {
        std::cout << std::endl
                  << "array_copy[arrlen + random_number()]: ";
        std::cout << array_copy[arrlen + random_number()];
        std::cout << KGRN "[ OK ]" KMAG << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    std::cout << std::endl;

    std::cout << KMAG "========================= [ FLOATS ] ========================" << std::endl
              << std::endl;

    Array<float> farray_source(arrlen);
    float* farray_check = new float[arrlen];
    std::cout << " [ Filling an array_source with random floats... ] ";
    for (size_t i(0); i != arrlen; ++i) {
        farray_source[i] = static_cast<float>(random_number());
        farray_check[i] = farray_source[i];
        if (verbose) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_source[" << i << "]: " << farray_source[i] << std::endl;
        }
    }
    std::cout << KGRN "[ OK ]" KMAG << std::endl;
    std::cout << std::endl;

    std::cout << " [ Copying array_source to array_copy... ] ";
    Array<float> farray_copy(farray_source);
    if (verbose) {
        for (size_t i(0); i != arrlen; ++i) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_copy[" << i << "]: " << farray_copy[i] << std::endl;
        }
    }
    std::cout << KGRN "[ OK ]" KMAG << std::endl;
    std::cout << std::endl;

    std::cout << " [ Filling array_source with new random floats... ] ";
    for (size_t i(0); i != arrlen; ++i) {
        farray_source[i] = random_number();
        if (verbose) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_source[" << i << "]: " << farray_source[i] << std::endl;
        }
    }
    std::cout << KGRN "[ OK ]" KMAG << std::endl;
    std::cout << std::endl;

    std::cout << " [ Check if array_copy has been modified... ] ";
    bool fcheck = true;
    for (size_t i(0); i != arrlen; ++i) {
        if (farray_check[i] != farray_copy[i]) {
            std::cerr << KRED " Error: array_copy has been modified" KMAG << std::endl;
            fcheck = false;
        }
    }

    if (verbose) {
        for (size_t i(0); i != arrlen; ++i) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_copy[" << i << "]:  " << farray_copy[i] << std::endl;
            std::cout << "array_check[" << i << "]: " << farray_check[i] << std::endl;
            if (farray_copy[i] == farray_check[i])
                std::cout << KGRN "[ OK ]" KMAG << std::endl;
            else
                std::cerr << KRED "[ FAILED ]" KMAG << std::endl;
            std::cout << std::endl;
        }
    } else if (fcheck)
        std::cout << KGRN "[ OK ]" KMAG << std::endl
                  << std::endl;
    else
        std::cerr << KRED "[ FAILED ]" KMAG << std::endl
                  << std::endl;

    std::cout << KMAG " [ Trying to access a value in array_copy ] ";
    try {
        std::cout << std::endl
                  << "array_copy[arrlen - 1]: ";
        std::cout << farray_copy[arrlen - 1];
        std::cout << KGRN " [ OK ]" KMAG << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl;

    std::cout << KMAG " [ Trying to access an out of bounds value in array_copy ] ";
    try {
        std::cout << std::endl
                  << "array_copy[arrlen + random_number()]: ";
        std::cout << farray_copy[arrlen + random_number()];
        std::cout << KGRN "[ OK ]" KMAG << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    std::cout << std::endl;

    std::cout << KMAG "======================= [ CHARACTERS ] ======================" << std::endl
              << std::endl;

    Array<char> carray_source(arrlen);
    char* carray_check = new char[arrlen];
    std::cout << " [ Filling an array_source with random characters... ] ";
    for (size_t i(0); i != arrlen; ++i) {
        carray_source[i] = random_char();
        carray_check[i] = carray_source[i];
        if (verbose) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_source[" << i << "]: " << carray_source[i] << std::endl;
        }
    }
    std::cout << KGRN "[ OK ]" KMAG << std::endl;
    std::cout << std::endl;

    std::cout << " [ Copying array_source to array_copy... ] ";
    Array<char> carray_copy(carray_source);
    if (verbose) {
        for (size_t i(0); i != arrlen; ++i) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_copy[" << i << "]: " << carray_copy[i] << std::endl;
        }
    }
    std::cout << KGRN "[ OK ]" KMAG << std::endl;
    std::cout << std::endl;

    std::cout << " [ Filling array_source with new random characters... ] ";
    for (size_t i(0); i != arrlen; ++i) {
        carray_source[i] = random_char();
        if (verbose) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_source[" << i << "]: " << carray_source[i] << std::endl;
        }
    }
    std::cout << KGRN "[ OK ]" KMAG << std::endl;
    std::cout << std::endl;

    std::cout << " [ Check if array_copy has been modified... ] ";
    bool ccheck = true;
    for (size_t i(0); i != arrlen; ++i) {
        if (carray_check[i] != carray_copy[i]) {
            std::cerr << KRED " Error: array_copy has been modified" KMAG << std::endl;
            check = false;
        }
    }

    if (verbose)
        for (size_t i(0); i != arrlen; ++i) {
            if (i == 0)
                std::cout << std::endl;
            std::cout << "array_copy[" << i << "]:  " << carray_copy[i] << std::endl;
            std::cout << "array_check[" << i << "]: " << carray_check[i] << std::endl;
            if (carray_copy[i] == carray_check[i])
                std::cout << KGRN "[ OK ]" KMAG << std::endl;
            else
                std::cerr << KRED "[ FAILED ]" KMAG << std::endl;
            std::cout << std::endl;
        }
    else if (ccheck)
        std::cout << KGRN "[ OK ]" KMAG << std::endl
                  << std::endl;
    else
        std::cerr << KRED "[ FAILED ]" KMAG << std::endl
                  << std::endl;

    std::cout << KMAG " [ Trying to access a value in array_copy ] ";
    try {
        std::cout << std::endl
                  << "array_copy[arrlen - 1]: ";
        std::cout << carray_copy[arrlen - 1];
        std::cout << KGRN " [ OK ]" KMAG << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }
    std::cout << std::endl;

    std::cout << KMAG " [ Trying to access an out of bounds value in array_copy ] ";
    try {
        std::cout << std::endl
                  << "array_copy[arrlen + random_number()]: ";
        std::cout << carray_copy[arrlen + random_number()];
        std::cout << KGRN "[ OK ]" KMAG << std::endl;
    } catch (std::exception& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    delete[] array_check;
    delete[] farray_check;
    delete[] carray_check;

    std::cout << KNRM;

    return EXIT_SUCCESS;
}
