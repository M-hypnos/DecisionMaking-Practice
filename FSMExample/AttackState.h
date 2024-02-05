#ifndef __ATTACK_STATE_H__
#define __ATTACK_STATE_H__

#include "FSM/BaseState.h"
#include "AIAttackNode.h"
class AttackState :
    public BaseState
{
public:
	AttackState(int stateId) : BaseState(stateId) {}
private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode);
	virtual void onUpdateAction(float dt, AINode* aiNode);
};

#endif