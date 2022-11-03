#include "Intern.hpp"
#include "AForm.hpp"
#include "colors.hpp"

Intern::Intern() { std::cout << KYEL "Intern::Intern() default constructor called" KNRM << std::endl; }

Intern::~Intern() { std::cout << KYEL "Intern::Intern() default destructor called" KNRM << std::endl; }

Intern::Intern(const Intern& src) {
    *this = src;
    std::cout << KYEL "Intern::Intern() copy constructor called" KNRM << std::endl;
}

Intern& Intern::operator=(const Intern& rhs) {

    (void)rhs;

    std::cout << KYEL "Intern::Intern() copy assignment operator called" KNRM << std::endl;

    return *this;
}

static AForm* createShrubberyCreationForm(const std::string& target) { return new ShrubberyCreationForm(target); }
static AForm* createRobotomyRequestForm(const std::string& target) { return new RobotomyRequestForm(target); }
static AForm* createPresidentialPardonForm(const std::string& target) { return new PresidentialPardonForm(target); }

AForm* Intern::makeForm(const std::string& form, const std::string& target) {
    std::string key[] = { "robotomy request", "shrubbery creation", "presidential pardon" };
    FuncPtr value[] = { createRobotomyRequestForm, createShrubberyCreationForm, createPresidentialPardonForm };
    for (int i(0); i != 3; ++i)
        if (not(key[i].compare(form))) {
            std::cout << KGRN "Intern::makeForm() called: Intern creates a [" << form << "] form ✓" KNRM << std::endl;
            AForm* created_form = value[i](target);
            return created_form;
        }
    throw FormNotFoundException();
}

const char* Intern::FormNotFoundException::what() const throw() { return "Intern::FormNotFoundException() throw(): form not found ✗"; }
