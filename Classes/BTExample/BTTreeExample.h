#ifndef __BT_TREE_EXAMPLE_H__
#define __BT_TREE_EXAMPLE_H__

using namespace std;

#include "BT/BTTree.h"
#include "BT/BTSelectNode.h"
#include "BT/BTPrioritySelectNode.h"
#include "BT/BTSequenceNode.h"
#include "BT/BTParallelNode.h"
#include "BT/BTConditionNode.h"
#include "BTDeadNode.h"
#include "BTAttackNode.h"
#include "BTIdleNode.h"
#include "BTPursuitNode.h"
#include "BTWanderNode.h"
#include "BTEvadingNode.h"
#include "BT/BTCooldownNode.h"
#include "BT/BTRepeatNode.h"
#include "AIAttackNode.h"

class BTTreeExample: public BTTree
{
public:
	BTTreeExample(BTNode* root);

	virtual void setTree() override;
	virtual ~BTTreeExample();
protected:

private:
	
};

#endif