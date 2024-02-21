#include "DeadState.h"

DeadState::DeadState(int stateId)
: BaseState(stateId)
{}

void DeadState::onEnterAction(AINode* aiNode) {
	//CCLOG("DeadState::onEnterAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->stopORCA();
	static_cast<AIAttackNode*>(aiNode)->setDead();
}

void DeadState::onExitAction(AINode* aiNode) {
	//CCLOG("DeadState::onExitAction  ");
	static_cast<AIAttackNode*>(aiNode)->resumeORCA();
}

void DeadState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("DeadState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->addDeadTime(dt);
}