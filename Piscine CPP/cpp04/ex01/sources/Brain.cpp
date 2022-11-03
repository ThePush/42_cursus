#include "Brain.hpp"
#include "colors.hpp"

Brain::Brain() {
    for (int i(0); i != 100; ++i)
        m_ideas[i] = '\0';
    std::cout << KYEL "Brain class default constructor called" KNRM << std::endl;
}

Brain::Brain(const Brain& src) {
    for (int i(0); i != 100; ++i)
        m_ideas[i] = '\0';

    for (int i(0); i != 100; ++i)
        this->m_ideas[i] = src.m_ideas[i];

    std::cout << KYEL "Brain class copy constructor called" KNRM << std::endl;
}

Brain::~Brain() {
    std::cout << KYEL "Brain class destructor called" KNRM << std::endl;
}

Brain& Brain::operator=(const Brain& rhs) {

    if (this != &rhs)
        for (int i(0); i != 100; ++i)
            this->m_ideas[i] = rhs.m_ideas[i];

    std::cout << "Brain class copy assignment operator called" << std::endl;

    return *this;
}

void Brain::setIdeas(std::string const& idea) {
    for (int i(0); i != 100; ++i)
        this->m_ideas[i] = idea;
}

std::string const* Brain::getIdeas(void) const {
    return this->m_ideas;
}