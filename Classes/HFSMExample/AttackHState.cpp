#include "AttackHState.h"

void AttackHState::onEnterAction(AINode* aiNode) {
	//CCLOG("AttackHState::onEnterAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->stopORCA();
}

void AttackHState::onExitAction(AINode* aiNode) {
	//CCLOG("AttackHState::onExitAction  ");
	static_cast<AIAttackNode*>(aiNode)->resumeORCA();
	static_cast<AIAttackNode*>(aiNode)->stopAttack();
}

void AttackHState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("AttackHState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	static_cast<AIAttackNode*>(aiNode)->attack();
}