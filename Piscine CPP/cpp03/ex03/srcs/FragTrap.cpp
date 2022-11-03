#include "FragTrap.hpp"
#include "colors.hpp"

FragTrap::FragTrap(std::string const& name)
    : ClapTrap(name) {
    setHitPoints(100);
    setEnergyPoints(100);
    setAttackDamage(30);
    std::cout << KYEL "FragTrap class: [" << this->m_name << "] default constructor called" KNRM << std::endl;
}

FragTrap::FragTrap(const FragTrap& src)
    : ClapTrap() {
    m_name = src.m_name;
    m_hit_points = src.m_hit_points;
    m_energy_points = src.m_energy_points;
    m_attack_damage = src.m_attack_damage;
    std::cout << KYEL "FragTrap class copy constructor called" KNRM << std::endl;
}

FragTrap::~FragTrap() {
    std::cout << KYEL "FragTrap class: [" << m_name << "] destructor called" KNRM << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& rhs) {

    if (this != &rhs) {
        this->m_name = rhs.m_name;
        this->m_hit_points = rhs.m_hit_points;
        this->m_energy_points = rhs.m_energy_points;
        this->m_attack_damage = rhs.m_attack_damage;
    }

    std::cout << KYEL "FragTrap class: [" << m_name << "] copy assignment operator called" KNRM << std::endl;

    return *this;
}

void FragTrap::attack(const std::string& target) {
    if (this->m_energy_points > 0 and this->m_hit_points > 0) {
        this->m_energy_points--;
        std::cout << KBLU "FragTrap.attack(): [" << this->m_name << "] tries to attack [" << target << "]: ...Success: [" << target << "] took [" << this->m_attack_damage << "] points of damage !" KNRM << std::endl;
    } else if (this->m_hit_points == 0) {
        std::cout << KRED "FragTrap.attack(): [" << this->m_name << "] tries to attack [" << target << "]: ...no more hit points, attack failed" KNRM << std::endl;
    } else if (this->m_energy_points == 0) {
        std::cout << KRED "FragTrap.attack(): [" << this->m_name << "] tries to attack [" << target << "]: ...no more energy, attack failed" KNRM << std::endl;
    }
}

void FragTrap::highFivesGuys(void) {
    std::cout << KCYN "FragTrap.highFivesGuys(): [" << this->m_name << "] ...high five guys ?" KNRM << std::endl;
}
