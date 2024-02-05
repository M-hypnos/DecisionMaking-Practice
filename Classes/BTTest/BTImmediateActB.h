#ifndef __BT_IMMEDIATE_ACT_B_H__
#define __BT_IMMEDIATE_ACT_B_H__

using namespace std;

#include "BT/BTActionNode.h"
#include "AILogNode.h"

class BTImmediateActB : public BTActionNode
{
public:
	BTImmediateActB() :BTActionNode() {}

protected:

private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode, BTResult result);
	virtual BTResult onUpdateAction(float dt, AINode* aiNode);
	int times = 0;
};

#endif