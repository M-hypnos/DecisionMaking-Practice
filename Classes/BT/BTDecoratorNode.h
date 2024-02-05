#ifndef __BT_DECORATOR_NODE_H__
#define __BT_DECORATOR_NODE_H__

using namespace std;

#include "BTNode.h"

class BTDecoratorNode : public BTNode
{
public:
	BTDecoratorNode(BTNode* node) : _childNode(node){}
	virtual void clear() override;
	virtual bool evaluate(AINode* aiNode) override;
	virtual void onInterrupt(AINode* aiNode);
	virtual ~BTDecoratorNode() {};
protected:
	BTNode* _childNode;
private:
	virtual void onEnterAction(AINode* aiNode) override {}
	virtual void onExitAction(AINode* aiNode, BTResult result) override {}
};

#endif