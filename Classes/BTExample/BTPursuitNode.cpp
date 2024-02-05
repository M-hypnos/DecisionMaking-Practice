#include "BTPursuitNode.h"

void BTPursuitNode::onEnterAction(AINode* aiNode) {
	CCLOG("BTPursuitNode::onEnterAction  ");
}

void BTPursuitNode::onExitAction(AINode* aiNode, BTResult result) {
	CCLOG("BTPursuitNode::onExitAction  ");
}

BTResult BTPursuitNode::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTPursuitNode::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	return static_cast<AIAttackNode*>(aiNode)->pursuitEx(dt);
}