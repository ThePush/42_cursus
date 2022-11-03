#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "colors.hpp"

#include <iostream>
#include <cstdlib>

void display_stats(FragTrap& claptrap) {
    std::cout << KMAG "[" << claptrap.getName() << "]'s HP: [" << claptrap.getHitPoints() << "]" KNRM << std::endl;
    std::cout << KMAG "[" << claptrap.getName() << "]'s EP: [" << claptrap.getEnergyPoints() << "]" KNRM << std::endl;
}

int main(void) {

    std::cout << KCYN "============================= [ TEST ] Default constructor =======================" << std::endl
              << std::endl;

    FragTrap clap_default;
    display_stats(clap_default);

    std::cout << std::endl
              << KCYN "============================= [ TEST ] Overloaded default constructor ============" << std::endl
              << std::endl;

    FragTrap clap_pikachu("Pikachu");
    display_stats(clap_pikachu);

    std::cout << std::endl
              << KCYN "============================= [ TEST ] Copy constructor ==========================" << std::endl
              << std::endl;

    FragTrap copykachu(clap_pikachu);
    display_stats(copykachu);

    std::cout << std::endl
              << KCYN "============================= [ TEST ] Assignment operator =======================" << std::endl
              << std::endl;

    FragTrap copyoperator("Copyoperator");
    display_stats(copyoperator);
    std::cout << KNRM << std::endl;
    copyoperator = copykachu;
    display_stats(copyoperator);

    std::cout << std::endl
              << KCYN "============================= [ TEST ] Member functions ==========================" << std::endl
              << std::endl;

    display_stats(clap_pikachu);
    clap_pikachu.attack("Roucool");
    display_stats(clap_pikachu);
    clap_pikachu.takeDamage(5);
    display_stats(clap_pikachu);
    clap_pikachu.beRepaired(5);
    display_stats(clap_pikachu);
    clap_pikachu.attack("Roucool");
    display_stats(clap_pikachu);
    clap_pikachu.takeDamage(15);
    display_stats(clap_pikachu);
    clap_pikachu.takeDamage(15);
    display_stats(clap_pikachu);
    clap_pikachu.attack("Roucool");
    display_stats(clap_pikachu);
    clap_pikachu.beRepaired(5);
    display_stats(clap_pikachu);
    clap_pikachu.highFivesGuys();

    return EXIT_SUCCESS;
}