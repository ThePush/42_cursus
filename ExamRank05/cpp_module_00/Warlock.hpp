#pragma once

#include <iostream>

class Warlock {
private:
	std::string name;
	std::string title;

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
};