#ifndef __BT_CONTROL_NODE_H__
#define __BT_CONTROL_NODE_H__

using namespace std;

#include "BTNode.h"

class BTControlNode : public BTNode
{
public:
	BTControlNode();

	
	void addChild(BTNode* node) override;

	virtual ~BTControlNode();
protected:
	vector<BTNode* > _childNodes;
private:
};

#endif