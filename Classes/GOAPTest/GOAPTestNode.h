#ifndef _GOAP_TEST_NODE_H__
#define _GOAP_TEST_NODE_H__

#include "cocos2d.h"
#include "AINode.h"
#include "GOAP/GOAPWorldState.h"
#include "GOAP/GOAPSensors.h"
#include "GOAP/GOAPPlanRunner.h"
#include "GOAPNodeTest.h"
#include "GOAP/GOAPPlanner.h"

USING_NS_CC;
using namespace std;

class GOAPTestNode : public AINode
{
public:
	static GOAPTestNode* create();

CC_CONSTRUCTOR_ACCESS:
	virtual ~GOAPTestNode();
	virtual bool init() override;

	void setString(string str);
	void setString1(string str);
	void setString2(string str);

	void createGoap();

	virtual void update(float dt);

protected:
	Label* _label;
	Label* _label1;
	Label* _label2;

	shared_ptr<GOAPPlanRunner> _planRunner;
	unique_ptr<GOAPWorldState> _worldState;
	unique_ptr<GOAPSensors> _sensors;
};

#endif