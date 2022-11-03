#include "colors.hpp"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static void check_arguments(int ac, char** av) {

    if (ac != 4) {
        std::cout << KRED " Error:" << std::endl
                  << "  • Wrong argument number" << std::endl
                  << KGRN " Usage:" << std::endl
                  << "  ./Sed_is_for_losers [filename] [occurence_to_replace] [replacement_string]" KNRM << std::endl;

        exit(EXIT_FAILURE);
    }

    if (std::string(av[1]).empty() or std::string(av[2]).empty()) {
        std::cout << KRED " Error:" << std::endl
                  << "  • [filename] and [occurence_to_replace] cannot be empty" << std::endl;

        exit(EXIT_FAILURE);
    }
}

static void open_streams(char* av, std::ifstream* infile, std::ofstream* outfile) {

    infile->open(av, std::ios::in);
    if (not(infile->is_open())) {
        std::cout << KRED " Error:" << std::endl
                  << "  • Could not open input file [" << av << "]" << KNRM << std::endl;

        exit(EXIT_FAILURE);
    } else {
        if (infile->peek() == std::ifstream::traits_type::eof()) {
            std::cout << KRED " Error:" << std::endl
                      << "  • Empty file [" << av << "]" << KNRM << std::endl;

            exit(EXIT_FAILURE);
        }
    }

    outfile->open(((std::string(av)).append(".replace")).c_str(), std::ios::out);
    if (not(outfile->is_open())) {
        std::cout << KRED " Error:" << std::endl
                  << "  • Could not open/create output file [" << ((std::string(av)).append(".replace")).c_str()
                  << "]" << KNRM << std::endl;

        exit(EXIT_FAILURE);
    }
}

/**
 * It reads a line from the input file, finds the first occurrence of the string to be replaced, erases
 * it, and inserts the replacement string in its place. It then repeats this process until it reaches
 * the end of the line. It then writes the line to the output file, and repeats the process until it
 * reaches the end of the input file
 * 
 * @param av the command line arguments
 * @param infile The input file stream.
 * @param outfile The file to write to.
 */
static void replace(char** av, std::ifstream* infile, std::ofstream* outfile) {

    std::string line;
    size_t index;

    while (getline(*infile, line)) {
        index = line.find(av[2]);

        while (index != std::string::npos) {
            line.erase(index, std::string(av[2]).length());
            line.insert(index, av[3]);
            index = line.find(av[2], index + std::string(av[3]).size());
        }
        *outfile << line;
        if (not(infile->eof()))
            *outfile << std::endl;
    }
}

int main(int ac, char** av) {

    check_arguments(ac, av);

    std::ifstream infile;
    std::ofstream outfile;

    open_streams(av[1], &infile, &outfile);

    replace(av, &infile, &outfile);

    infile.close();
    outfile.close();

    return EXIT_SUCCESS;
}