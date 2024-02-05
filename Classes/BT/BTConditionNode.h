#ifndef __BT_CONDITION_NODE_H__
#define __BT_CONDITION_NODE_H__

using namespace std;

#include "BTNode.h"

class BTConditionNode : public BTNode
{
public:
	BTConditionNode(function<bool(AINode*, float dt)> conditionFunc);

	virtual ~BTConditionNode();
protected:

private:
	virtual void onEnterAction(AINode* aiNode) override  {}
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) override;
	virtual void onExitAction(AINode* aiNode, BTResult result) override  {}

	function<bool(AINode*, float dt)> _conditionFunc;
};

#endif