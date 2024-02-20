#include "EvadingState.h"

void EvadingState::onEnterAction(AINode* aiNode) {
	//CCLOG("EvadingState::onEnterAction  ");
}

void EvadingState::onExitAction(AINode* aiNode) {
	//CCLOG("EvadingState::onExitAction  ");
}

void EvadingState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("EvadingState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	static_cast<AIAttackNode*>(aiNode)->evading(dt);
}