#pragma once

#include "ASpell.hpp"
#include <iostream>
#include <map>

class SpellBook {
private:
	std::map<std::string, ASpell*> spellPool;

	SpellBook(SpellBook const& other);
	SpellBook& operator=(SpellBook const& other);

public:
	SpellBook() {}
	~SpellBook() {
		std::map<std::string, ASpell*>::iterator it = spellPool.begin();
		for (; it != spellPool.end(); it++)
			delete it->second;
		spellPool.clear();
		}

	void learnSpell(ASpell* spellToLearn) { if (spellToLearn) { spellPool.insert(std::pair<std::string, ASpell*>(spellToLearn->getName(), spellToLearn->clone())); } }

	void forgetSpell(std::string const& spellToForget) {
		std::map<std::string, ASpell*>::iterator it = spellPool.find(spellToForget);
		if (it != spellPool.end())
			delete it->second;
		spellPool.erase(spellToForget);
	}

	ASpell* createSpell(std::string const& spellToCreate) {
		if (spellPool.find(spellToCreate) != spellPool.end())
			return spellPool[spellToCreate];
		return NULL;
	}
};