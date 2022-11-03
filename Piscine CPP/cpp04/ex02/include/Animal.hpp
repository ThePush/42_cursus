#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal {
public:
    Animal();
    Animal(Animal const& src);
    virtual ~Animal();

    Animal& operator=(Animal const& rhs);

    std::string getType(void) const;
    virtual void makeSound(void) const = 0;

protected:
    std::string m_type;
};

#endif