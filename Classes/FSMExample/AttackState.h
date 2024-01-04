#ifndef __ATTACK_STATE_H__
#define __ATTACK_STATE_H__

#include "FSM/BaseState.h"
class AttackState :
    public BaseState
{
public:
	AttackState(int stateId, AINode* aiNode) : BaseState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif