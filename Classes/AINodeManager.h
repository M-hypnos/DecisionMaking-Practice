#ifndef __AI_NODE_MANAGER_H__
#define __AI_NODE_MANAGER_H__

#include "cocos2d.h"
#include "FSMExample/FSMNode.h"
#include "HFSMExample/HFSMNode.h"

USING_NS_CC;
using namespace std;

enum class AINodeType {
	FSMNode,
	HFSMNode,
};

class AINodeManager
{
public:
	AINode* getFSMNode();
	AINode* getHFSMNode();

protected:
	
};

#endif