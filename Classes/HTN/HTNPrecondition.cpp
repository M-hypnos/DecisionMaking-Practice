#include "HTNPrecondition.h"

HTNPrecondition::HTNPrecondition()
	: _conditionType(HTNPreconditionType::HTNAND)
	, _trueNum(1)
{}

HTNPrecondition::~HTNPrecondition() {
	_conditions.clear();
}

bool HTNPrecondition::check(const unique_ptr<HTNWorldState>& worldState) {
	switch (_conditionType) {
	case HTNPreconditionType::HTNAND:
		for (auto condition : _conditions) {
			if (!condition(worldState)) return false;
		}
		return true;
	case HTNPreconditionType::HTNOR:
		for (auto condition : _conditions) {
			if (condition(worldState)) return true;
		}
		return false;
	case HTNPreconditionType::HTNNUM:
	default:
		int num = 0;
		for (auto condition : _conditions) {
			if (condition(worldState)) num++;
		}
		return num >= _trueNum;
	}
}