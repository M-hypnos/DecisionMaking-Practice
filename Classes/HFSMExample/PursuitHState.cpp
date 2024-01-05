#include "PursuitHState.h"

void PursuitHState::onEnterAction() {
	CCLOG("PursuitHState::onEnterAction  ");
}

void PursuitHState::onExitAction() {
	CCLOG("PursuitHState::onExitAction  ");
}

void PursuitHState::onUpdateAction(float dt) {
	CCLOG("PursuitHState::onUpdateAction  ");
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	_aiNode->pursuit(dt);
}