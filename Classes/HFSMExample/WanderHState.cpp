#include "WanderHState.h"

WanderHState::WanderHState(int stateId)
: HState(stateId)
{}

void WanderHState::onEnterAction(AINode* aiNode) {
	//CCLOG("WanderHState::onEnterAction  ");
}

void WanderHState::onExitAction(AINode* aiNode) {
	//CCLOG("WanderHState::onExitAction  ");
}

void WanderHState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("WanderHState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	static_cast<AIAttackNode*>(aiNode)->wander(dt);
}