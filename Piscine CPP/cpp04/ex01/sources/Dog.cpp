#include "Dog.hpp"
#include "colors.hpp"

Dog::Dog()
    : Animal() {
    std::cout << KYEL "Dog class: [" << this->m_type << "] default constructor called" KNRM << std::endl;
    this->m_brain = new Brain();
    this->m_brain->setIdeas(KGRN "I EAT bones" KNRM);
    this->m_type = "Dog";
}

Dog::Dog(const Dog& src)
    : Animal() {
    this->m_type = src.m_type;
    this->m_brain = new Brain(*src.m_brain);

    std::cout << KYEL "Dog class: [" << m_type << "] Copy constructor called" KNRM << std::endl;
}

Dog::~Dog() {
    delete this->m_brain;
    std::cout << KYEL "Dog class: [" << m_type << "] Destructor called" KNRM << std::endl;
}

Dog& Dog::operator=(const Dog& rhs) {

    if (this != &rhs) {
        this->m_type = rhs.m_type;
        for (int i(0); i != 100; ++i)
            this->m_brain->m_ideas[i] = rhs.getBrain()->m_ideas[i];
    }

    std::cout << KYEL "Dog class: [" << m_type << "] Assignment operator called" KNRM << std::endl;

    return *this;
}

void Dog::makeSound(void) const {
    std::cout << KGRN "Dog class: [" << m_type << "] makeSound() called: Bark" KNRM << std::endl;
}

Brain* Dog::getBrain(void) const {
    return m_brain;
}