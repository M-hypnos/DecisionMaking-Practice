#include "WanderState.h"

void WanderState::onEnterAction() {
	CCLOG("WanderState::onEnterAction  ");
}

void WanderState::onExitAction() {
	CCLOG("WanderState::onExitAction  ");
}

void WanderState::onUpdateAction(float dt) {
	CCLOG("WanderState::onUpdateAction  ");
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	_aiNode->wander(dt);
}