#ifndef __AI_NODE_MANAGER_H__
#define __AI_NODE_MANAGER_H__

#include "cocos2d.h"
#include "FSMExample/FSMNode.h"

USING_NS_CC;
using namespace std;

enum class AINodeType {
	FSMNode
};

class AINodeManager
{
public:
	AINode* getFSMNode();

protected:
	
};

#endif