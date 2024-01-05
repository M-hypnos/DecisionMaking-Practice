#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include "AINode.h"
#include "AIEnum.h"

class Transition
{
public:
	Transition(int toStateId):_toStateId(toStateId), _transitionType(TransitionType::AND),_trueNum(1), _weight(0){}
	int getToStateId() { return _toStateId; }
	void addConditions(function<bool(AINode*, float timer)> condition);
	void setType(int type) { _transitionType = type; }
	bool checkChangeState(AINode* aiNode, float timer);
	int getWeight() const { return _weight; }
private:
	int _toStateId;
	int _trueNum;
	int _transitionType;
	int _weight;
	vector<function<bool(AINode*, float timer)>> _conditions;
};

#endif

