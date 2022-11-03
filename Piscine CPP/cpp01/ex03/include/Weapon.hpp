#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <cstring>
#include <iostream>

class Weapon {
public:
    Weapon(std::string const& type = "Default");
    ~Weapon();

    std::string const getType(void) const;
    void setType(std::string const& newtype);

private:
    std::string _type;
};

#endif