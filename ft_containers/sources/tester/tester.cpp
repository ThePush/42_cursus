#include "../../include/colors/colors.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <unistd.h>

// https://www.tutorialspoint.com/How-to-execute-a-command-and-get-the-output-of-command-within-Cplusplus-using-POSIX
std::string exec(std::string command) {
    char buffer[128];
    std::string result = "";

    // Open pipe to file
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) { return "popen failed!"; }

    // read til end of process:
    while (!feof(pipe)) {

        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);
    return result;
}

void print_usage(char** av) {
    std::cout << "42Paris ft_containers" << std::endl;
    std::cout << "Usage: " << av[0] << " [-vv | --verbose] [-t | --time] [-l | --logfile] [-d | --diff] [-vg | --valgrind] [-p | --pair] [-m | --map] [-s | --stack] [-v | --vector] [-a | --all]" << std::endl;
    std::cout << "GENERAL:" << std::endl;
    std::cout << "  -vv, --verbose: Print tests on stdout" << std::endl;
    std::cout << "  -t, --time: Print execution time" << std::endl;
    std::cout << "  -l, --logfile: Print tests into logs files" << std::endl;
    std::cout << "  -d, --diff: Print diff between ft::<container> tests and std::<container> tests" << std::endl;
    std::cout << "  -vg, --valgrind: Test memory leaks" << std::endl;
    std::cout << "AVAILABLE TESTS:" << std::endl;
    std::cout << "  -p, --pair: Pair tests" << std::endl;
    std::cout << "  -s, --stack: Stack tests" << std::endl;
    std::cout << "  -v, --vector: Vector tests" << std::endl;
    std::cout << "  -m, --map: Map tests" << std::endl;
    std::cout << "  -a, --all: All tests" << std::endl;
    std::cout << "EXAMPLES:" << std::endl;
    std::cout << "  " << av[0] << " -vv -d -m" << std::endl;
    std::cout << "  " << av[0] << " -vv -s" << std::endl;
    std::cout << "  " << av[0] << " -vv -a -t -d -vg" << std::endl;
}

int main(int ac, char** av) {

    std::string options = "";
    std::string valgrind = "";
    bool diff = false, time = false, verbose = false;

    if (ac == 1) {
        print_usage(av);
        return EXIT_SUCCESS;
    }

    for (int i(1); i != ac; ++i) {
        if (std::string(av[i]) == "-vv" || std::string(av[i]) == "--verbose") {
            options += " -vv";
            verbose = true;
        } else if (std::string(av[i]) == "-t" || std::string(av[i]) == "--time") {
            time = true;
            options += " -t";
        } else if (std::string(av[i]) == "-l" || std::string(av[i]) == "--logfile")
            options += " -l";
        else if (std::string(av[i]) == "-p" || std::string(av[i]) == "--pair")
            options += " -p";
        else if (std::string(av[i]) == "-m" || std::string(av[i]) == "--map")
            options += " -m";
        else if (std::string(av[i]) == "-s" || std::string(av[i]) == "--stack")
            options += " -s";
        else if (std::string(av[i]) == "-v" || std::string(av[i]) == "--vector")
            options += " -v";
        else if (std::string(av[i]) == "-a" || std::string(av[i]) == "--all")
            options += " -a";
        else if (std::string(av[i]) == "-d" || std::string(av[i]) == "--diff") {
            diff = true;
            options += " -l";
        } else if (std::string(av[i]) == "-vg" || std::string(av[i]) == "--valgrind") {
            valgrind = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ";
        } else {
            std::cout << "Unknown option: " << av[i] << std::endl;
            print_usage(av);
            return EXIT_FAILURE;
        }
    }

    std::string cmd_ft = "";
    std::string cmd_std = "";
    std::string ft_containers = valgrind + "./ft_containers";
    std::string std_containers = valgrind + " ./std_containers";
    cmd_ft = ft_containers + options;
    cmd_std = std_containers + options;
    std::cout << "-------------------------------- FT_CONTAINERS_TEST -----------------------------------" << std::endl;
    if (!valgrind.empty())
        std::cout << "------------------------- valgrind output for ft_containers ---------------------------" << std::endl;
    std::system(cmd_ft.c_str());
    if (!valgrind.empty())
        std::cout << std::endl
                  << "-------------------------- valgrind output for std_containers -------------------------" << std::endl;
    std::system(cmd_std.c_str());
    if (!valgrind.empty())
        std::cout << "---------------------------------------------------------------------------------------" << std::endl;

    if (diff) {
        if (verbose) {
            std::string ft_containers_log = exec("cat logfiles/ft_containers.log");
            std::string std_containers_log = exec("cat logfiles/std_containers.log");
            std::cout << ft_containers_log << std::endl;
            std::cout << "---------------------------------------------------------------------------------------" << std::endl;
            std::cout << std_containers_log << std::endl;
        }
        if (valgrind.empty())
            std::cout << "---------------------------------------------------------------------------------------" << std::endl;
        exec("diff -d -I 'STD::' -I 'FT::' logfiles/std_containers.log logfiles/ft_containers.log > logfiles/diff.log");
        std::string diff_log = exec("cat logfiles/diff.log");
        if (diff_log.empty()) {
            std::cout << KGRN << "[SUCCESS] All tests passed, no difference between ft_containers.log and std_containers.log" KNRM << std::endl;
        } else if (!diff_log.empty() && time == true) {
            exec("diff -d -I 'STD::' -I 'FT::' -I 'time' logfiles/std_containers.log logfiles/ft_containers.log > logfiles/no_time.log");
            std::string diff_time = exec("cat logfiles/no_time.log");
            if (diff_time.empty()) {
                std::cout << KGRN << "[SUCCESS] All tests passed, no difference between ft_containers.log and std_containers.log (except time)" KNRM << std::endl;
            } else {
                std::cout << KRED << "[FAIL] Difference between ft_containers.log and std_containers.log" KNRM << std::endl;
            }
        } else {
            std::cout << KRED << "[FAIL] Difference between ft_containers.log and std_containers.log" KNRM << std::endl;
        }
        std::cout << "Print diff log: logfiles/diff.log" << std::endl;
        std::cout << diff_log << std::endl;
        std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    }
    return EXIT_SUCCESS;
}