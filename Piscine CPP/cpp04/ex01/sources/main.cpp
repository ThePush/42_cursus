#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "colors.hpp"
#include "utils.tpp"

#include <cstdlib>
#include <iostream>

int main() {

    std::cout << KCYN "============================= [ TEST ] Default constructor =======================" << std::endl
              << std::endl;

    Dog inu;
    inu.makeSound();

    std::cout << std::endl
              << KCYN "============================= [ TEST ] Copy constructor ==========================" << std::endl
              << std::endl;

    std::cout << KBLU << std::endl
              << "[ORIGINAL] Creation of a cat object and overwriting of its default idea with a new one:" KNRM << std::endl;

    Cat* cat = new Cat;
    std::cout << KBLU << std::endl
              << "[ORIGINAL] Print its ideas:" KNRM << std::endl;
    print_brain(*cat);
    std::cout << KBLU << std::endl
              << std::endl
              << "[ORIGINAL] Overwrite its default idea with a new one and print them:" KNRM << std::endl;
    cat->getBrain()->setIdeas(KRED "I HATE fish");
    print_brain(*cat);

    std::cout << KBLU << std::endl
              << std::endl
              << "[COPY] Creation of a copy with the copy constructor:" KNRM << std::endl;

    Cat* copycat = new Cat(*cat);

    std::cout << KBLU << std::endl
              << "[ORIGINAL] We delete the original cat object to be sure that we are not working on a pointer:" KNRM << std::endl;

    delete cat;

    std::cout << KBLU << std::endl
              << std::endl
              << "[COPY] Now we check if the copy is, indeed a deep copy, by printing its ideas, copied from the original object:" KNRM << std::endl;

    print_brain(*copycat);

    std::cout << KNRM << std::endl;

    std::cout << KBLU << std::endl
              << "[COPY] Call to copy's method makesound():" KNRM << std::endl;
    copycat->makeSound();

    std::cout << KNRM << std::endl;

    std::cout << KBLU << std::endl
              << "[COPY] We delete the copy object:" KNRM << std::endl;

    delete copycat;

    std::cout << std::endl
              << KCYN "============================= [ TEST ] Assignment operator =======================" << std::endl
              << std::endl;

    std::cout << KBLU << std::endl
              << "[ORIGINAL] Creation of a dog object and overwriting of its default idea with a new one:" KNRM << std::endl;

    Dog dog;
    dog.getBrain()->setIdeas(KRED "I HATE bones");

    std::cout << KBLU << std::endl
              << "[COPY] Declaration of a dog instance:" KNRM << std::endl;

    Dog copydog;

    std::cout << KBLU << std::endl
              << "[COPY] We print the copy default ideas:" KNRM << std::endl;

    print_brain(copydog);

    std::cout << KBLU << std::endl
              << std::endl
              << "[COPY] Use of '=' operator to copy:" KNRM << std::endl;

    copydog = dog;

    std::cout << KBLU << std::endl
              << "[COPY] Now we check if the copy is, indeed a deep copy, by printing its ideas, copied from the original object:" KNRM << std::endl;

    print_brain(copydog);

    std::cout << KNRM << std::endl;

    std::cout << KBLU << std::endl
              << "Call to copy's method makesound():" KNRM << std::endl;
    copydog.makeSound();

    std::cout << KNRM << std::endl;

    std::cout << std::endl;

    std::cout << std::endl
              << KCYN "============================= [ TEST ] Array of objects ==========================" << std::endl
              << std::endl;

    std::cout << KBLU "Creation of an array of 10 animals, half dogs and half cats, with a loop:" KNRM << std::endl;
    Animal* animal[10];

    for (int i(0); i != 5; ++i)
        animal[i] = new Dog;

    std::cout << std::endl;

    for (int i(5); i != 10; ++i)
        animal[i] = new Cat;

    std::cout << std::endl
              << KBLU "Now we delete it with a loop:" KNRM << std::endl;

    for (int i(0); i != 10; ++i)
        delete animal[i];

    std::cout << std::endl;

    return EXIT_SUCCESS;
}