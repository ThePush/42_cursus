#include "utils.hpp"

int get_index(std::string key[], std::string level) {

    int index;

    for (index = 0; index < 5; index++)
        if (not(key[index].compare(level)))
            break;

    return index;
}