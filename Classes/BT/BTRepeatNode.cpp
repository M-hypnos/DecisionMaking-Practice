#include "BTRepeatNode.h"

void BTRepeatNode::onExitAction(AINode* aiNode, BTResult result) {
	_repeatIdx = 0;
}

BTResult BTRepeatNode::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTRepeatNode::onUpdateAction  %d ", _repeatIdx);
	auto result = BTResult::SUCCESS;
	while (_repeatIdx < _repeatCount) {
		result = _childNode->onUpdate(dt, aiNode);
		if (result == BTResult::SUCCESS) {
			_repeatIdx++;
		}
		else {
			return result;
		}
	}
	return result;
}