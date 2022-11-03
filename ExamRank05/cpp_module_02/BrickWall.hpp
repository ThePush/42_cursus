#pragma once

#include "ATarget.hpp"
#include <iostream>

class BrickWall : public ATarget{
public:
	BrickWall() : ATarget("Inconspicuous Red-brick Wall") {}
	virtual ~BrickWall() {}

	ATarget* clone() const { return new BrickWall(); }
};