#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>

class Intern {
private:
    typedef AForm* (*FuncPtr)(const std::string& target);

public:
    Intern();
    Intern(const Intern& src);
    virtual ~Intern();
    Intern& operator=(const Intern& rhs);

    AForm* makeForm(const std::string& form, const std::string& target);

    class FormNotFoundException
        : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& out, const Intern& intern);

#endif