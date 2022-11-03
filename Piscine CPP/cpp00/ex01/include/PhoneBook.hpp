#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include "utils.hpp"
#include <cstring>
#include <iostream>

#define MAX_CONTACTS 8

class PhoneBook {
public:
    PhoneBook();
    ~PhoneBook();

    void setContact(void);
    void getContact(unsigned int index) const;
    void searchContact(void) const;
    void phonebookDisplayContactColumns(void) const;

private:
    int _number_of_contacts;
    int _rows_to_print;
    Contact _phone_book_contacts[MAX_CONTACTS];
};

#endif