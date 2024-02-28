#ifndef _HTN_NODE_H__
#define _HTN_NODE_H__

#include "AIAttackNode.h"
#include "HTN/HTNDomain.h"
#include "HTN/HTNPlanRunner.h"
#include "HTN/HTNWorldState.h"
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

	void updateWorldState(string key, Any data);
	HTNResult htnAttack();
	HTNResult htnPursuit(float dt);
	HTNResult htnEvading(float dt);
	void hurtEx() override;

	auto checkFindEnemy()-> void override {
		if (!notFoundEnemy()) {
			updateWorldState("findEnemy", true);
		}
	}

	virtual ~HTNNode();
	
private:
	shared_ptr<HTNPlanRunner> _planRunner;
	shared_ptr<HTNDomain> _domain;
	unique_ptr<HTNWorldState> _worldState;
};

#endif