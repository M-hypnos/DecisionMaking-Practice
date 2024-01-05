#include "PursuitState.h"

void PursuitState::onEnterAction() {
	CCLOG("PursuitState::onEnterAction  ");
}

void PursuitState::onExitAction() {
	CCLOG("PursuitState::onExitAction  ");
}

void PursuitState::onUpdateAction(float dt) {
	CCLOG("PursuitState::onUpdateAction  ");
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	_aiNode->pursuit(dt);
}