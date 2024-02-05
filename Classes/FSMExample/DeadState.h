#ifndef __DEAD_STATE_H__
#define __DEAD_STATE_H__

#include "FSM/BaseState.h"
#include "AIAttackNode.h"
class DeadState :
    public BaseState
{
public:
	DeadState(int stateId) : BaseState(stateId) {}
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif