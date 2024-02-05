#ifndef __ECLUDE_STATE_H__
#define __ECLUDE_STATE_H__

#include "FSM/BaseState.h"
#include "AIAttackNode.h"
class EvadingState :
    public BaseState
{
public:
	EvadingState(int stateId) : BaseState(stateId) {}
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif