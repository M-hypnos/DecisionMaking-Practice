#include "Transition.h"

bool Transition::checkChangeState(AINode* aiNode, float timer) {
	switch (_transitionType) {
		case TransitionType::AND:
			for (auto condition : _conditions) {
				if (!condition(aiNode, timer)) return false;
			}
			return true;
		case TransitionType::OR:
			for (auto condition : _conditions) {
				if (condition(aiNode, timer)) return true;
			}
			return false;
		case TransitionType::NUM:
		default:
			int num = 0;
			for (auto condition : _conditions) {
				if (condition(aiNode, timer)) num++;
			}
			return num >= _trueNum;
	}
}

void Transition::addConditions(function<bool(AINode*, float timer)> condition) {
	_conditions.push_back(condition);
}