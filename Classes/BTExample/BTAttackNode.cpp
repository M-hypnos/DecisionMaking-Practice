#include "BTAttackNode.h"

void BTAttackNode::onEnterAction(AINode* aiNode) {
	//CCLOG("BTAttackNode::onEnterAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->stopORCA();
}

void BTAttackNode::onExitAction(AINode* aiNode, BTResult result) {
	//CCLOG("BTAttackNode::onExitAction  ");
	static_cast<AIAttackNode*>(aiNode)->resumeORCA();
	static_cast<AIAttackNode*>(aiNode)->stopAttack();
}

BTResult BTAttackNode::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("BTAttackNode::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	return static_cast<AIAttackNode*>(aiNode)->attackEx();
}