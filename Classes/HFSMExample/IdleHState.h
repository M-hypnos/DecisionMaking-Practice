#ifndef __IDLE_HSTATE_H__
#define __IDLE_HSTATE_H__

#include "HFSM/HState.h"
class IdleHState :
    public HState
{
public:
	IdleHState(int stateId, AINode* aiNode) : HState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif