#ifndef __PURSUIT_STATE_H__
#define __PURSUIT_STATE_H__

#include "FSM/BaseState.h"
class PursuitState :
    public BaseState
{
public:
	PursuitState(int stateId, AINode* aiNode) : BaseState(stateId, aiNode) {}
private:
	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif