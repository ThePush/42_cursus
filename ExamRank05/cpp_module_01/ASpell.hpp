#pragma once

#include "ATarget.hpp"
#include <iostream>

class ATarget;

class ASpell {
protected:
	std::string name;
	std::string effects;

public:
	ASpell() {}
	ASpell(ASpell const& other) : name(other.getName()), effects(other.getEffects()) {}
	ASpell& operator=(ASpell const& other) { if (this != &other) { name = other.getName(); effects = other.getEffects(); } return *this; }
	ASpell(std::string const& name, std::string const& effects) : name(name), effects(effects) {}
	virtual ~ASpell() {}

	std::string const& getName() const { return name; }
	std::string const& getEffects() const { return effects; }

	virtual ASpell* clone() const = 0;

	void launch(ATarget const& target) const;

};