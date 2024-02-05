#ifndef __ECLUDE_HSTATE_H__
#define __ECLUDE_HSTATE_H__

#include "HFSM/HState.h"
#include "AIAttackNode.h"
class EvadingHState :
    public HState
{
public:
	EvadingHState(int stateId) : HState(stateId) {}
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif