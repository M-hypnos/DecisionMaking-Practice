#ifndef __BT_DECORATOR_NODE_H__
#define __BT_DECORATOR_NODE_H__

using namespace std;

#include "BTNode.h"

class BTDecoratorNode : public BTNode
{
public:
	BTDecoratorNode(BTNode* node);
	virtual bool evaluate(AINode* aiNode) override;
	virtual void onInterrupt(AINode* aiNode);
	virtual ~BTDecoratorNode();
	BTDecoratorNode() = delete;
protected:
	BTNode* _childNode;
private:
	virtual void onEnterAction(AINode* aiNode) override {}
	virtual void onExitAction(AINode* aiNode, BTResult result) override {}
};

#endif