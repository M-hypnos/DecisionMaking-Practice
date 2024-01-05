#include "AttackHState.h"

void AttackHState::onEnterAction() {
	CCLOG("AttackHState::onEnterAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->stopORCA();
}

void AttackHState::onExitAction() {
	CCLOG("AttackHState::onExitAction  ");
	_aiNode->resumeORCA();
	_aiNode->stopAttack();
}

void AttackHState::onUpdateAction(float dt) {
	CCLOG("AttackHState::onUpdateAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	_aiNode->attack();
}