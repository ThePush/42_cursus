#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <cstring>
#include <iostream>

#define MAX_INFOS 5

class Contact {
public:
    Contact();
    ~Contact();

    bool setValues(unsigned int index);
    void displayContactInfos(void) const;
    bool checkContactExistence(void) const;
    void contactDisplayContactColumns(int index) const;

private:
    unsigned int _index;
    std::string _keys[MAX_INFOS];
    std::string _values[MAX_INFOS];
};

#endif