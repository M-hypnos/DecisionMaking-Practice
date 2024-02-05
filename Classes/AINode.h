#ifndef _AI_NODE_H__
#define _AI_NODE_H__

#include "cocos2d.h"
#include "AIEnum.h"
USING_NS_CC;
using namespace std;

class AINode : public Node
{
public:
	static AINode* create();

CC_CONSTRUCTOR_ACCESS:
	virtual bool init() override;
	virtual bool isStopORCA();
	float getWeight() { return _weight; }
protected:
	float _weight = 0.5;
};

#endif