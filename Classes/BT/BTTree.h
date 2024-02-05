#ifndef __BT_TREE_H__
#define __BT_TREE_H__

using namespace std;

#include "BTNode.h"

class BTTree
{
public:
	BTTree(BTNode* root);

	void onUpdate(float dt, AINode* aiNode);
	void start(bool onlyOnce = false);

	virtual void setTree() = 0;
	virtual ~BTTree();
protected:
	bool _isActived;
	bool _onlyOnce;
	BTNode* _root;
private:
	
};

#endif