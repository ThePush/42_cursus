#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include "AForm.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

class AForm;
class Bureaucrat {
private:
    const std::string m_name;
    int m_grade;

public:
    Bureaucrat(const std::string& name = "Default", const int& grade = 150);
    Bureaucrat(const Bureaucrat& src);
    virtual ~Bureaucrat();
    Bureaucrat& operator=(const Bureaucrat& rhs);

    void raiseGrade(void);
    void lowerGrade(void);
    void signForm(AForm& form) const;
    void executeForm(AForm const& form);

    std::string getName(void) const;
    int getGrade(void) const;
    void setGrade(const int& grade);

    class GradeTooHighException
        : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowException
        : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat);

#endif