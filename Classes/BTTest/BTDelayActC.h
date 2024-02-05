#ifndef __BT_DELAY_ACT_C_H__
#define __BT_DELAY_ACT_C_H__

using namespace std;

#include "BT/BTActionNode.h"
#include "AILogNode.h"

class BTDelayActC : public BTActionNode
{
public:
	BTDelayActC() :BTActionNode() {}

protected:

private:
	virtual void onEnterAction(AINode* aiNode);
	virtual void onExitAction(AINode* aiNode, BTResult result);
	virtual BTResult onUpdateAction(float dt, AINode* aiNode);
	int times = 0;
};

#endif