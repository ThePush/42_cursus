#include "DiamondTrap.hpp"
#include "colors.hpp"

DiamondTrap::DiamondTrap(std::string const& name)
    : ClapTrap(name + "_clap_name") {
    this->m_name = name;
    this->m_hit_points = FragTrap::m_hit_points;
    this->m_energy_points = ScavTrap::m_energy_points;
    this->m_attack_damage = FragTrap::m_attack_damage;
    std::cout << KYEL "DiamondTrap class: [" << m_name << "] default constructor called" KNRM << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& src)
    : ClapTrap()
    , ScavTrap()
    , FragTrap() {
    m_name = src.m_name;
    m_hit_points = src.m_hit_points;
    m_energy_points = src.m_energy_points;
    m_attack_damage = src.m_attack_damage;
    std::cout << KYEL "DiamondTrap class: [" << m_name << "] copy constructor called" KNRM << std::endl;
}

DiamondTrap::~DiamondTrap() {
    std::cout << KYEL "DiamondTrap class: [" << m_name << "] destructor called" KNRM << std::endl;
}

DiamondTrap& DiamondTrap::operator=(DiamondTrap const& rhs) {

    if (this != &rhs) {
        this->m_name = rhs.m_name;
        this->m_hit_points = rhs.m_hit_points;
        this->m_energy_points = rhs.m_energy_points;
        this->m_attack_damage = rhs.m_attack_damage;
    }

    std::cout << KYEL "DiamondTrap class: [" << m_name << "] copy assignment operator called" KNRM << std::endl;

    return *this;
}

void DiamondTrap::attack(const std::string& target) {
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI() {
    std::cout << KCYN "DiamondTrap.whoAmI(): DiamondTrap m_name is: [" << this->m_name << "]" << KNRM << std::endl;
    std::cout << KCYN "DiamondTrap.whoAmI(): subobject ClapTrap m_name is: [" << ClapTrap::getName() << "]" << KNRM << std::endl;
}