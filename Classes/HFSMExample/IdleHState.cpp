#include "IdleHState.h"

void IdleHState::onEnterAction(AINode* aiNode) {
	CCLOG("IdleHState::onEnterAction  ");
	auto scale1 = ScaleTo::create(0.2, 1.2);
	auto scale2 = ScaleTo::create(0.1, 1);
	auto delay = DelayTime::create(0.3);
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->runAction(RepeatForever::create(Sequence::create(scale1, scale2, delay, nullptr)));
}

void IdleHState::onExitAction(AINode* aiNode) {
	CCLOG("IdleHState::onExitAction  ");
	static_cast<AIAttackNode*>(aiNode)->stopAllActions();
	static_cast<AIAttackNode*>(aiNode)->setScale(1);
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(10);
}

void IdleHState::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("IdleHState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->recoverHP(dt);
}