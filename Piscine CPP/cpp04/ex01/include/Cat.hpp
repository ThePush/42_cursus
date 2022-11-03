#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
public:
    Cat();
    Cat(const Cat& src);
    virtual ~Cat();
    Cat& operator=(const Cat& rhs);

    Brain* getBrain(void) const;

    virtual void makeSound(void) const;

private:
    Brain* m_brain;
};

#endif