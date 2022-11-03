#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137)
    , m_target(target) {
    std::cout << KYEL "ShrubberyCreationForm::ShrubberyCreationForm() [" << this->getName() << "] default constructor called" KNRM << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& src)
    : AForm(src.getName(), src.getSignGrade(), src.getExecGrade()) {
    std::cout << KYEL "ShrubberyCreationForm::ShrubberyCreationForm() [" << this->getName() << "] copy constructor called" KNRM << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm() { std::cout << KYEL "ShrubberyCreationForm::ShrubberyCreationForm() [" << this->getName() << "] default destructor called" KNRM << std::endl; }

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& rhs) {

    if (this != &rhs)
        AForm::operator=(rhs);

    std::cout << KYEL "ShrubberyCreationForm::ShrubberyCreationForm() [" << this->getName() << "] copy assignment operator called" KNRM << std::endl;

    return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
    if (this->getSigned() && (executor.getGrade() <= this->getExecGrade())) {
        std::cout << KBLU "ShrubberyCreationForm::execute() [" << this->getName() << "]: tries to draw a forest in [" << this->m_target << "_shrubbery]... " << std::endl;
        std::ofstream outfile;
        outfile.open((this->m_target + "_shrubbery").c_str(), std::ios::out);
        if (not(outfile.is_open())) {
            std::cout << KRED " Error:" << std::endl
                      << "  • Could not open/create output file [" << (this->m_target + "_shrubbery").c_str()
                      << "]" << KNRM << std::endl;

            return;
        }
        outfile << " .. ........... .............  ........... . ..... ........ ......." << std::endl;
        outfile << " ......  ....................%.... .... ..... .........%............" << std::endl;
        outfile << " .@@@ ........ @@.... @@@@  . ............................  *  ....." << std::endl;
        outfile << " ....@@ ..... @ .... @ .............   ....... .....; .... *** ....." << std::endl;
        outfile << " .....\\@\\....@ .... @ ............................. #  .. *****  ..." << std::endl;
        outfile << "  @@@.. @@@@@  @@@@@@___.. ....... ...%..... ...  {###}  *******" << std::endl;
        outfile << " ....@-@..@ ..@......@@@\\...... %...... ....... <## ####>********" << std::endl;
        outfile << "   @@@@\\...@ @ ........\\@@@@ ..... ...... ....... {###}***********" << std::endl;
        outfile << " ....%..@  @@ /@@@@@ . ....... ...............<###########> *******" << std::endl;
        outfile << " ...... .@-@@@@ ...V......     .... %.......... {#######}******* ***" << std::endl;
        outfile << " ...... .  @@ .. ..v.. .. . { } ............<###############>*******" << std::endl;
        outfile << " ......... @@ .... ........ {^^,     .......   {## ######}***** ****" << std::endl;
        outfile << " ..%..... @@ .. .%.... . .. (   `-;   ... <###################> ****" << std::endl;
        outfile << " . .... . @@ . .... .. _  .. `;;~~ ......... {#############}********" << std::endl;
        outfile << " .... ... @@ ... ..   /(______); .. ....<################  #####>***" << std::endl;
        outfile << " . .... ..@@@ ...... (         (  .........{##################}*****" << std::endl;
        outfile << " ......... @@@  ....  |:------( )  .. <##########################>**" << std::endl;
        outfile << "  @@@@ ....@@@  ... _// ...... \\ ...... {###   ##############}*****" << std::endl;
        outfile << " @@@@@@@  @@@@@ .. / /@@@@@@@@@ vv  <##############################>" << std::endl;
        outfile << " @@@@@@@ @@@@@@@ @@@@@@@@@@@@@@@@@@@ ..... @@@@@@  @@@@@@@  @@@@" << std::endl;
        outfile << " @@@@@@###@@@@@### @@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        outfile << " @@@@@@@@###@##@@ @@@@@@@@@@@@@@@@@@@@@ @@@@@   @@@@@@@@@@@@@@@@@@@" << std::endl;
        outfile << " @@@@@@@@@@@### @@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        outfile << " -@@@@@@@@@#####@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        outfile.close();
    } else if (not(this->getSigned())) {
        throw FormNotSignedException();
    } else if (executor.getGrade() > this->getExecGrade()) {
        throw GradeTooLowException();
    }
}

std::ostream& operator<<(std::ostream& out, const ShrubberyCreationForm& form) {
    out << KBLU "std::ostream& operator<< [" << form.getName() << "]: SignGrade: [" << form.getSignGrade() << "], "
        << "ExecGrade: [" << form.getExecGrade() << "], "
        << "Signature status: " << form.signStatus() << KNRM << std::endl;
    return out;
}