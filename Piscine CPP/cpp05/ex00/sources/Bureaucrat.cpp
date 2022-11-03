#include "Bureaucrat.hpp"
#include "colors.hpp"

Bureaucrat::Bureaucrat(const std::string& name, const int& grade)
    : m_name(name) {
    std::cout << KYEL "Bureaucrat::Bureaucrat() [" << this->m_name << "] default constructor called" KNRM << std::endl;
    if (grade < 1)
        throw GradeTooHighException();
    else if (grade > 150)
        throw GradeTooLowException();
    else
        this->m_grade = grade;
}

Bureaucrat::~Bureaucrat() { std::cout << KYEL "Bureaucrat::Bureaucrat() [" << this->m_name << "] default destructor called" KNRM << std::endl; }

Bureaucrat::Bureaucrat(const Bureaucrat& src)
    : m_name(src.m_name)
    , m_grade(src.m_grade) {
    std::cout << KYEL "Bureaucrat::Bureaucrat() [" << this->m_name << "] copy constructor called" KNRM << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& rhs) {

    if (this != &rhs) {
        (std::string&)this->m_name = rhs.m_name;
        this->m_grade = rhs.m_grade;
    }

    std::cout << KYEL "Bureaucrat::Bureaucrat() [" << this->m_name << "] copy assignment operator called" KNRM << std::endl;

    return *this;
}

void Bureaucrat::raiseGrade(void) {
    std::cout << KCYN "Bureaucrat::raiseGrade() [" << this->m_name << "] called" KNRM << std::endl;
    if (this->m_grade - 1 < 1)
        throw GradeTooHighException();
    else
        this->m_grade = m_grade - 1;
}

void Bureaucrat::lowerGrade(void) {
    std::cout << KCYN "Bureaucrat::lowerGrade() [" << this->m_name << "] called" KNRM << std::endl;
    if (this->m_grade + 1 > 150)
        throw GradeTooLowException();
    else
        this->m_grade = m_grade + 1;
}

std::string Bureaucrat::getName(void) const { return this->m_name; }
int Bureaucrat::getGrade(void) const { return this->m_grade; }

void Bureaucrat::setGrade(const int& grade) {
    if (grade > 150)
        throw GradeTooLowException();
    else if (grade < 1)
        throw GradeTooHighException();
    else
        this->m_grade = grade;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() { return ("Bureaucrat::GradeTooHighException() throw(): grade too high"); }
const char* Bureaucrat::GradeTooLowException::what() const throw() { return ("Bureaucrat::GradeTooLowException() throw(): grade too low"); }

std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat) {
    out << KBLU "std::ostream& operator<< [" << bureaucrat.getName() << "]: Grade: [" << bureaucrat.getGrade() << "]" KNRM << std::endl;
    return out;
}