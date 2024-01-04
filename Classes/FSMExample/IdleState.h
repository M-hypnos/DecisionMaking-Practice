#ifndef __IDLE_STATE_H__
#define __IDLE_STATE_H__

#include "FSM/BaseState.h"
class IdleState :
    public BaseState
{
public:
	IdleState(int stateId, AINode* aiNode) : BaseState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif