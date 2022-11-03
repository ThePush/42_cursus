#ifndef FORM_HPP
#define FORM_HPP

#include "colors.hpp"

#include "Bureaucrat.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

class Bureaucrat;

class Form {
private:
    const std::string m_name;
    const int m_sign_grade;
    const int m_exec_grade;
    bool m_is_signed;

public:
    Form(const std::string& name = "Form", const int& sign_grade = 150, const int& exec_grade = 150);
    Form(const Form& src);
    virtual ~Form();
    Form& operator=(const Form& rhs);

    std::string getName(void) const;
    int getSignGrade(void) const;
    int getExecGrade(void) const;
    std::string signStatus(void) const;

    void beSigned(const Bureaucrat& bureaucrat);

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

std::ostream& operator<<(std::ostream& out, const Form& form);

#endif