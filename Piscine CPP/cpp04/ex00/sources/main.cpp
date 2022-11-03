#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "colors.hpp"

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

    Dog copyinu(inu);
    copyinu.makeSound();

    std::cout << std::endl
              << KCYN "============================= [ TEST ] Assignment operator =======================" << std::endl
              << std::endl;

    Dog copyoperator;
    copyoperator = copyinu;
    copyoperator.makeSound();

    std::cout << std::endl
              << KCYN "============================= [ TEST ] Member functions ==========================" << std::endl
              << std::endl;

    const Animal* animal = new Animal();
    std::cout << std::endl;
    const Animal* dog = new Dog();
    std::cout << std::endl;
    const Animal* cat = new Cat();
    std::cout << std::endl;
    std::cout << KBLU "Animal m_type: " << animal->getType() << KNRM << std::endl;
    std::cout << KBLU "Dog m_type: " << dog->getType() << KNRM << std::endl;
    std::cout << KBLU "Cat m_type: " << cat->getType() << KNRM << std::endl;
    std::cout << std::endl;
    animal->makeSound(); // will output the animal sound
    dog->makeSound(); // will output the dog sound
    cat->makeSound(); // wil output the cat soung

    std::cout << std::endl;

    const WrongAnimal* wronganimal = new WrongAnimal();
    std::cout << std::endl;
    const WrongAnimal* wrongcat = new WrongCat();
    std::cout << std::endl;
    std::cout << KBLU "Wronganimal m_type: " << wronganimal->getType() << KNRM << std::endl;
    std::cout << KBLU "Wrongcat m_type: " << wrongcat->getType() << KNRM << std::endl;
    wronganimal->makeSound(); // will output the wronganimal sound
    wrongcat->makeSound(); // will output the wronganimal sound
    std::cout << std::endl;
    WrongCat wrongcatto;
    wrongcatto.makeSound(); // will output the wrongcat sound

    std::cout << std::endl;
    delete animal;
    std::cout << std::endl;
    delete cat;
    std::cout << std::endl;
    delete dog;
    std::cout << std::endl;
    delete wronganimal;
    std::cout << std::endl;
    delete wrongcat;
    std::cout << std::endl;

    return EXIT_SUCCESS;
}