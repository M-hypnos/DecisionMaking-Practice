#ifndef __BT_ACTION_NODE_H__
#define __BT_ACTION_NODE_H__

using namespace std;

#include "BTNode.h"

class BTActionNode : public BTNode
{
public:
	BTActionNode();
	virtual ~BTActionNode();
protected:

private:
	virtual void onEnterAction(AINode* aiNode) override {}
	virtual void onExitAction(AINode* aiNode, BTResult result) override {}
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) override { return BTResult::SUCCESS; }
};

#endif