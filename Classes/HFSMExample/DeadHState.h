#ifndef __DEAD_HSTATE_H__
#define __DEAD_HSTATE_H__

#include "HFSM/HState.h"
class DeadHState :
    public HState
{
public:
	DeadHState(int stateId, AINode* aiNode) : HState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif