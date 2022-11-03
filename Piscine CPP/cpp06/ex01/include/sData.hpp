#ifndef SDATA_HPP
#define SDATA_HPP

#include <iostream>
#include <stdint.h>

typedef struct s_Data {
    std::string str;
    int number;
} Data;

uintptr_t serialize(Data* ptr);
Data* deserialize(uintptr_t raw);

#endif