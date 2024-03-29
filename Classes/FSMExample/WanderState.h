#ifndef __WANDER_STATE_H__
#define __WANDER_STATE_H__

#include "FSM/BaseState.h"
#include "AIAttackNode.h"
class WanderState :
    public BaseState
{
public:
	WanderState(int stateId);
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif