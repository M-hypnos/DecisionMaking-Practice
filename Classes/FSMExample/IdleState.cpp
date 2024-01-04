#include "IdleState.h"

void IdleState::onEnterAction() {
	CCLOG("IdleState::onEnterAction  ");
	auto scale1 = ScaleTo::create(0.2, 1.2);
	auto scale2 = ScaleTo::create(0.1, 1);
	auto delay = DelayTime::create(0.3);
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->runAction(RepeatForever::create(Sequence::create(scale1, scale2, delay, nullptr)));
}

void IdleState::onExitAction() {
	CCLOG("IdleState::onExitAction  ");
	_aiNode->stopAllActions();
	_aiNode->setScale(1);
	_aiNode->setRestInterval(10);
}

void IdleState::onUpdateAction(float dt) {
	CCLOG("IdleState::onUpdateAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->recoverHP(dt);
}