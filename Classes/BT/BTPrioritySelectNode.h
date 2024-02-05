#ifndef __BT_PRIORITY_SELECT_NODE_H__
#define __BT_PRIORITY_SELECT_NODE_H__

using namespace std;

#include "BTControlNode.h"

class BTPrioritySelectNode : public BTControlNode
{
public:
	BTPrioritySelectNode();
	virtual ~BTPrioritySelectNode();
	virtual void onInterrupt(AINode* aiNode) override;
protected:
private:
	int _executeIdx;
	virtual void onEnterAction(AINode* aiNode) override;
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) override;
	virtual void onExitAction(AINode* aiNode, BTResult result) override;
};

#endif