#pragma once

#include "ASpell.hpp"
#include <iostream>
#include <map>

class Warlock {
private:
	std::string name;
	std::string title;
	std::map<std::string, ASpell*> spellPool;

	Warlock() {}
	Warlock(Warlock const& other);
	Warlock& operator=(Warlock const& other);

public:
	Warlock(std::string const& name, std::string const& title) : name(name), title(title) { std::cout << name << ": This looks like another boring day.\n"; }
	~Warlock() {
		std::cout << name << ": My job here is done!\n";
		std::map<std::string, ASpell*>::iterator it = spellPool.begin();
		for (; it != spellPool.end(); it++)
			delete it->second;
		spellPool.clear();
		}

	std::string const& getName() const { return name; }
	std::string const& getTitle() const { return title; }

	void setTitle(std::string const& title) { this->title = title; }

	void introduce() const { std::cout << name << ": I am " << name << ", " << title << "!\n"; }

	void learnSpell(ASpell* spellToLearn) { if (spellToLearn) { spellPool.insert(std::pair<std::string, ASpell*>(spellToLearn->getName(), spellToLearn->clone())); } }

	void forgetSpell(std::string const& spellToForget) {
		std::map<std::string, ASpell*>::iterator it = spellPool.find(spellToForget);
		if (it != spellPool.end())
			delete it->second;
		spellPool.erase(spellToForget);
	}

	void launchSpell(std::string const& spellToLaunch, ATarget const& target) {
		if (spellPool.find(spellToLaunch) != spellPool.end()) {
			ASpell* spell = spellPool[spellToLaunch];
			if (spell)
				spell->launch(target);
		}
	}
};