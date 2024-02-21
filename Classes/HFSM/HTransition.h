#ifndef __HTRANSITION_H__
#define __HTRANSITION_H__

#include "AINode.h"
#include "AIEnum.h"

class HTransition
{
public:
	HTransition(int fromStateId, int toStateId);
	~HTransition();
	int getFromStateId() { return _fromStateId; }
	int getToStateId() { return _toStateId; }
	void addConditions(function<bool(AINode*, float timer)> condition);
	void setType(int type) { _transitionType = type; }
	bool checkChangeState(AINode* aiNode, float timer);
	int getWeight() const { return _weight; }
private:
	int _fromStateId;
	int _toStateId;
	int _trueNum;
	int _transitionType;
	int _weight;
	vector<function<bool(AINode*, float timer)>> _conditions;
};

#endif

