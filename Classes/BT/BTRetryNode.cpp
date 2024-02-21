#include "BTRetryNode.h"

BTRetryNode::BTRetryNode(BTNode* node, int count)
: BTDecoratorNode(node)
, _retryCount(count)
, _retryIdx(0)
{}

void BTRetryNode::onExitAction(AINode* aiNode, BTResult result) {
	_retryIdx = 0;
}

BTResult BTRetryNode::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTRepeatNode::onUpdateAction  %d ", _retryIdx);
	auto result = BTResult::FAIL;
	while (_retryIdx < _retryCount) {
		result = _childNode->onUpdate(dt, aiNode);
		if (result == BTResult::FAIL) {
			_retryIdx++;
		}
		else {
			return result;
		}
	}
	return result;
}