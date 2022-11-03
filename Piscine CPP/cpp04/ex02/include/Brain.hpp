#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain {
public:
    Brain();
    Brain(const Brain& src);
    ~Brain();

    Brain& operator=(const Brain& rhs);

    std::string const* getIdeas(void) const;
    void setIdeas(std::string const& idea);

    std::string m_ideas[100];
};

#endif