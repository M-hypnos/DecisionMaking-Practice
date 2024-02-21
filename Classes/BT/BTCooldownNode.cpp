#include "BTCooldownNode.h"

BTCooldownNode::BTCooldownNode(BTNode* node, float cooldownTime)
: BTDecoratorNode(node)
, _cooldownTime(cooldownTime)
, _lastActTime(0) 
{
}

bool BTCooldownNode::evaluate(AINode* aiNode) {
	auto cur = std::chrono::system_clock::now();
	auto curTimeStamp = std::chrono::time_point_cast<std::chrono::milliseconds>(cur).time_since_epoch().count();
	if ((curTimeStamp - _lastActTime) < _cooldownTime * 1000) {
		return false;
	}
	return _childNode->evaluate(aiNode);
}

void BTCooldownNode::onExitAction(AINode* aiNode, BTResult result) {
	auto cur = std::chrono::system_clock::now();
	_lastActTime = std::chrono::time_point_cast<std::chrono::milliseconds>(cur).time_since_epoch().count();
}

BTResult BTCooldownNode::onUpdateAction(float dt, AINode* aiNode) {
	auto result = _childNode->onUpdate(dt, aiNode);
	return result;
}