#ifndef _FSM_NODE_H__
#define _FSM_NODE_H__

#include "AIAttackNode.h"
#include "AIEnum.h"
#include "FSM/FSM.h"
#include "WanderState.h"
#include "IdleState.h"
#include "PursuitState.h"
#include "AttackState.h"
#include "EvadingState.h"
#include "DeadState.h"
using namespace std;

class FSMNode : public AIAttackNode
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