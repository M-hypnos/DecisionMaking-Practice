#ifndef __BTPRECONDITION_H__
#define __BTPRECONDITION_H__

#include "AINode.h"
#include "AIEnum.h"

class BTPrecondition
{
public:
	BTPrecondition(): _conditionType (BTPreconditionType::BTAND), _trueNum(1) {}
	~BTPrecondition();
	void setType(int type) { _conditionType = type; }
	void addConditions(function<bool(AINode*)> condition);
	bool doEvaluate(AINode* aiNode);
private:
	int _trueNum;
	int _conditionType;
	vector<function<bool(AINode*)>> _conditions;
};

#endif

