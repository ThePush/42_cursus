#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "colors.hpp"

#include "AForm.hpp"
#include "Bureaucrat.hpp"

#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

class Bureaucrat;
class AForm;

class RobotomyRequestForm : public AForm {

private:
    std::string m_target;

public:
    RobotomyRequestForm(const std::string& target = "Default");
    RobotomyRequestForm(const RobotomyRequestForm& src);
    virtual ~RobotomyRequestForm();
    RobotomyRequestForm& operator=(const RobotomyRequestForm& rhs);

    void execute(Bureaucrat const& executor) const;
};

std::ostream& operator<<(std::ostream& out, const RobotomyRequestForm& robotomyrequestform);

#endif