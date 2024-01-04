#include "EvadingState.h"

void EvadingState::onEnterAction() {
	CCLOG("EvadingState::onEnterAction  ");
}

void EvadingState::onExitAction() {
	CCLOG("EvadingState::onExitAction  ");
}

void EvadingState::onUpdateAction(float dt) {
	CCLOG("EvadingState::onUpdateAction  ");
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	_aiNode->evading(dt);
}