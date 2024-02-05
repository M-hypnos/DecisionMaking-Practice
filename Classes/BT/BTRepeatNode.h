#ifndef __BT_REPEAT_NODE_H__
#define __BT_REPEAT_NODE_H__

using namespace std;

#include "BTDecoratorNode.h"

class BTRepeatNode : public BTDecoratorNode
{
public:
	BTRepeatNode(BTNode* node, int count = 1) : BTDecoratorNode(node), _repeatCount(count), _repeatIdx(0) {}

	virtual ~BTRepeatNode() {};
protected:
	
private:
	int _repeatCount;
	int _repeatIdx;
	virtual void onEnterAction(AINode* aiNode) override;
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) override;
	virtual void onExitAction(AINode* aiNode, BTResult result) override;
};

#endif