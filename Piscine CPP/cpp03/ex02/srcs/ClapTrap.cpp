#include "ClapTrap.hpp"
#include "colors.hpp"

ClapTrap::ClapTrap(std::string const& name)
    : m_name(name)
    , m_hit_points(10)
    , m_energy_points(10)
    , m_attack_damage(0) {
    std::cout << KYEL "ClapTrap class: [" << this->m_name << "] default constructor called" KNRM << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& src)
    : m_name(src.m_name)
    , m_hit_points(src.m_hit_points)
    , m_energy_points(src.m_energy_points)
    , m_attack_damage(src.m_attack_damage) {
    std::cout << KYEL "ClapTrap class: Copy constructor called" KNRM << std::endl;
}

ClapTrap::~ClapTrap() {
    std::cout << KYEL "ClapTrap class: [" << m_name << "] Destructor called" KNRM << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& rhs) {

    if (this != &rhs) {
        this->m_name = rhs.m_name;
        this->m_hit_points = rhs.m_hit_points;
        this->m_energy_points = rhs.m_energy_points;
        this->m_attack_damage = rhs.m_attack_damage;
    }

    std::cout << KYEL "ClapTrap class: [" << m_name << "] Assignment operator called" KNRM << std::endl;

    return *this;
}

void ClapTrap::attack(const std::string& target) {
    if (this->m_energy_points > 0 and this->m_hit_points > 0) {
        this->m_energy_points--;
        std::cout << KBLU "ClapTrap.attack(): [" << this->m_name << "] tries to attack [" << target << "]: ...Success: [" << target << "] took [" << this->m_attack_damage << "] points of damage !" KNRM << std::endl;
    } else if (this->m_hit_points == 0) {
        std::cout << KRED "ClapTrap.attack(): [" << this->m_name << "] tries to attack [" << target << "]: ...no more hit points, attack failed" KNRM << std::endl;
    } else if (this->m_energy_points == 0) {
        std::cout << KRED "ClapTrap.attack(): [" << this->m_name << "] tries to attack [" << target << "]: ...no more energy, attack failed" KNRM << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (this->m_hit_points > 0 and ((int)this->m_hit_points - (int)amount < 0)) {
        this->m_hit_points = 0;
        std::cout << KRED "ClapTrap.takeDamage(): [" << this->m_name << "] is attacked: [" << amount << "] HP lost !" << std::endl
                  << "[" << this->m_name << "] is KO !" KNRM << std::endl;
    } else if (this->m_hit_points > 0) {
        this->m_hit_points -= amount;
        std::cout << KRED "ClapTrap.takeDamage(): [" << this->m_name << "] is attacked: [" << amount << "] hit points lost !" KNRM << std::endl;
    } else {
        std::cout << KRED "ClapTrap.takeDamage(): [" << this->m_name << "] is attacked: ...but it is already KO !" KNRM << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (this->m_energy_points > 0 and this->m_hit_points) {
        this->m_hit_points += amount;
        this->m_energy_points--;
        std::cout << KGRN "Claptrap.beRepaired(): [" << this->m_name << "] tries to repair himself: ...Success: [+" << amount << "] hit points !" KNRM << std::endl;
    } else if (this->m_hit_points == 0) {
        std::cout << KRED "Claptrap.beRepaired(): [" << this->m_name << "] tries to repair himself: ...no more hit points, reparation failed" KNRM << std::endl;
    } else if (this->m_energy_points == 0) {
        std::cout << KRED "Claptrap.beRepaired(): [" << this->m_name << "] tries to repair himself: ...no more energy, reparation failed" KNRM << std::endl;
    }
}

int ClapTrap::getHitPoints(void) const { return this->m_hit_points; }
int ClapTrap::getEnergyPoints(void) const { return this->m_energy_points; }
int ClapTrap::getAttackDamage(void) const { return this->m_attack_damage; }
std::string ClapTrap::getName(void) const { return this->m_name; }
void ClapTrap::setHitPoints(unsigned int const& hit_points) { this->m_hit_points = hit_points; }
void ClapTrap::setEnergyPoints(unsigned int const& energy_points) { this->m_energy_points = energy_points; }
void ClapTrap::setAttackDamage(unsigned int const& attack_damage) { this->m_attack_damage = attack_damage; }
