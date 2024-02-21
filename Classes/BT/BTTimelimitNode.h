#ifndef __BT_TIMELIMIT_NODE_H__
#define __BT_TIMELIMIT_NODE_H__

using namespace std;

#include "BTDecoratorNode.h"

class BTTimeLimitNode : public BTDecoratorNode
{
public:
	BTTimeLimitNode(BTNode* node, float limitTime = 1);
protected:
	
private:
	float _limitTime;
	float _curTime;
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) override;
	virtual void onExitAction(AINode* aiNode, BTResult result) override;
};

#endif