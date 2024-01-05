#include "DeadHState.h"

void DeadHState::onEnterAction() {
	CCLOG("DeadHState::onEnterAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->stopORCA();
	_aiNode->setDead();
}

void DeadHState::onExitAction() {
	CCLOG("DeadHState::onExitAction  ");
	_aiNode->resumeORCA();
}

void DeadHState::onUpdateAction(float dt) {
	CCLOG("DeadHState::onUpdateAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
}