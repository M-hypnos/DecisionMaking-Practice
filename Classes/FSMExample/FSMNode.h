#ifndef _FSM_NODE_H__
#define _FSM_NODE_H__

#include "AINode.h"
#include "FSM/FSM.h"
#include "WanderState.h"
#include "IdleState.h"
#include "FSM/Transition.h"
#include "PursuitState.h"
#include "AttackState.h"
#include "EvadingState.h"
#include "DeadState.h"
using namespace std;

enum FSMNodeStateID
{
	Wander,
	Idle,
	Pursuit,
	Attack,
	Evading,
	Dead
};

class FSMNode : public AINode
{
public:
	static FSMNode* create();

CC_CONSTRUCTOR_ACCESS:
	virtual bool init() override;

	virtual void update(float dt);

	virtual ~FSMNode();
	
private:
	FSM* _fsm;
};

#endif