#ifndef AFORM_HPP
#define AFORM_HPP

#include "colors.hpp"

#include "Bureaucrat.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

class Bureaucrat;

class AForm {
private:
    const std::string m_name;
    const int m_sign_grade;
    const int m_exec_grade;
    bool m_is_signed;

public:
    AForm(const std::string& name = "AForm", const int& sign_grade = 150, const int& exec_grade = 150);
    AForm(const AForm& src);
    virtual ~AForm();
    AForm& operator=(const AForm& rhs);

    std::string getName(void) const;
    int getSignGrade(void) const;
    int getExecGrade(void) const;
    bool getSigned(void) const;
    std::string signStatus(void) const;

    void beSigned(const Bureaucrat& bureaucrat);

    virtual void execute(Bureaucrat const& executor) const = 0;

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

    class FormNotSignedException
        : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& out, const AForm& form);

#endif