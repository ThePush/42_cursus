#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "colors.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>

int main() {

    std::cout << KCYN "============================= [ TEST ] Bureaucrat Copy  constructor ==================================" << std::endl
              << std::endl;
    Bureaucrat* bureaucrat = new Bureaucrat("Bureaucrat");
    Bureaucrat* copybureaucrat = new Bureaucrat(*bureaucrat);
    std::cout << KBLU "Original: " << *bureaucrat;
    std::cout << KBLU "Copy: " << *copybureaucrat;

    delete bureaucrat;
    delete copybureaucrat;

    std::cout << std::endl;

    std::cout << KCYN "============================= [ TEST ] Form constructors and assignment operator =====================" << std::endl
              << std::endl;
    Form* form = new Form("PanamaPapers");
    Form* copyform = new Form(*form);
    Form* assigned = new Form;
    *assigned = *copyform;
    std::cout << KBLU "Original: " << *form;
    std::cout << KBLU "Copy: " << *copyform;
    std::cout << KBLU "Assignment copy: " << *assigned;

    delete form;
    delete copyform;
    delete assigned;

    std::cout << std::endl;

    std::cout << KCYN "============================= [ TEST ] Exceptions and relations between classes =====================" << std::endl
              << std::endl;

    try {
        std::cout << KMAG "---- Declaration of a Form of grades 1, 1 ----" << std::endl
                  << std::endl;
        //std::auto_ptr<Form> form(new Form("PanamaPapers", 1, 1));
         Form* form = new Form("PanamaPapers", 1, 1);
        std::cout << *form;
        try {
            std::cout << std::endl
                      << KMAG "---- Declaration of a Bureaucrat of grade 4 ----" << std::endl
                      << std::endl;
            //std::auto_ptr<Bureaucrat> maggot(new Bureaucrat("Maggot", 4));
             Bureaucrat* maggot = new Bureaucrat("Maggot", 4);
            std::cout << *maggot;
            std::cout << std::endl
                      << KMAG "---- Our bureaucrat tries to sign the form ----" << std::endl
                      << std::endl;
            maggot->signForm(*form); // signature will fail if maggot is low level
            std::cout << *form;
            std::cout << std::endl;
            std::cout << std::endl
                      << KMAG "---- Let's raise bureaucrat's level to the required form level ----" << std::endl
                      << std::endl;
            for (int i(maggot->getGrade()); i != form->getSignGrade(); --i) {
                maggot->raiseGrade();
                std::cout << *maggot;
                maggot->signForm(*form);
                std::cout << *form;
            }
             delete form;
             delete maggot;
        } catch (std::exception const& e) {
            std::cerr << KRED << e.what() << KNRM << std::endl;
             delete form;
            return EXIT_FAILURE;
        }
    } catch (std::exception const& e) {
        std::cerr << KRED << e.what() << KNRM << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}