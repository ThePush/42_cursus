#include "Cat.hpp"
#include "colors.hpp"

Cat::Cat()
    : Animal() {
    std::cout << KYEL "Cat class: [" << this->m_type << "] default constructor called" KNRM << std::endl;
    this->m_brain = new Brain();
    this->m_brain->setIdeas(KGRN "I EAT fish" KNRM);
    this->m_type = "Cat";
}

Cat::Cat(const Cat& src)
    : Animal() {
    this->m_type = src.m_type;
    this->m_brain = new Brain(*src.m_brain);

    std::cout << KYEL "Cat class: [" << m_type << "] Copy constructor called" KNRM << std::endl;
}

Cat::~Cat() {
    delete this->m_brain;
    std::cout << KYEL "Cat class: [" << m_type << "] Destructor called" KNRM << std::endl;
}

Cat& Cat::operator=(const Cat& rhs) {

    if (this != &rhs) {
        this->m_type = rhs.m_type;
        for (int i(0); i != 100; ++i)
            this->m_brain->m_ideas[i] = rhs.getBrain()->m_ideas[i];
    }

    std::cout << KYEL "Cat class: [" << m_type << "] Assignment operator called" KNRM << std::endl;

    return *this;
}

void Cat::makeSound(void) const {
    std::cout << KGRN "Cat class: [" << m_type << "] makeSound() called: Meow" KNRM << std::endl;
}

Brain* Cat::getBrain(void) const {
    return m_brain;
}