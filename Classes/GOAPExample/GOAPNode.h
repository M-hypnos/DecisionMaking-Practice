#ifndef _GOAP_NODE_H__
#define _GOAP_NODE_H__

#include "AIAttackNode.h"
#include "GOAP/GOAPWorldState.h"
#include "GOAP/GOAPSensors.h"
#include "GOAP/GOAPPlanRunner.h"
#include "GOAP/GOAPPlanner.h"
#include "GOAP/GOAPIGoal.h"
#include "GOAPNodeExample.h"

using namespace std;

class GOAPNodeExample;

class GOAPNode : public AIAttackNode
{
public:
	static GOAPNode* create();

CC_CONSTRUCTOR_ACCESS:
	virtual bool init() override;

	virtual void update(float dt);

	GOAPResult htnAttack();
	GOAPResult htnPursuit(float dt);
	GOAPResult htnEvading(float dt);

	virtual ~GOAPNode();
	
private:
	shared_ptr<GOAPPlanRunner> _planRunner;
	unique_ptr<GOAPWorldState> _worldState;
	unique_ptr<GOAPSensors> _sensors;
};

#endif