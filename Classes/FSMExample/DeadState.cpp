#include "DeadState.h"

void DeadState::onEnterAction() {
	CCLOG("DeadState::onEnterAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->stopORCA();
}

void DeadState::onExitAction() {
	CCLOG("DeadState::onExitAction  ");
	_aiNode->resumeORCA();
}

void DeadState::onUpdateAction(float dt) {
	CCLOG("DeadState::onUpdateAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
}