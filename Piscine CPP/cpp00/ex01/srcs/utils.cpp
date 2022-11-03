#include "utils.hpp"
#include "display.hpp"

bool str_isdigit(const std::string& str) {
    for (unsigned int i(0); i != str.length(); ++i) {
        if (not(std::isdigit(str[i])))
            return false;
    }
    return true;
}

bool str_isalnum(const std::string& str) {
    for (unsigned int i(0); i != str.length(); ++i) {
        if (not(std::isalnum(str[i])))
            return false;
    }
    return true;
}

bool str_has_space(const std::string& str) {
    for (unsigned int i(0); i != str.length(); ++i) {
        if (std::isspace(str[i]))
            return true;
    }
    return false;
}