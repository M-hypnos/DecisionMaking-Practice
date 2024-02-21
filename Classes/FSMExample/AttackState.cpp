#include "AttackState.h"

AttackState::AttackState(int stateId)
: BaseState(stateId)
{}

void AttackState::onEnterAction(AINode* aiNode) {
	//CCLOG("AttackState::onEnterAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->stopORCA();
}

void AttackState::onExitAction(AINode* aiNode) {
	//CCLOG("AttackState::onExitAction  ");
	static_cast<AIAttackNode*>(aiNode)->resumeORCA();
	static_cast<AIAttackNode*>(aiNode)->stopAttack();
}

void AttackState::onUpdateAction(float dt, AINode* aiNode) {
	//CCLOG("AttackState::onUpdateAction  ");
	static_cast<AIAttackNode*>(aiNode)->setVelocity(Vec2::ZERO);
	static_cast<AIAttackNode*>(aiNode)->setRestInterval(static_cast<AIAttackNode*>(aiNode)->getRestInterval() - dt);
	static_cast<AIAttackNode*>(aiNode)->attack();
}