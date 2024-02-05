#ifndef _BT_TREE_NODE_H__
#define _BT_TREE_NODE_H__

#include "AIAttackNode.h"
#include "AIEnum.h"
#include "BTTreeExample.h"
using namespace std;

class BTTreeNode : public AIAttackNode
{
public:
	static BTTreeNode* create();

CC_CONSTRUCTOR_ACCESS:
	virtual bool init() override;

	virtual void update(float dt);

	virtual ~BTTreeNode();
	
private:
	BTTree* _btTree;
};

#endif