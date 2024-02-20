#include "BTIdleNode.h"

void BTIdleNode::onEnterAction(AINode* aiNode) {
	//CCLOG("BTIdleNode::onEnterAction  ");
	auto scale1 = ScaleTo::create(0.2, 1.2);
	auto scale2 = ScaleTo::create(0.1, 1);
	auto delay = DelayTime::create(0.3);
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->runAction(RepeatForever::create(Sequence::create(scale1, scale2, delay, nullptr)));
}

void BTIdleNode::onExitAction(AINode* aiNode, BTResult result) {
	//CCLOG("BTIdleNode::onExitAction  ");
	static_cast<AIAttackNode*>(aiNode)->stopAllActions();
	static_cast<AIAttackNode*>(aiNode)->setScale(1);
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(10);
}

BTResult BTIdleNode::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("BTIdleNode::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->recoverHP(dt);
	return BTResult::RUNNING;
}