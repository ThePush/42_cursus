#include "ScavTrap.hpp"
#include "colors.hpp"

ScavTrap::ScavTrap(std::string const& name)
    : ClapTrap(name) {
    setHitPoints(100);
    setEnergyPoints(50);
    setAttackDamage(20);
    std::cout << KYEL "ScavTrap class: [" << this->m_name << "] default constructor called" KNRM << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& src)
    : ClapTrap() {
    m_name = src.m_name;
    m_hit_points = src.m_hit_points;
    m_energy_points = src.m_energy_points;
    m_attack_damage = src.m_attack_damage;
    std::cout << KYEL "ScavTrap class: Copy constructor called" KNRM << std::endl;
}

ScavTrap::~ScavTrap() {
    std::cout << KYEL "ScavTrap class: [" << m_name << "] Destructor called" KNRM << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& rhs) {

    if (this != &rhs) {
        this->m_name = rhs.m_name;
        this->m_hit_points = rhs.m_hit_points;
        this->m_energy_points = rhs.m_energy_points;
        this->m_attack_damage = rhs.m_attack_damage;
    }

    std::cout << KYEL "ScavTrap class: [" << m_name << "] Assignment operator called" KNRM << std::endl;

    return *this;
}

void ScavTrap::attack(const std::string& target) {
    if (this->m_energy_points > 0 and this->m_hit_points > 0) {
        this->m_energy_points--;
        std::cout << KBLU "ScavTrap.attack(): [" << this->m_name << "] tries to attack [" << target << "]: ...Success: [" << target << "] took [" << this->m_attack_damage << "] points of damage !" KNRM << std::endl;
    } else if (this->m_hit_points == 0) {
        std::cout << KRED "ScavTrap.attack(): [" << this->m_name << "] tries to attack [" << target << "]: ...no more hit points, attack failed" KNRM << std::endl;
    } else if (this->m_energy_points == 0) {
        std::cout << KRED "ScavTrap.attack(): [" << this->m_name << "] tries to attack [" << target << "]: ...no more energy, attack failed" KNRM << std::endl;
    }
}

void ScavTrap::guardGate(void) {
    std::cout << KCYN "ScavTrap.guardGate(): [" << this->m_name << "] switches to GateKeeper mode" KNRM << std::endl;
}
