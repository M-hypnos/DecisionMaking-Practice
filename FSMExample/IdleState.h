#ifndef __IDLE_STATE_H__
#define __IDLE_STATE_H__

#include "FSM/BaseState.h"
#include "AIAttackNode.h"
class IdleState :
    public BaseState
{
public:
	IdleState(int stateId) : BaseState(stateId) {}
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif