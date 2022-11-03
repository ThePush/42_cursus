#include "Contact.hpp"
#include "display.hpp"
#include "utils.hpp"
#include <cstdlib>

Contact::Contact() {
    this->_index = 0;
    this->_keys[0] = "first name";
    this->_keys[1] = "last name";
    this->_keys[2] = "nickname";
    this->_keys[3] = "phone number";
    this->_keys[4] = "darkest secret";
}

Contact::~Contact() {
}

bool Contact::checkContactExistence(void) const {
    for (int i(0); i != MAX_INFOS; ++i)
        if (this->_values[i].empty())
            return (false);
    return (true);
}

/**
 * It takes an index as a parameter, displays a message to the user, then asks the user to enter a
 * value for each of the contact's fields. If the user enters an empty string, a string with spaces, a
 * string that contains non-alphanumeric characters, or a string that contains non-numeric characters
 * for the phone number, the function displays an error message and returns false. Otherwise, it
 * displays a success message and returns true
 * 
 * @param index the index of the contact in the phonebook
 * 
 * @return A boolean value.
 */
bool Contact::setValues(unsigned int index) {

    if (std::cin.eof()) {
        display_exit();
        exit(EXIT_SUCCESS);
    }

    this->_index = index;

    display_add_contact();

    for (int i(0); i != MAX_INFOS; ++i) {
        std::cout << KBLU << " • Enter contact's " << this->_keys[i] << ": " << KWHT;
        std::getline(std::cin, this->_values[i]);
        if (std::cin.eof()) {
            display_exit();
            exit(EXIT_SUCCESS);
        }
        if (this->_values[i].empty()
            or str_has_space(this->_values[i])
            or not(str_isalnum(this->_values[i]))
            or (i == 3 and not(str_isdigit(this->_values[i])))) {
            display_error_add_contact();
            return false;
        }
    }

    display_contact_added_successfully(_index);

    return true;
}

/**
 * It displays the contact's information in a table format
 * 
 * @param index the index of the contact in the phonebook
 */
void Contact::contactDisplayContactColumns(int index) const {
    std::cout << "        |";
    std::cout << std::setw(10) << index << "|";

    for (int column(0); column != 3; ++column) {
        if (this->_values[column].length() > 10)
            std::cout << this->_values[column].substr(0, 9) << ".";
        else
            std::cout << std::setw(10) << this->_values[column];
        std::cout << "|";
    }

    std::cout << std::endl;
    std::cout << "        ---------------------------------------------" << std::endl;
}

void Contact::displayContactInfos(void) const {
    std::cout << std::endl;

    for (int i(0); i != MAX_INFOS; ++i)
        std::cout << "      • " << this->_keys[i] << ": " << this->_values[i] << std::endl;

    std::cout << std::endl
              << KMAG
              << " *********************************************************" << std::endl;
}