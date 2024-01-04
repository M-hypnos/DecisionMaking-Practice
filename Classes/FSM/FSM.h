#ifndef __FSM_H__
#define __FSM_H__

#include<unordered_map>
#include "BaseState.h"
using namespace std;

class FSM
{
public:
	FSM();
	void onUpdate(float dt);
	void changeState(int stateId);
	void addState(BaseState* state);
	BaseState* removeState(int stateId);
	unordered_map<int, BaseState*> getAllStates() { return _allStates; }
	~FSM();
private:
	BaseState* _curState;
	BaseState* _lastState;
	unordered_map<int, BaseState*> _allStates;
};

#endif