#include "EvadingHState.h"

void EvadingHState::onEnterAction(AINode* aiNode) {
	CCLOG("EvadingHState::onEnterAction  ");
}

void EvadingHState::onExitAction(AINode* aiNode) {
	CCLOG("EvadingHState::onExitAction  ");
}

void EvadingHState::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("EvadingHState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	static_cast<AIAttackNode*>(aiNode)->evading(dt);
}