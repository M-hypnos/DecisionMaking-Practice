#include "WanderState.h"

void WanderState::onEnterAction(AINode* aiNode) {
	//CCLOG("WanderState::onEnterAction  ");
}

void WanderState::onExitAction(AINode* aiNode) {
	//CCLOG("WanderState::onExitAction  ");
}

void WanderState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("WanderState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	static_cast<AIAttackNode*>(aiNode)->wander(dt);
}