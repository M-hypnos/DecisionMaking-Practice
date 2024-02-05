#ifndef __BT_IDLE_NODE_H__
#define __BT_IDLE_NODE_H__

using namespace std;

#include "BT/BTActionNode.h"
#include "AIAttackNode.h"

class BTIdleNode : public BTActionNode
{
public:
	BTIdleNode() :BTActionNode() {}

protected:

private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode, BTResult result);
	virtual BTResult onUpdateAction(float dt, AINode* aiNode);
};

#endif