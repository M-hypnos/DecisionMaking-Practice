#ifndef __ATTACK_HSTATE_H__
#define __ATTACK_HSTATE_H__

#include "HFSM/HState.h"
class AttackHState :
    public HState
{
public:
	AttackHState(int stateId, AINode* aiNode) : HState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif