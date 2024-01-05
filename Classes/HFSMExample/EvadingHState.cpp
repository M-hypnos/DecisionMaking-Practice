#include "EvadingHState.h"

void EvadingHState::onEnterAction() {
	CCLOG("EvadingHState::onEnterAction  ");
}

void EvadingHState::onExitAction() {
	CCLOG("EvadingHState::onExitAction  ");
}

void EvadingHState::onUpdateAction(float dt) {
	CCLOG("EvadingHState::onUpdateAction  ");
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	_aiNode->evading(dt);
}