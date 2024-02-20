#ifndef __BT_PARALLEL_NODE_H__
#define __BT_PARALLEL_NODE_H__

using namespace std;

#include "BTControlNode.h"

class BTParallelNode : public BTControlNode
{
public:
	BTParallelNode(int successTarNum = 1);
	virtual void onInterrupt(AINode* aiNode) override;
	virtual ~BTParallelNode();
protected:
private:
	int _successTarNum;
	int _successCurNum;
	int _failCurNum;
	vector<BTNode* > _waitNodes;
	virtual void onEnterAction(AINode* aiNode) override;
	virtual BTResult onUpdateAction(float dt, AINode* aiNode) override;
	virtual void onExitAction(AINode* aiNode, BTResult result) override;
};

#endif