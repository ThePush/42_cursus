#pragma once

#include "ASpell.hpp"
#include "SpellBook.hpp"
#include <iostream>
#include <map>

class Warlock {
private:
	std::string name;
	std::string title;
	SpellBook spellPool;

	Warlock() {}
	Warlock(Warlock const& other);
	Warlock& operator=(Warlock const& other);

public:
	Warlock(std::string const& name, std::string const& title) : name(name), title(title) { std::cout << name << ": This looks like another boring day.\n"; }
	~Warlock() { std::cout << name << ": My job here is done!\n"; }

	std::string const& getName() const { return name; }
	std::string const& getTitle() const { return title; }

	void setTitle(std::string const& title) { this->title = title; }

	void introduce() const { std::cout << name << ": I am " << name << ", " << title << "!\n"; }

	void learnSpell(ASpell* spellToLearn) { spellPool.learnSpell(spellToLearn); }

	void forgetSpell(std::string const& spellToForget) { spellPool.forgetSpell(spellToForget); }

	void launchSpell(std::string const& spellToLaunch, ATarget const& target) {
			ASpell* spell = spellPool.createSpell(spellToLaunch);
			if (spell)
				spell->launch(target);
	}
};