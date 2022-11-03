#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm("PresidentialPardonForm", 25, 5)
    , m_target(target) {
    std::cout << KYEL "PresidentialPardonForm::PresidentialPardonForm() [" << this->getName() << "] default constructor called" KNRM << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src)
    : AForm(src.getName(), src.getSignGrade(), src.getExecGrade()) {
    std::cout << KYEL "PresidentialPardonForm::PresidentialPardonForm() [" << this->getName() << "] copy constructor called" KNRM << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm() { std::cout << KYEL "PresidentialPardonForm::PresidentialPardonForm() [" << this->getName() << "] default destructor called" KNRM << std::endl; }

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& rhs) {

    if (this != &rhs)
        AForm::operator=(rhs);

    std::cout << KYEL "PresidentialPardonForm::PresidentialPardonForm() [" << this->getName() << "] copy assignment operator called" KNRM << std::endl;

    return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const& executor) const {
    if (this->getSigned() && (executor.getGrade() <= this->getExecGrade())) {
        std::cout << KBLU "PresidentialPardonForm::execute() [" << this->getName() << "]: [" << this->m_target << "] has been pardoned by Zaphod Beeblebrox" << std::endl;
    } else if (not(this->getSigned())) {
        throw FormNotSignedException();
    } else if (executor.getGrade() > this->getExecGrade()) {
        throw GradeTooLowException();
    }
}

std::ostream& operator<<(std::ostream& out, const PresidentialPardonForm& form) {
    out << KBLU "std::ostream& operator<< [" << form.getName() << "]: SignGrade: [" << form.getSignGrade() << "], "
        << "ExecGrade: [" << form.getExecGrade() << "], "
        << "Signature status: " << form.signStatus() << KNRM << std::endl;
    return out;
}