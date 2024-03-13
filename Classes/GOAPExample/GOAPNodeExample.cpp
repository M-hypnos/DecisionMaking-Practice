#include "GOAPNodeExample.h"

using namespace GOAPNodeExampleSpace;

AttackNode::AttackNode(GOAPNode* aiNode)
: GOAPAction("attackNode", 1)
,_aiNode(aiNode)
{
	setPreconditionStates({ {"inAttackRange", true}, {"findEnemy", true } });
	setEffectStates({ { "findEnemy", false } });
};

AttackNode::~AttackNode() {
	_aiNode = nullptr;
}


void AttackNode::onEnterAction() {
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->stopORCA();
}

GOAPResult AttackNode::onUpdateAction(float dt) {
	CCLOG("GOAP AttackNode::onUpdateAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	return _aiNode->htnAttack();
}

void AttackNode::onExitAction(GOAPResult result) {
	_aiNode->resumeORCA();
	_aiNode->stopAttack();
}

DeadNode::DeadNode(GOAPNode* aiNode)
: GOAPAction("deadNode", 1)
, _aiNode(aiNode)
{
	setPreconditionStates({ { "alive", false },{"deadDelete", false}});
	setEffectStates({ { "deadDelete", true } });
};

DeadNode::~DeadNode() {
	_aiNode = nullptr;
}

void DeadNode::onEnterAction() {
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->stopORCA();
	_aiNode->setDead();
}

GOAPResult DeadNode::onUpdateAction(float dt) {
	CCLOG("GOAP DeadNode::onUpdateAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->addDeadTime(dt);
	return GOAPResult::GRUNNING;
}

void DeadNode::onExitAction(GOAPResult result) {
	_aiNode->resumeORCA();
}

WanderNode::WanderNode(GOAPNode* aiNode)
: GOAPAction("wanderNode", 1)
, _aiNode(aiNode)
{
	setPreconditionStates({ { "findEnemy", false} });
	setEffectStates({ { "findEnemy", true } });
};

WanderNode::~WanderNode() {
	_aiNode = nullptr;
}

void WanderNode::onEnterAction() {
}

GOAPResult WanderNode::onUpdateAction(float dt) {
	CCLOG("GOAP WanderNode::onUpdateAction  ");
	_aiNode->wander(dt);
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	return _aiNode->notFoundEnemy() ? GOAPResult::GRUNNING : GOAPResult::GSUCCESS;
}

void WanderNode::onExitAction(GOAPResult result) {
}

PursuitNode::PursuitNode(GOAPNode* aiNode)
: GOAPAction("pursuitNode", 1)
, _aiNode(aiNode)
{
	setPreconditionStates({ { "inAttackRange", false} });
	setEffectStates({ { "inAttackRange", true } });
};

PursuitNode::~PursuitNode() {
	_aiNode = nullptr;
}

void PursuitNode::onEnterAction() {
}

GOAPResult PursuitNode::onUpdateAction(float dt) {
	CCLOG("GOAP PursuitNode::onUpdateAction  ");

	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	return _aiNode->htnPursuit(dt);
}

void PursuitNode::onExitAction(GOAPResult result) {
}

EvadingNode::EvadingNode(GOAPNode* aiNode)
: GOAPAction("evadingNode", 1)
, _aiNode(aiNode)
{
	setPreconditionStates({ {"inDanger", true}, {"findEnemy", true}});
	setEffectStates({ { "findEnemy", false } });
};

EvadingNode::~EvadingNode() {
	_aiNode = nullptr;
}

void EvadingNode::onEnterAction() {
}

GOAPResult EvadingNode::onUpdateAction(float dt) {
	CCLOG("GOAP EvadingNode::onUpdateAction  ");
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	return _aiNode->htnEvading(dt);
}

void EvadingNode::onExitAction(GOAPResult result) {
}

IdleNode::IdleNode(GOAPNode* aiNode)
: GOAPAction("idleNode", 1)
, _aiNode(aiNode)
{
	setPreconditionStates({ { "findEnemy", false}, { "fullHp", false} });
	setEffectStates({ { "fullHp", true } });
};

IdleNode::~IdleNode() {
	_aiNode = nullptr;
}

void IdleNode::onEnterAction() {
	auto scale1 = ScaleTo::create(0.2, 1.2);
	auto scale2 = ScaleTo::create(0.1, 1);
	auto delay = DelayTime::create(0.3);
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->runAction(RepeatForever::create(Sequence::create(scale1, scale2, delay, nullptr)));
}

GOAPResult IdleNode::onUpdateAction(float dt) {
	CCLOG("GOAP IdleNode::onEnterAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->recoverHP(dt);
	if (!_aiNode->notFoundEnemy()) {
		return GOAPResult::GFAIL;
	}
	return _aiNode->getHP() < 100 ? GOAPResult::GRUNNING : GOAPResult::GSUCCESS;
}

void IdleNode::onExitAction(GOAPResult result) {
	_aiNode->stopAllActions();
	_aiNode->setScale(1);
	_aiNode->setRestInterval(10);
}

HPSensor::HPSensor(GOAPNode* aiNode)
: _aiNode(aiNode)
{}

void HPSensor::initSensor(unique_ptr<GOAPWorldState>& worldState) {
	int hp = _aiNode->getHP();
	worldState->addState("alive", hp > 0 ? true : false);
	worldState->addState("inDanger", hp < 20 ? true : false);
	worldState->addState("fullHp", hp == 100 ? true : false);
	worldState->addState("deadDelete", false);
}

void HPSensor::updateSensor(unique_ptr<GOAPWorldState>& worldState) {
	int hp = _aiNode->getHP();
	if (hp > 0) {
		if (worldState->getState("fullHp") != (hp == 100)) {
			worldState->updateState("fullHp", hp == 100);
		}
		if (worldState->getState("inDanger") != (hp < 20)) {
			worldState->updateState("inDanger", hp < 20);
		}
	}
	else {
		if (worldState->getState("alive") == true) {
			worldState->updateState("alive", false);
		}
	}
}

EnemySensor::EnemySensor(GOAPNode* aiNode)
: _aiNode(aiNode)
{}

void EnemySensor::initSensor(unique_ptr<GOAPWorldState>& worldState) {
	worldState->addState("findEnemy", !_aiNode->notFoundEnemy());
	worldState->addState("inAttackRange", _aiNode->inAttackRange());
}

void EnemySensor::updateSensor(unique_ptr<GOAPWorldState>& worldState) {
	if (worldState->getState("findEnemy") == _aiNode->notFoundEnemy()) {
		worldState->updateState("findEnemy", !_aiNode->notFoundEnemy());
	}
	if (worldState->getState("inAttackRange") != _aiNode->inAttackRange()) {
		worldState->updateState("inAttackRange", _aiNode->inAttackRange());
	}
}