#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "colors.hpp"

#include "AForm.hpp"
#include "Bureaucrat.hpp"

#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

class Bureaucrat;
class AForm;

class ShrubberyCreationForm : public AForm {

private:
    std::string m_target;

public:
    ShrubberyCreationForm(const std::string& target = "Default");
    ShrubberyCreationForm(const ShrubberyCreationForm& src);
    virtual ~ShrubberyCreationForm();
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& rhs);

    void execute(Bureaucrat const& executor) const;
};

std::ostream& operator<<(std::ostream& out, const ShrubberyCreationForm& shrubberycreationform);

#endif