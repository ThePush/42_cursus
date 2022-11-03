#include "Contact.hpp"
#include "PhoneBook.hpp"
#include "display.hpp"

int main(int ac, char** av) {

    (void)av;

    if (ac != 1) {
        std::cout << KRED " Error:" << std::endl
                  << " • No argument needed" KNRM << std::endl;
        exit(1);
    }

    std::string prompt;
    PhoneBook phonebook;

    display_welcome_message();
    while (true) {
        std::cout << KBLU " Enter a [command] > " KWHT;
        std::getline(std::cin, prompt);
        std::cout << KMAG;
        if (not(prompt.compare("ADD")) or not(prompt.compare("add"))) {
            phonebook.setContact();
        } else if (not(prompt.compare("SEARCH")) or not(prompt.compare("search"))) {
            phonebook.searchContact();
        } else if (std::cin.eof() or not(prompt.compare("EXIT")) or not(prompt.compare("exit"))) {
            display_exit();
            break;
        } else if (not(prompt.compare("USAGE")) or not(prompt.compare("usage"))) {
            display_usage();
        } else {
            display_error_usage();
        }
        std::cin.clear();
    }
    std::cout << std::endl;

    return 0;
}