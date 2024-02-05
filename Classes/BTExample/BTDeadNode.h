#ifndef __BT_DEAD_NODE_H__
#define __BT_DEAD_NODE_H__

using namespace std;

#include "BT/BTActionNode.h"
#include "AIAttackNode.h"

class BTDeadNode : public BTActionNode
{
public:
	BTDeadNode() :BTActionNode() {}

protected:

private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode, BTResult result);
	virtual BTResult onUpdateAction(float dt, AINode* aiNode);
};

#endif