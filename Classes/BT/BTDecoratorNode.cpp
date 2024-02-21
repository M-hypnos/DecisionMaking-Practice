#include "BTDecoratorNode.h"

BTDecoratorNode::BTDecoratorNode(BTNode* node)
: _childNode(node) {}

BTDecoratorNode::~BTDecoratorNode() {
	delete _childNode;
	_childNode = nullptr;
}

bool BTDecoratorNode::evaluate(AINode* aiNode) {
	return _childNode->evaluate(aiNode);
}

void BTDecoratorNode::onInterrupt(AINode* aiNode) {
	_childNode->onInterrupt(aiNode);
	onExit(aiNode, BTResult::INTERRUPT);
}