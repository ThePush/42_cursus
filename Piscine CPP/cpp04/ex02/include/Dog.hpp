#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
public:
    Dog();
    Dog(const Dog& src);
    virtual ~Dog();
    Dog& operator=(const Dog& rhs);

    Brain* getBrain(void) const;

    virtual void makeSound(void) const;

private:
    Brain* m_brain;
};

#endif