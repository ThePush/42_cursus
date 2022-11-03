#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "colors.hpp"

#include <cstdlib>
#include <iostream>

int main() {

    ShrubberyCreationForm Garden = ShrubberyCreationForm("Garden");
    std::cout << Garden << std::endl;
    RobotomyRequestForm Robotomy = RobotomyRequestForm("Robotomy");
    std::cout << Robotomy << std::endl;
    PresidentialPardonForm Pardon = PresidentialPardonForm("Pardon");
    std::cout << Pardon << std::endl;

    try {
        Bureaucrat HighLvl = Bureaucrat("Highlvl", 1);
        std::cout << HighLvl << std::endl;
        Bureaucrat LowLvl = Bureaucrat("Lowlvl", 150);
        std::cout << LowLvl << std::endl;
        LowLvl.signForm(Garden);
        HighLvl.executeForm(Garden);
        LowLvl.signForm(Robotomy);
        HighLvl.executeForm(Robotomy);
        LowLvl.signForm(Pardon);
        HighLvl.executeForm(Pardon);
        std::cout << std::endl;
        HighLvl.signForm(Garden);
        HighLvl.signForm(Robotomy);
        HighLvl.signForm(Pardon);
        std::cout << std::endl;
        std::cout << Garden;
        std::cout << Robotomy;
        std::cout << Pardon;
        std::cout << std::endl;
        LowLvl.executeForm(Garden);
        LowLvl.executeForm(Robotomy);
        LowLvl.executeForm(Pardon);
        std::cout << std::endl;
        HighLvl.executeForm(Garden);
        HighLvl.executeForm(Robotomy);
        HighLvl.executeForm(Pardon);
        std::cout << std::endl;
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}