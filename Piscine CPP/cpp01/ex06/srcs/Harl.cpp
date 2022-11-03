#include "Harl.hpp"
#include "colors.hpp"
#include "utils.hpp"

Harl::Harl() {
}

Harl::~Harl() {
}

void Harl::debug(void) {
    std::cout << KGRN "[ DEBUG ]" << std::endl
              << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" KNRM << std::endl
              << std::endl;
}

void Harl::info(void) {
    std::cout << KCYN "[ INFO ]" << std::endl
              << "I cannot believe adding extra bacon costs more money. You did not put enough bacon in my burger! If you did, I would not be asking for more!" KNRM << std::endl
              << std::endl;
}

void Harl::warning(void) {
    std::cout << KYEL "[ WARNING ]" << std::endl
              << "I think I deserve to have some extra bacon for free. I have been coming for years whereas you started working here since last month." KNRM << std::endl
              << std::endl;
}

void Harl::error(void) {
    std::cout << KRED "[ ERROR ]" << std::endl
              << "This is unacceptable! I want to speak to the manager now." KNRM << std::endl
              << std::endl;
}

void Harl::complain(const std::string& level) {

    std::string key[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    int index = get_index(key, level);

    switch (index) {

    case 0:
        debug();
    case 1:
        info();
    case 2:
        warning();
    case 3:
        error();
        break;
    default:
        std::cout << KMAG "[ Probably complaining about insignificant problems ]" KNRM << std::endl
                  << std::endl;
    }
}