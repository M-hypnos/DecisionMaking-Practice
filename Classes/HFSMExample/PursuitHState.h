#ifndef __PURSUIT_HSTATE_H__
#define __PURSUIT_HSTATE_H__

#include "HFSM/HState.h"
class PursuitHState :
    public HState
{
public:
	PursuitHState(int stateId, AINode* aiNode) : HState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif