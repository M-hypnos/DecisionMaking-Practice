#include "BTDeadNode.h"

void BTDeadNode::onEnterAction(AINode* aiNode) {
	CCLOG("BTDeadNode::onEnterAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->stopORCA();
	static_cast<AIAttackNode*>(aiNode)->setDead();
}

void BTDeadNode::onExitAction(AINode* aiNode, BTResult result) {
	CCLOG("BTDeadNode::onExitAction  ");
	static_cast<AIAttackNode*>(aiNode)->resumeORCA();
}

BTResult BTDeadNode::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTDeadNode::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	return BTResult::RUNNING;
}