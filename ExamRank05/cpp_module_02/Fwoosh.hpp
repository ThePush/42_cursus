#pragma once

#include "ASpell.hpp"
#include <iostream>

class Fwoosh : public ASpell{
public:
	Fwoosh() : ASpell("Fwoosh", "fwooshed") {}
	virtual ~Fwoosh() {}

	ASpell* clone() const { return new Fwoosh(); }
};