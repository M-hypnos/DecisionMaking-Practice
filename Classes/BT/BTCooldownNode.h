#ifndef __BT_COOLDOWN_NODE_H__
#define __BT_COOLDOWN_NODE_H__

using namespace std;

#include "BTDecoratorNode.h"

class BTCooldownNode : public BTDecoratorNode
{
public:
	BTCooldownNode(BTNode* node, float cooldownTime = 1);
	virtual bool evaluate(AINode* aiNode) override;
protected:
	
private:
	float _cooldownTime;
	long long _lastActTime;
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) override;
	virtual void onExitAction(AINode* aiNode, BTResult result) override;
};

#endif