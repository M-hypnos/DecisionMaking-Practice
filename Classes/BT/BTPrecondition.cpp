#include "BTPrecondition.h"

BTPrecondition::BTPrecondition()
: _conditionType(BTPreconditionType::BTAND)
, _trueNum(1) 
{}

BTPrecondition::~BTPrecondition() {
	_conditions.clear();
}

bool BTPrecondition::doEvaluate(AINode* aiNode) {
	switch (_conditionType) {
		case BTPreconditionType::BTAND:
			for (auto condition : _conditions) {
				if (!condition(aiNode)) return false;
			}
			return true;
		case BTPreconditionType::BTOR:
			for (auto condition : _conditions) {
				if (condition(aiNode)) return true;
			}
			return false;
		case BTPreconditionType::BTNUM:
		default:
			int num = 0;
			for (auto condition : _conditions) {
				if (condition(aiNode)) num++;
			}
			return num >= _trueNum;
	}
}

void BTPrecondition::addConditions(function<bool(AINode*)> condition) {
	_conditions.push_back(condition);
}