#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "colors.hpp"

#include <cstdlib>
#include <iostream>

int main() {

    try {
        Bureaucrat bureaucrat = Bureaucrat("Bureaucrat", 1);
        Intern someRandomIntern;
        AForm *rrf, *rrf2, *rrf3, *rrf4;
        std::cout << std::endl;
        try {
            rrf = someRandomIntern.makeForm("robotomy request", "Bender");
            bureaucrat.signForm(*rrf);
            bureaucrat.executeForm(*rrf);
            delete rrf;
            std::cout << std::endl;
            rrf2 = someRandomIntern.makeForm("shrubbery creation", "Bender");
            bureaucrat.signForm(*rrf2);
            bureaucrat.executeForm(*rrf2);
            delete rrf2;
            std::cout << std::endl;
            rrf3 = someRandomIntern.makeForm("presidential pardon", "Bender");
            bureaucrat.signForm(*rrf3);
            bureaucrat.executeForm(*rrf3);
            delete rrf3;
            std::cout << std::endl;
            rrf4 = someRandomIntern.makeForm("fail", "Bender");
            bureaucrat.signForm(*rrf4);
            bureaucrat.executeForm(*rrf4);
            delete rrf4;
            std::cout << std::endl;
        } catch (std::exception const& e) {
            std::cerr << KRED << e.what() << KNRM << std::endl;
            return EXIT_FAILURE;
        }
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}