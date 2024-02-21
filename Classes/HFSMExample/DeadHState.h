#ifndef __DEAD_HSTATE_H__
#define __DEAD_HSTATE_H__

#include "HFSM/HState.h"
#include "AIAttackNode.h"
class DeadHState :
    public HState
{
public:
	DeadHState(int stateId);
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif