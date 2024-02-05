#include "BTEvadingNode.h"

void BTEvadingNode::onEnterAction(AINode* aiNode) {
	CCLOG("BTEvadingNode::onEnterAction  ");
}

void BTEvadingNode::onExitAction(AINode* aiNode, BTResult result) {
	CCLOG("BTEvadingNode::onExitAction  ");
}

BTResult BTEvadingNode::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTEvadingNode::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	static_cast<AIAttackNode*>(aiNode)->evadingEx(dt);
	return BTResult::RUNNING;
}