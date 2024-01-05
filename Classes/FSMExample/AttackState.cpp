#include "AttackState.h"

void AttackState::onEnterAction() {
	CCLOG("AttackState::onEnterAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->stopORCA();
}

void AttackState::onExitAction() {
	CCLOG("AttackState::onExitAction  ");
	_aiNode->resumeORCA();
	_aiNode->stopAttack();
}

void AttackState::onUpdateAction(float dt) {
	CCLOG("AttackState::onUpdateAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	_aiNode->attack();
}