#include "colors.hpp"

#include "sData.hpp"

#include <cstdlib>

int main(void) {
    Data ptr;
    ptr.str = "I fly like paper get high like planes";
    ptr.number = 1312;

    std::cout << KMAG "============================= [ TEST ] reinterpret_cast ========================" << std::endl
              << std::endl;

    std::cout << " • " KYEL "ptr" KMAG " is a" KGRN " structure " KMAG " of defined type Data that contains a string and an integer " << std::endl
              << " • " KYEL "raw" KMAG " is an" KGRN " uintptr_t " KMAG "to which ptr will be converted to and back" << std::endl
              << std::endl;

    std::cout << KCYN " [ ptr data members values at beginning ]" << std::endl;
    std::cout << " str: " << ptr.str << std::endl
              << " number: " << ptr.number << KMAG << std::endl
              << std::endl;

    std::cout << " First we convert" KYEL " ptr " KMAG "from a " KGRN "structure" KMAG " to an " KGRN "uintptr_t" KMAG " and store it in " KYEL "raw" KMAG << std::endl
              << std::endl;

    uintptr_t raw = serialize(&ptr);

    std::cout << KCYN " [ raw value after call to \"raw = serialized(&ptr)\" ] " << std::endl
              << " " << raw << KMAG << std::endl
              << std::endl;

    std::cout << " Then we convert" KYEL " raw " KMAG "back from an " KGRN "uintptr_t" KMAG " to a " KGRN "structure" KMAG
                 " and store it in " KYEL "ptr" KMAG
              << std::endl
              << std::endl;

    ptr = *deserialize(raw);

    std::cout << KCYN " [ ptr data members after call to \"ptr = *deserialized(raw)\" ]" << std::endl
              << " str: " << ptr.str << std::endl
              << " number: " << ptr.number << KNRM << std::endl;

    return EXIT_SUCCESS;
}

/*
MAN:
uintptr_t
Include: <stdint.h>. Alternatively, <inttypes.h>.
An unsigned integer type such that any valid (void *) value can be converted to this type and back.
According to the C language standard, it shall be capable of storing values in the range [0, UINTPTR_MAX].
*/