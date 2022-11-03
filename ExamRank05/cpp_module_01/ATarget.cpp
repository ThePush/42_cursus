#include "ATarget.hpp"

void ATarget::getHitBySpell(ASpell const& spell) const { std::cout << type << " has been " << spell.getEffects() << "!\n"; }