#include "Form.hpp"

Form::Form(const std::string& name, const int& sign_grade, const int& exec_grade)
    : m_name(name)
    , m_sign_grade(sign_grade)
    , m_exec_grade(exec_grade)
    , m_is_signed(0) {
    std::cout << KYEL "Form::Form() [" << this->m_name << "] default constructor called" KNRM << std::endl;
    if (this->m_sign_grade < 1 or this->m_exec_grade < 1)
        throw GradeTooHighException();
    else if (this->m_sign_grade > 150 or this->m_exec_grade > 150)
        throw GradeTooLowException();
}

Form::~Form() { std::cout << KYEL "Form::Form() [" << this->m_name << "] default destructor called" KNRM << std::endl; }

Form::Form(const Form& src)
    : m_name(src.m_name)
    , m_sign_grade(src.m_sign_grade)
    , m_exec_grade(src.m_exec_grade)
    , m_is_signed(src.m_is_signed) {
    std::cout << KYEL "Form::Form() [" << this->m_name << "] copy constructor called" KNRM << std::endl;
}

Form& Form::operator=(const Form& rhs) {

    if (this != &rhs) {
        (std::string&)this->m_name = rhs.m_name;
        (int&)this->m_sign_grade = rhs.m_sign_grade;
        (int&)this->m_exec_grade = rhs.m_exec_grade;
        this->m_is_signed = rhs.m_is_signed;
    }

    std::cout << KYEL "Form::Form() [" << this->m_name << "] copy assignment operator called" KNRM << std::endl;

    return *this;
}

std::string Form::getName(void) const { return this->m_name; }
int Form::getSignGrade(void) const { return this->m_sign_grade; }
int Form::getExecGrade(void) const { return this->m_exec_grade; }

std::string Form::signStatus(void) const {
    if (this->m_is_signed)
        return (KGRN "[Signed ✓]" KNRM);
    else
        return (KRED "[Not signed ✗]" KNRM);
}

void Form::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() <= this->m_sign_grade)
        this->m_is_signed = 1;
    else
        throw GradeTooLowException();
}

const char* Form::GradeTooHighException::what() const throw() { return ("Form::GradeTooHighException() throw(): grade too high"); }
const char* Form::GradeTooLowException::what() const throw() { return ("Form::GradeTooLowException() throw(): grade too low"); }

std::ostream& operator<<(std::ostream& out, const Form& form) {
    out << KBLU "std::ostream& operator<< [" << form.getName() << "]: SignGrade: [" << form.getSignGrade() << "], "
        << "ExecGrade: [" << form.getExecGrade() << "], "
        << "Signature status: " << form.signStatus() << KNRM << std::endl;
    return out;
}