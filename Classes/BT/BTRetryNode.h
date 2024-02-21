#ifndef __BT_RETRY_NODE_H__
#define __BT_RETRY_NODE_H__

using namespace std;

#include "BTDecoratorNode.h"

class BTRetryNode : public BTDecoratorNode
{
public:
	BTRetryNode(BTNode* node, int count = 1);

	virtual ~BTRetryNode() {};
protected:
	
private:
	int _retryCount;
	int _retryIdx;
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) override;
	virtual void onExitAction(AINode* aiNode, BTResult result) override;
};

#endif