#include "display.hpp"
#include "Contact.hpp"
#include "PhoneBook.hpp"

void display_welcome_message(void) {

    std::cout << KMAG " =========================================================" << std::endl;
    std::cout << " *        _                      _                 _     *" << std::endl;
    std::cout << " *  _ __ | |__   ___  _ __   ___| |__   ___   ___ | | __ *" << std::endl;
    std::cout << " * | '_ \\| '_ \\ / _ \\| '_ \\ / _ \\ '_ \\ / _ \\ / _ \\| |/ / *" << std::endl;
    std::cout << " * | |_) | | | | (_) | | | |  __/ |_) | (_) | (_) |   <  *" << std::endl;
    std::cout << " * | .__/|_| |_|\\___/|_| |_|\\___|_.__/ \\___/ \\___/|_|\\_\\ *" << std::endl;
    std::cout << " * | |             _   _                    _____        *" << std::endl;
    std::cout << " * | |              \\ /                    (.---.)-._.-. *" << std::endl;
    std::cout << " * | |               V                      /:::\\ _.---' *" << std::endl;
    std::cout << " * |_|crappy awesome   software            '-----'       *" << std::endl;
    std::cout << " =========================================================" << std::endl
         << std::endl;
    std::cout << " ************************ Usage **************************" << std::endl;
    std::cout << KBLU " • Please enter:" << std::endl
         << std::endl;
    std::cout << "       - [ADD] to save a new contact" << std::endl;
    std::cout << "       - [SEARCH] to display a specific contact" << std::endl;
    std::cout << "       - [EXIT] to quit crappy_awesome_phonebook_software" KMAG << std::endl
         << std::endl;
    std::cout << " *********************************************************" << std::endl;
}

void display_error_usage(void) {
    std::cout << KRED << std::endl
         << " Error:" << std::endl
         << " • Please enter a valid command, type USAGE to get a list" << std::endl
         << "   of commands" << KMAG << std::endl
         << std::endl;
    std::cout << " *********************************************************" << std::endl;
}

void display_usage(void) {
    std::cout << std::endl << KMAG " *********************************************************" << std::endl;
    std::cout << KBLU " • Please enter:" << std::endl
         << std::endl;
    std::cout << "       - [ADD] to save a new contact" << std::endl;
    std::cout << "       - [SEARCH] to display a specific contact" << std::endl;
    std::cout << "       - [EXIT] to quit crappy_awesome_phonebook_software" KMAG << std::endl
         << std::endl;
    std::cout << " *********************************************************" << std::endl;
}

void display_add_contact(void) {
    std::cout << std::endl
         << " *********************************************************" << std::endl;
    std::cout << KBLU "                      -----------------" << std::endl;
    std::cout << "                      | Add a contact |" << std::endl;
    std::cout << "                      -----------------" KMAG << std::endl
         << std::endl;
}

void display_error_add_contact(void) {
    std::cout << std::endl
         << KRED " Error:" << std::endl
         << " • Field cannot be blank nor contain spaces" << std::endl << std::endl
         << " • All fields except phone number must contains" << std::endl
         << "   only alphanumeric characters" << std::endl << std::endl
         << " • Phone number's field must contains" << std::endl
         << "   only numeric characters" << std::endl << std::endl
         << "   Contact not added" << KMAG << std::endl
         << std::endl;
    std::cout << " *********************************************************" << std::endl
         << std::endl;
}

void display_contact_added_successfully(unsigned int index) {
    std::cout << std::endl
         << KGRN "           Contact successfully added at index [" << index << "]" << std::endl;
    std::cout << std::endl;
    std::cout << KMAG " *********************************************************" << std::endl;
}

void display_search(void) {
    std::cout << std::endl
         << " *********************************************************" << std::endl
         << KBLU "                    --------------------" << std::endl;
    std::cout << "                    | Search a contact |" << std::endl;
    std::cout << "                    --------------------" << std::endl
         << std::endl;
}

void display_no_contact_created_yet(void) {
    std::cout << "                  No contact created yet !" KMAG << std::endl
         << std::endl;
    std::cout << " *********************************************************" << std::endl;
}

void display_search_prompt(void) {
    std::cout << std::endl << KBLU " Enter the index of a contact to display its informations" << std::endl
         << std::endl;
    std::cout << "  Contact index > " KWHT;
}

void display_error_searched_index(void) {
    std::cout << std::endl
         << KRED " Error:" << std::endl;
    std::cout << " • Index must be a positive number between 0 and " << MAX_CONTACTS - 1 << KMAG << std::endl
         << std::endl;
    std::cout << " *********************************************************" << std::endl
         << std::endl;
}

void display_columns(void) {
    std::cout << KCYN "        ---------------------------------------------" << std::endl;
    std::cout << "        |";
    std::cout << std::setw(10) << "Index"
         << "|";
    std::cout << std::setw(10) << "First name"
         << "|";
    std::cout << std::setw(10) << "Last name"
         << "|";
    std::cout << std::setw(10) << "Nickname"
         << "|" << std::endl;
    std::cout << "        ---------------------------------------------" << std::endl;
}

void display_error_searched_contact_doesnt_exist(void) {
    std::cout << std::endl
         << KRED " Error:" << std::endl;
    std::cout << " • Contact does not exist" << KMAG << std::endl
         << std::endl;
    std::cout << " *********************************************************" << std::endl
         << std::endl;
}

void display_exit(void) {
    std::cout << std::endl << KMAG;
    std::cout << " *********************************************************" << std::endl << std::endl;
    std::cout << KBLU "         ------------------------------------------" << std::endl;
    std::cout << "         | Quit crappy_awesome_phonebook_software |" << std::endl;
    std::cout << "         ------------------------------------------" KMAG << std::endl << std::endl;
    std::cout << " *********************************************************" << std::endl;
}