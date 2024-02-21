#ifndef __PURSUIT_HSTATE_H__
#define __PURSUIT_HSTATE_H__

#include "HFSM/HState.h"
#include "AIAttackNode.h"
class PursuitHState :
    public HState
{
public:
	PursuitHState(int stateId);
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif