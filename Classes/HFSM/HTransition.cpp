#include "HTransition.h"

HTransition::~HTransition() {
	_conditions.clear();
}

bool HTransition::checkChangeState(AINode* aiNode, float timer) {
	switch (_transitionType) {
		case HTransitionType::HAND:
			for (auto condition : _conditions) {
				if (!condition(aiNode, timer)) return false;
			}
			return true;
		case HTransitionType::HOR:
			for (auto condition : _conditions) {
				if (condition(aiNode, timer)) return true;
			}
			return false;
		case HTransitionType::HNUM:
		default:
			int num = 0;
			for (auto condition : _conditions) {
				if (condition(aiNode, timer)) num++;
			}
			return num >= _trueNum;
	}
}

void HTransition::addConditions(function<bool(AINode*, float timer)> condition) {
	_conditions.push_back(condition);
}