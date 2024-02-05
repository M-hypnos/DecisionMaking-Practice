#ifndef __BT_PURSUIT_NODE_H__
#define __BT_PURSUIT_NODE_H__

using namespace std;

#include "BT/BTActionNode.h"
#include "AIAttackNode.h"

class BTPursuitNode : public BTActionNode
{
public:
	BTPursuitNode() :BTActionNode() {}

protected:

private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode, BTResult result);
	virtual BTResult onUpdateAction(float dt, AINode* aiNode);
};

#endif