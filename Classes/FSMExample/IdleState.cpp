#include "IdleState.h"

void IdleState::onEnterAction(AINode* aiNode) {
	//CCLOG("IdleState::onEnterAction  ");
	auto scale1 = ScaleTo::create(0.2, 1.2);
	auto scale2 = ScaleTo::create(0.1, 1);
	auto delay = DelayTime::create(0.3);
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->runAction(RepeatForever::create(Sequence::create(scale1, scale2, delay, nullptr)));
}

void IdleState::onExitAction(AINode* aiNode) {
	//CCLOG("IdleState::onExitAction  ");
	static_cast<AIAttackNode*>(static_cast<AIAttackNode*>(aiNode))->stopAllActions();
	static_cast<AIAttackNode*>(static_cast<AIAttackNode*>(aiNode))->setScale(1);
	static_cast<AIAttackNode*>(static_cast<AIAttackNode*>(aiNode))->setRestInterval(10);
}

void IdleState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("IdleState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->recoverHP(dt);
}