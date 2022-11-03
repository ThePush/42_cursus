#include "AForm.hpp"

AForm::AForm(const std::string& name, const int& sign_grade, const int& exec_grade)
    : m_name(name)
    , m_sign_grade(sign_grade)
    , m_exec_grade(exec_grade)
    , m_is_signed(0) {
    std::cout << KYEL "AForm::AForm() [" << this->m_name << "] default constructor called" KNRM << std::endl;
    if (this->m_sign_grade < 1 or this->m_exec_grade < 1)
        throw GradeTooHighException();
    else if (this->m_sign_grade > 150 or this->m_exec_grade > 150)
        throw GradeTooLowException();
}

AForm::~AForm() { std::cout << KYEL "AForm::AForm() [" << this->m_name << "] default destructor called" KNRM << std::endl; }

AForm::AForm(const AForm& src)
    : m_name(src.m_name)
    , m_sign_grade(src.m_sign_grade)
    , m_exec_grade(src.m_exec_grade)
    , m_is_signed(src.m_is_signed) {
    std::cout << KYEL "AForm::AForm() [" << this->m_name << "] copy constructor called" KNRM << std::endl;
}

AForm& AForm::operator=(const AForm& rhs) {

    if (this != &rhs) {
        (std::string&)this->m_name = rhs.m_name;
        (int&)this->m_sign_grade = rhs.m_sign_grade;
        (int&)this->m_exec_grade = rhs.m_exec_grade;
        this->m_is_signed = rhs.m_is_signed;
    }

    std::cout << KYEL "AForm::AForm() [" << this->m_name << "] copy assignment operator called" KNRM << std::endl;

    return *this;
}

std::string AForm::getName(void) const { return this->m_name; }
int AForm::getSignGrade(void) const { return this->m_sign_grade; }
int AForm::getExecGrade(void) const { return this->m_exec_grade; }
bool AForm::getSigned(void) const { return this->m_is_signed; }

std::string AForm::signStatus(void) const {
    if (this->m_is_signed)
        return (KGRN "[Signed ✓]" KNRM);
    else
        return (KRED "[Not signed ✗]" KNRM);
}

void AForm::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() <= this->m_sign_grade)
        this->m_is_signed = 1;
    else
        throw GradeTooLowException();
}

const char* AForm::GradeTooHighException::what() const throw() { return ("AForm::GradeTooHighException() throw(): grade too high"); }
const char* AForm::GradeTooLowException::what() const throw() { return ("AForm::GradeTooLowException() throw(): grade too low"); }
const char* AForm::FormNotSignedException::what() const throw() { return ("AForm::FormNotsignedException() throw(): form not signed"); }

std::ostream& operator<<(std::ostream& out, const AForm& form) {
    out << KBLU "std::ostream& operator<< [" << form.getName() << "]: SignGrade: [" << form.getSignGrade() << "], "
        << "ExecGrade: [" << form.getExecGrade() << "], "
        << "Signature status: " << form.signStatus() << KNRM << std::endl;
    return out;
}