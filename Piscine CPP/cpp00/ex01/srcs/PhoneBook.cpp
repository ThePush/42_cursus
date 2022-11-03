#include "PhoneBook.hpp"
#include "display.hpp"
#include "utils.hpp"
#include <cstdlib>

PhoneBook::PhoneBook()
    : _number_of_contacts(0)
    , _rows_to_print(0) {
}

PhoneBook::~PhoneBook() {
}

void PhoneBook::setContact(void) {

    unsigned int index = this->_number_of_contacts;

    if (index >= MAX_CONTACTS) {
        index = 0;
        this->_number_of_contacts = 0;
    }
    if (this->_phone_book_contacts[index].setValues(index)) {
        this->_number_of_contacts++;
        if (this->_rows_to_print < MAX_CONTACTS)
            this->_rows_to_print++;
    }
}

void PhoneBook::getContact(unsigned int index) const {

    if (this->_phone_book_contacts[index].checkContactExistence()) {
        std::cout << std::endl
                  << KBLU "   • Contact [" << index << "] informations:" << std::endl;
        this->_phone_book_contacts[index].displayContactInfos();
        std::cout << std::endl;
    } else
        display_error_searched_contact_doesnt_exist();
}

void PhoneBook::phonebookDisplayContactColumns(void) const {
    for (int index(0); index < this->_rows_to_print; index++) {
        this->_phone_book_contacts[index].contactDisplayContactColumns(index);
    }
}

void PhoneBook::searchContact(void) const {

    int index;
    std::string prompt;

    if (std::cin.eof()) {
        display_exit();
        exit(EXIT_SUCCESS);
    }

    display_search();

    if (this->_phone_book_contacts[0].checkContactExistence()) {
        display_columns();
        phonebookDisplayContactColumns();
        display_search_prompt();

        getline(std::cin, prompt);
        if (std::cin.eof()) {
            display_exit();
            exit(EXIT_SUCCESS);
        }
        index = std::atoi(prompt.c_str());
        if (not(prompt.empty()) and (prompt.length() < 2) and str_isdigit(prompt) and index >= 0 and index <= MAX_CONTACTS - 1)
            getContact(index);
        else
            display_error_searched_index();
    } else
        display_no_contact_created_yet();
}
