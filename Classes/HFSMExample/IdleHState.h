#ifndef __IDLE_HSTATE_H__
#define __IDLE_HSTATE_H__

#include "HFSM/HState.h"
#include "AIAttackNode.h"
class IdleHState :
    public HState
{
public:
	IdleHState(int stateId);
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif