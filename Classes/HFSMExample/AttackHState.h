#ifndef __ATTACK_HSTATE_H__
#define __ATTACK_HSTATE_H__

#include "HFSM/HState.h"
#include "AIAttackNode.h"
class AttackHState :
    public HState
{
public:
	AttackHState(int stateId);
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif