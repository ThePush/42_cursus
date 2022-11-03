#include "Bureaucrat.hpp"
#include "colors.hpp"

#include <cstdlib>
#include <iostream>

int main(void) {

    std::cout << KMAG "================= [ TEST ] Constructors and assignment operator =============" KNRM << std::endl
              << std::endl;
    Bureaucrat* bureaucrat1 = new Bureaucrat("Bureaucrat", 140);
    Bureaucrat* maggot = new Bureaucrat(*bureaucrat1);
    Bureaucrat* peon = new Bureaucrat;
    *peon = *bureaucrat1;
    std::cout << KBLU "Original: " << *bureaucrat1;
    std::cout << KBLU "Copy: " << *maggot;
    std::cout << KBLU "Assignment Copy: " << *peon;

    delete bureaucrat1;
    delete maggot;
    delete peon;

    std::cout << std::endl;

    std::cout << KMAG "================= [ TEST ] Exception in member function raise() =============" KNRM << std::endl
              << std::endl;
    Bureaucrat* bureaucrat = new Bureaucrat("Bureaucrat");

    std::cout << std::endl
              << KMAG "Set a bureaucrat to grade 2:" KNRM << std::endl;

    try {
        bureaucrat->setGrade(2);
        std::cout << *bureaucrat;
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    std::cout << std::endl
              << KMAG "Try to raise its grade:" KNRM << std::endl;

    try {
        bureaucrat->raiseGrade();
        std::cout << *bureaucrat;
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    std::cout << std::endl
              << KMAG "Try to raise its grade again:" KNRM << std::endl;

    try {
        bureaucrat->raiseGrade();
        std::cout << *bureaucrat;
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    std::cout << std::endl
              << KMAG "================= [ TEST ] Exception in member function lower() =============" KNRM << std::endl
              << std::endl;

    std::cout << KMAG "Set our bureaucrat grade to 149:" KNRM << std::endl;

    try {
        bureaucrat->setGrade(149);
        std::cout << *bureaucrat;
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    std::cout << std::endl
              << KMAG "Try to lower its grade:" KNRM << std::endl;

    try {
        bureaucrat->lowerGrade();
        std::cout << *bureaucrat;
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    std::cout << std::endl
              << KMAG "Try to lower its grade again:" KNRM << std::endl;

    try {
        bureaucrat->lowerGrade();
        std::cout << *bureaucrat;
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    delete bureaucrat;

    std::cout << std::endl
              << KMAG "===================== [ TEST ] Exception in constructor =====================" KNRM << std::endl
              << std::endl;

    std::cout << KMAG "Try to create a bureaucrat with a grade of -155:" KNRM << std::endl;

    try {
        Bureaucrat* maggot = new Bureaucrat("Maggot", -155);
        std::cout << *maggot;
        delete maggot;
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    std::cout << std::endl
              << KMAG "Try to create a bureaucrat with a grade of 155:" KNRM << std::endl;

    try {
        Bureaucrat* maggot = new Bureaucrat("Maggot", 155);
        std::cout << *maggot;
        delete maggot;
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
    }

    return EXIT_SUCCESS;
}
