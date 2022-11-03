#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "colors.hpp"

#include "AForm.hpp"
#include "Bureaucrat.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

class Bureaucrat;
class AForm;

class PresidentialPardonForm : public AForm {

private:
    std::string m_target;

public:
    PresidentialPardonForm(const std::string& target = "Default");
    PresidentialPardonForm(const PresidentialPardonForm& src);
    virtual ~PresidentialPardonForm();
    PresidentialPardonForm& operator=(const PresidentialPardonForm& rhs);

    void execute(Bureaucrat const& executor) const;
};

std::ostream& operator<<(std::ostream& out, const PresidentialPardonForm& presidentialpardonform);

#endif