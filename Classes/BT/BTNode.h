#ifndef __BT_NODE_H__
#define __BT_NODE_H__

using namespace std;

#include "AINode.h"
#include "AIEnum.h"
#include "BTPrecondition.h"

class BTNode
{
public:
	BTNode();
	void onEnter(AINode* aiNode);
	BTResult onUpdate(float dt, AINode* aiNode);
	void onExit(AINode* aiNode, BTResult result);
	virtual void onInterrupt(AINode* aiNode);
	virtual bool evaluate(AINode* aiNode);
	virtual ~BTNode();
	BTNode* _parentNode;
	void clear();
	virtual void addChild(BTNode* node) { node->_parentNode = this; }
	void addPrecondition(BTPrecondition* precondition) { _precondition = precondition; }
	bool isRunning() { return _isRunning; }
protected:
	BTPrecondition* _precondition;
private:
	bool _isRunning;
	virtual void onEnterAction(AINode* aiNode) = 0;
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) = 0;
	virtual void onExitAction(AINode* aiNode, BTResult result) = 0;
};

#endif