#ifndef _HFSM_NODE_H__
#define _HFSM_NODE_H__

#include "AIAttackNode.h"
#include "HFSM/HFSM.h"
#include "WanderHState.h"
#include "IdleHState.h"
#include "PursuitHState.h"
#include "AttackHState.h"
#include "EvadingHState.h"
#include "DeadHState.h"
using namespace std;

class HFSMNode : public AIAttackNode
{
public:
	static HFSMNode* create();

CC_CONSTRUCTOR_ACCESS:
	virtual bool init() override;

	virtual void update(float dt);

	virtual ~HFSMNode();
	
private:
	HFSM* _hfsm;
};

#endif