#include "WanderHState.h"

void WanderHState::onEnterAction() {
	CCLOG("WanderHState::onEnterAction  ");
}

void WanderHState::onExitAction() {
	CCLOG("WanderHState::onExitAction  ");
}

void WanderHState::onUpdateAction(float dt) {
	CCLOG("WanderHState::onUpdateAction  ");
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	_aiNode->wander(dt);
}