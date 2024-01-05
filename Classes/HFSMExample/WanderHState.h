#ifndef __WANDER_HSTATE_H__
#define __WANDER_HSTATE_H__

#include "HFSM/HState.h"
class WanderHState :
    public HState
{
public:
	WanderHState(int stateId, AINode* aiNode) : HState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif