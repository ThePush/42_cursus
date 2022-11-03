#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", 72, 45)
    , m_target(target) {
    std::cout << KYEL "RobotomyRequestForm::RobotomyRequestForm() [" << this->getName() << "] default constructor called" KNRM << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& src)
    : AForm(src.getName(), src.getSignGrade(), src.getExecGrade()) {
    std::cout << KYEL "RobotomyRequestForm::RobotomyRequestForm() copy constructor called" KNRM << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm() { std::cout << KYEL "RobotomyRequestForm::RobotomyRequestForm() [" << this->getName() << "] default destructor called" KNRM << std::endl; }

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& rhs) {

    if (this != &rhs)
        AForm::operator=(rhs);

    std::cout << KYEL "RobotomyRequestForm::RobotomyRequestForm() copy assignment operator called" KNRM << std::endl;

    return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const& executor) const {
    if (this->getSigned() && (executor.getGrade() <= this->getExecGrade())) {
        srand(time(0));
        bool boolean = rand() % 2;
        std::cout << KBLU "RobotomyRequestForm::execute() [" << this->getName() << "]: *Drill Noises* attempting robotomy on [" << this->m_target << "]: ";
        if (boolean)
            std::cout << KGRN "...has been robotomized successfully" << std::endl;
        else
            std::cout << KRED "...robotomy failed" << std::endl;
    } else if (not(this->getSigned())) {
        throw FormNotSignedException();
    } else if (executor.getGrade() > this->getExecGrade()) {
        throw GradeTooLowException();
    }
}

std::ostream& operator<<(std::ostream& out, const RobotomyRequestForm& form) {
    out << KBLU "std::ostream& operator<< [" << form.getName() << "]: SignGrade: [" << form.getSignGrade() << "], "
        << "ExecGrade: [" << form.getExecGrade() << "], "
        << "Signature status: " << form.signStatus() << KNRM << std::endl;
    return out;
}