#ifndef __BT_SELECT_NODE_H__
#define __BT_SELECT_NODE_H__

using namespace std;

#include "BTControlNode.h"

class BTSelectNode : public BTControlNode
{
public:
	BTSelectNode();
	virtual ~BTSelectNode();
	virtual void onInterrupt(AINode* aiNode) override;
protected:
private:
	int _executeIdx;
	virtual void onEnterAction(AINode* aiNode) override;
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) override;
	virtual void onExitAction(AINode* aiNode, BTResult result) override;
};

#endif