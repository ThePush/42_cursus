#ifndef UTILS_HPP
#define UTILS_HPP

template <typename Type>
void print_brain(Type& toPrint) {
    Brain* copycatbrain = toPrint.getBrain();
    std::string const* cbrain_array = copycatbrain->getIdeas();
    for (int i(0); i != 100; ++i) {
        std::cout << cbrain_array[i];
        if (i != 99)
            std::cout << ", ";
        else
            std::cout << ".";
    }
}

#endif // UTILS_HPP