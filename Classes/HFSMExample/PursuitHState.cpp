#include "PursuitHState.h"

PursuitHState::PursuitHState(int stateId)
: HState(stateId)
{}

void PursuitHState::onEnterAction(AINode* aiNode) {
	//CCLOG("PursuitHState::onEnterAction  ");
}

void PursuitHState::onExitAction(AINode* aiNode) {
	//CCLOG("PursuitHState::onExitAction  ");
}

void PursuitHState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("PursuitHState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	static_cast<AIAttackNode*>(aiNode)->pursuit(dt);
}