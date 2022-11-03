#include "colors.hpp"

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

enum types { typeChar,
    typeInt,
    typeFloat,
    typeDouble,
    typeOther };

static void check_args(int ac) {
    if (ac != 2) {
        std::cout << KRED " Error:" << std::endl
                  << " • Wrong argument format" << std::endl
                  << std::endl
                  << KGRN " Usage:" << std::endl
                  << " • ./convert <number_to_convert>" << std::endl
                  << std::endl
                  << " Number to convert must be of type:" << std::endl
                  << " • char (printable)" << std::endl
                  << " • int" << std::endl
                  << " • float" << std::endl
                  << " • double" << std::endl
                  << " • NaN / NaNf" << std::endl
                  << " • +inf / -inf" << std::endl
                  << " • +inff / -inff" KNRM << std::endl;

        exit(EXIT_FAILURE);
    }
}

static void convert_char(std::string character) {

    if ((static_cast<int>(character[0]) < 32) or (static_cast<int>(character[0]) > 126))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(character[0]) << "'" << std::endl;

    std::cout << "int: " << static_cast<int>(character[0]) << std::endl;
    std::cout << "float: " << static_cast<float>(character[0]) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(character[0]) << ".0" << std::endl;
}

static void convert_int(std::string integer) {

    double number = strtod(integer.c_str(), NULL);

    if ((static_cast<int>(number) < 32) or (static_cast<int>(number) > 126))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(number) << "'" << std::endl;

    std::cout << "int: " << static_cast<int>(number) << std::endl;
    std::cout << "float: " << static_cast<float>(number) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(number) << ".0" << std::endl;
}

static bool only_zero_in_fractional(std::string floating) {

    size_t i(0);

    while (floating[i] != '.')
        i++;

    i++;

    while (floating[i] != 'f') {
        if (floating[i] != '0')
            return false;
        i++;
    }

    return true;
}

static void convert_float(std::string floating) {

    double number = strtod(floating.c_str(), NULL);

    if ((static_cast<int>(number) < 32) or (static_cast<int>(number) > 126))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(number) << "'" << std::endl;

    if (number > std::numeric_limits<int>::max()
        or number < std::numeric_limits<int>::min())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(number) << std::endl;
    if (only_zero_in_fractional(floating)) {
        std::cout.precision(std::numeric_limits<float>::digits10);
        std::cout << "float: " << static_cast<float>(number) << ".0f" << std::endl;
        std::cout.precision(std::numeric_limits<double>::digits10);
        std::cout << "double: " << number << ".0" << std::endl;
    } else {
        std::cout.precision(std::numeric_limits<float>::digits10);
        std::cout << "float: " << static_cast<float>(number) << 'f' << std::endl;
        std::cout.precision(std::numeric_limits<double>::digits10);
        std::cout << "double: " << number << std::endl;
    }
}

static void convert_double(std::string doublef) {

    double number = strtod(doublef.c_str(), NULL);

    if ((static_cast<int>(number) < 32) or (static_cast<int>(number) > 126))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(number) << "'" << std::endl;

    if (number > std::numeric_limits<int>::max()
        or number < std::numeric_limits<int>::min())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(number) << std::endl;
    std::cout.precision(std::numeric_limits<float>::digits10);
    std::cout << "float: " << static_cast<float>(number) << 'f' << std::endl;
    std::cout.precision(std::numeric_limits<double>::digits10);
    std::cout << "double: " << number << std::endl;
}

static void print_impossible(std::string character, std::string integer, std::string floating, std::string doublef) {
    std::cout << "char: " << character << std::endl;
    std::cout << "int: " << integer << std::endl;
    std::cout << "float: " << floating << std::endl;
    std::cout << "double: " << doublef << std::endl;
}

static void convert_impossible(std::string impossible) {

    if (not(impossible.compare("+inf")) or not(impossible.compare("+inff")))
        print_impossible("impossible", "impossible", "inff", "inf");
    else if (not(impossible.compare("-inf")) or not(impossible.compare("-inff")))
        print_impossible("impossible", "impossible", "-inff", "-inf");
    else if (not(impossible.compare("nan")) or not(impossible.compare("nanf")))
        print_impossible("impossible", "impossible", "nanf", "nan");
    else
        check_args(0);
}

static int type_detection(char* av) {

    if ((strlen(av) == 1) and not(isdigit(*av)))
        return typeChar;

    char* endptr;
    double number = strtod(av, &endptr);

    if (not(*endptr) and not(static_cast<int>(number) - number)
        and static_cast<int>(number) >= std::numeric_limits<int>::min()
        and static_cast<int>(number) <= std::numeric_limits<int>::max())
        return typeInt;

    if (strlen(endptr) == 1 and *endptr == 'f'
        and static_cast<float>(number) >= -std::numeric_limits<float>::max()
        and static_cast<float>(number) <= std::numeric_limits<float>::max())
        return typeFloat;

    if (strchr(av, '.') and not(*endptr) and (number == atof(av)))
        return typeDouble;

    return typeOther;
}

int main(int ac, char** av) {

    check_args(ac);

    switch (type_detection(av[1])) {

    case typeChar:
        // std::cout << "char" << std::endl;
        convert_char(std::string(av[1]));
        break;

    case typeInt:
        // std::cout << "int" << std::endl;
        convert_int(std::string(av[1]));
        break;

    case typeFloat:
        // std::cout << "float" << std::endl;
        convert_float(std::string(av[1]));
        break;

    case typeDouble:
        // std::cout << "double" << std::endl;
        convert_double(std::string(av[1]));
        break;

    case typeOther:
        // std::cout << "other" << std::endl;
        convert_impossible(std::string(av[1]));
        break;
    }

    return EXIT_SUCCESS;
}

// Constant std::numeric_limits<T>::digits10 returns the number of decimal digits that can be represented without change or loss.
// https://www.boost.org/doc/libs/1_63_0/libs/multiprecision/doc/html/boost_multiprecision/tut/limits/constants.html