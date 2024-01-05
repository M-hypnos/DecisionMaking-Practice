#ifndef __ECLUDE_STATE_H__
#define __ECLUDE_STATE_H__

#include "FSM/BaseState.h"
class EvadingState :
    public BaseState
{
public:
	EvadingState(int stateId, AINode* aiNode) : BaseState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif