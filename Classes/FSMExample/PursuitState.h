#ifndef __PURSUIT_STATE_H__
#define __PURSUIT_STATE_H__

#include "FSM/BaseState.h"
#include "AIAttackNode.h"
class PursuitState :
    public BaseState
{
public:
	PursuitState(int stateId) : BaseState(stateId) {}
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif