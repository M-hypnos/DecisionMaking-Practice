#ifndef _AI_LOG_NODE_H__
#define _AI_LOG_NODE_H__

#include "cocos2d.h"
#include "AINode.h"
#include "BTTest/BTTestTree.h"
USING_NS_CC;
using namespace std;

class AILogNode : public AINode
{
public:
	static AILogNode* create();

CC_CONSTRUCTOR_ACCESS:
	virtual ~AILogNode();
	virtual bool init() override;

	void setString(string str);
	void setString1(string str);
	void setString2(string str);

	void startTree();
	virtual void update(float dt);

	BTResult doImmediatelyAction(string str);
	void interruptAct();
	BTResult doDelayAction(float dt, string str);
protected:
	Label* _label;
	Label* _label1;
	Label* _label2;
	float _delayActTime = 0;
	BTTree* _btTree;
};

#endif