#pragma once

#include "ATarget.hpp"
#include <iostream>
#include <map>

class TargetGenerator {
private:
	std::map<std::string, ATarget*> targetPool;

	TargetGenerator(TargetGenerator const& other);
	TargetGenerator& operator=(TargetGenerator const& other);

public:
	TargetGenerator() {}
	~TargetGenerator() {
		std::map<std::string, ATarget*>::iterator it = targetPool.begin();
		for (; it != targetPool.end(); it++)
			delete it->second;
		targetPool.clear();
		}

	void learnTargetType(ATarget* targetToLearn) { if (targetToLearn) { targetPool.insert(std::pair<std::string, ATarget*>(targetToLearn->getType(), targetToLearn->clone())); } }

	void forgetTargetType(std::string const& targetToForget) {
		std::map<std::string, ATarget*>::iterator it = targetPool.find(targetToForget);
		if (it != targetPool.end())
			delete it->second;
		targetPool.erase(targetToForget);
	}

	ATarget* createTarget(std::string const& targetToCreate) {
		if (targetPool.find(targetToCreate) != targetPool.end())
			return targetPool[targetToCreate];
		return NULL;
	}
};