#pragma once

#include "ASpell.hpp"
#include <iostream>

class ASpell;

class ATarget {
protected:
	std::string type;

public:
	ATarget() {}
	ATarget(ATarget const& other) : type(other.getType()) {}
	ATarget& operator=(ATarget const& other) { if (this != &other) { type = other.getType(); } return *this; }
	ATarget(std::string const& type) : type(type) {}
	virtual ~ATarget() {}

	std::string const& getType() const { return type; }

	virtual ATarget* clone() const = 0;

	void getHitBySpell(ASpell const& spell) const;

};