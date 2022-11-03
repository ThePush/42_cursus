#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap {
public:
    ClapTrap(std::string const& name = "Default");
    ClapTrap(const ClapTrap& src);
    virtual ~ClapTrap();
    ClapTrap& operator=(const ClapTrap& rhs);

    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
    int getHitPoints(void) const;
    int getEnergyPoints(void) const;
    int getAttackDamage(void) const;
    std::string getName(void) const;

    void setHitPoints(unsigned int const& hit_points);
    void setEnergyPoints(unsigned int const& energy_points);
    void setAttackDamage(unsigned int const& attack_damage);

protected:
    std::string m_name;
    unsigned int m_hit_points;
    unsigned int m_energy_points;
    unsigned int m_attack_damage;
};

#endif