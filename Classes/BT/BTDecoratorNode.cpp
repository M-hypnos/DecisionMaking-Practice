#include "BTDecoratorNode.h"

void BTDecoratorNode::clear() {
	delete _childNode;
}

bool BTDecoratorNode::evaluate(AINode* aiNode) {
	return _childNode->evaluate(aiNode);
}

void BTDecoratorNode::onInterrupt(AINode* aiNode) {
	_childNode->onInterrupt(aiNode);
	onExit(aiNode, BTResult::INTERRUPT);
}