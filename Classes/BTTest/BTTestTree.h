#ifndef __BT_TEST_TREE_H__
#define __BT_TEST_TREE_H__

using namespace std;

#include "BT/BTTree.h"
#include "BT/BTSelectNode.h"
#include "BT/BTPrioritySelectNode.h"
#include "BT/BTSequenceNode.h"
#include "BT/BTParallelNode.h"
#include "BT/BTConditionNode.h"
#include "BT/BTCooldownNode.h"
#include "BT/BTRepeatNode.h"
#include "BT/BTRetryNode.h"
#include "BT/BTTimeLimitNode.h"
#include "BTImmediateActA.h"
#include "BTImmediateActB.h"
#include "BTImmediateActC.h"
#include "BTDelayActA.h"
#include "BTDelayActB.h"
#include "BTDelayActC.h"

class BTTestTree : public BTTree
{
public:
	BTTestTree(BTNode* root);

	virtual void setTree() override;
	virtual ~BTTestTree();
protected:

private:
	
};

#endif