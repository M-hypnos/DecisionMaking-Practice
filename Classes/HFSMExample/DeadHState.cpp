#include "DeadHState.h"

void DeadHState::onEnterAction(AINode* aiNode) {
	//CCLOG("DeadHState::onEnterAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->stopORCA();
	static_cast<AIAttackNode*>(aiNode)->setDead();
}

void DeadHState::onExitAction(AINode* aiNode) {
	//CCLOG("DeadHState::onExitAction  ");
	static_cast<AIAttackNode*>(aiNode)->resumeORCA();
}

void DeadHState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("DeadHState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->addDeadTime(dt);
}