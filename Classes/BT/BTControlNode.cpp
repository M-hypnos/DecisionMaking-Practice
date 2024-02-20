#include "BTControlNode.h"

BTControlNode::BTControlNode()
{
};

BTControlNode::~BTControlNode(){
	for (auto node : _childNodes) {
		delete node;
	}
	_childNodes.clear();
}

void BTControlNode::addChild(BTNode* node) {
	_childNodes.push_back(node);
	node->_parentNode = this;
}