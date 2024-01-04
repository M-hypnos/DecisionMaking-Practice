#ifndef __WANDER_STATE_H__
#define __WANDER_STATE_H__

#include "FSM/BaseState.h"
class WanderState :
    public BaseState
{
public:
	WanderState(int stateId, AINode* aiNode) : BaseState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif