#ifndef __ECLUDE_HSTATE_H__
#define __ECLUDE_HSTATE_H__

#include "HFSM/HState.h"
class EvadingHState :
    public HState
{
public:
	EvadingHState(int stateId, AINode* aiNode) : HState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif