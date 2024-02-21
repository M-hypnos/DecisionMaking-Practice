#include "BTTimeLimitNode.h"

BTTimeLimitNode::BTTimeLimitNode(BTNode* node, float limitTime)
: BTDecoratorNode(node)
, _limitTime(limitTime)
, _curTime(0)
{}

void BTTimeLimitNode::onExitAction(AINode* aiNode, BTResult result) {
	_curTime = 0;
}

BTResult BTTimeLimitNode::onUpdateAction(float dt, AINode* aiNode) {
	auto result = _childNode->onUpdate(dt, aiNode);
	if (result != BTResult::RUNNING) {
		return result;
	}
	_curTime += dt;
	if (_curTime >= _limitTime) {
		_childNode->onInterrupt(aiNode);
		return BTResult::FAIL;
	}
	return BTResult::RUNNING;
}