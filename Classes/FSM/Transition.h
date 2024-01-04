#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include "AINode.h"

enum TransitionType
{
	AND,
	OR,
	NUM
};

class Transition
{
public:
	Transition(int toStateId):_toStateId(toStateId), _transitionType(TransitionType::AND),_trueNum(1){}
	int getToStateId() { return _toStateId; }
	void addConditions(function<bool(AINode*, float timer)> condition);
	void setType(int type) { _transitionType = type; }
	bool checkChangeState(AINode* aiNode, float timer);
private:
	int _toStateId;
	int _trueNum;
	int _transitionType;
	vector<function<bool(AINode*, float timer)>> _conditions;
};

#endif

