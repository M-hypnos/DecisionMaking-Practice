#include "PursuitState.h"

PursuitState::PursuitState(int stateId)
: BaseState(stateId)
{}

void PursuitState::onEnterAction(AINode* aiNode) {
	//CCLOG("PursuitState::onEnterAction  ");
}

void PursuitState::onExitAction(AINode* aiNode) {
	//CCLOG("PursuitState::onExitAction  ");
}

void PursuitState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("PursuitState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	static_cast<AIAttackNode*>(aiNode)->pursuit(dt);
}