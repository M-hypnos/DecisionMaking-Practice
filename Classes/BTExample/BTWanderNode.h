#ifndef __BT_WANDER_NODE_H__
#define __BT_WANDER_NODE_H__

using namespace std;

#include "BT/BTActionNode.h"
#include "AIAttackNode.h"

class BTWanderNode : public BTActionNode
{
public:

protected:

private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode, BTResult result);
	virtual BTResult onUpdateAction(float dt, AINode* aiNode);
};

#endif