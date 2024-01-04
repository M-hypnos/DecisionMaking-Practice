#ifndef __DEAD_STATE_H__
#define __DEAD_STATE_H__

#include "FSM/BaseState.h"
class DeadState :
    public BaseState
{
public:
	DeadState(int stateId, AINode* aiNode) : BaseState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif