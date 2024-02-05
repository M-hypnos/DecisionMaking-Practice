#ifndef __BT_IMMEDIATE_ACT_C_H__
#define __BT_IMMEDIATE_ACT_C_H__

using namespace std;

#include "BT/BTActionNode.h"
#include "AILogNode.h"

class BTImmediateActC : public BTActionNode
{
public:
	BTImmediateActC() :BTActionNode() {}

protected:

private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode, BTResult result);
	virtual BTResult onUpdateAction(float dt, AINode* aiNode);
	int times = 0;
};

#endif