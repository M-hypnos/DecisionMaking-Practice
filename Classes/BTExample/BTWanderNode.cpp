#include "BTWanderNode.h"

void BTWanderNode::onEnterAction(AINode* aiNode) {
	//CCLOG("BTWanderNode::onEnterAction  ");
}

void BTWanderNode::onExitAction(AINode* aiNode, BTResult result) {
	//CCLOG("BTWanderNode::onExitAction  ");
}

BTResult BTWanderNode::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("BTWanderNode::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->wander(dt);
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	return BTResult::RUNNING;
}