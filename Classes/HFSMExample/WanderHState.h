#ifndef __WANDER_HSTATE_H__
#define __WANDER_HSTATE_H__

#include "HFSM/HState.h"
#include "AIAttackNode.h"
class WanderHState :
    public HState
{
public:
	WanderHState(int stateId);
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif