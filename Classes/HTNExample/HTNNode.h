#ifndef _HTN_NODE_H__
#define _HTN_NODE_H__

#include "AIAttackNode.h"
#include "HTN/HTNDomain.h"
#include "HTN/HTNPlanRunner.h"
#include "HTN/HTNWorldState.h"
#include "HTN/HTNSensors.h"
#include "HTNNodeExample.h"

using namespace std;

class HTNNodeExample;

class HTNNode : public AIAttackNode
{
public:
	static HTNNode* create();

CC_CONSTRUCTOR_ACCESS:
	virtual bool init() override;

	virtual void update(float dt);

	HTNResult htnAttack();
	HTNResult htnPursuit(float dt);
	HTNResult htnEvading(float dt);

	virtual ~HTNNode();
	
private:
	shared_ptr<HTNPlanRunner> _planRunner;
	shared_ptr<HTNDomain> _domain;
	unique_ptr<HTNWorldState> _worldState;
	unique_ptr<HTNSensors> _sensors;
};

#endif