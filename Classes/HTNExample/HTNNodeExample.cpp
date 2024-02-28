#include "HTNNodeExample.h"

using namespace HTNNodeExampleSpace;

AttackNode::AttackNode(HTNNode* aiNode)
: HTNPrimitiveTask("attackNode")
,_aiNode(aiNode)
{};

AttackNode::~AttackNode() {
	_aiNode = nullptr;
}

void AttackNode::effectWorldState(unique_ptr<HTNWorldState>& worldState) {

}

void AttackNode::onEnterAction() {
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->stopORCA();
}

HTNResult AttackNode::onUpdateAction(float dt) {
	//CCLOG("HTN AttackNode::onUpdateAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	return _aiNode->htnAttack();
}

void AttackNode::onExitAction(HTNResult result) {
	_aiNode->resumeORCA();
	_aiNode->stopAttack();
}

DeadNode::DeadNode(HTNNode* aiNode)
: HTNPrimitiveTask("deadNode")
, _aiNode(aiNode)
{};

DeadNode::~DeadNode() {
	_aiNode = nullptr;
}

void DeadNode::effectWorldState(unique_ptr<HTNWorldState>& worldState) {
	
}

void DeadNode::onEnterAction() {
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->stopORCA();
	_aiNode->setDead();
}

HTNResult DeadNode::onUpdateAction(float dt) {
	//CCLOG("HTN DeadNode::onUpdateAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->addDeadTime(dt);
	return HTNResult::HRUNNING;
}

void DeadNode::onExitAction(HTNResult result) {
	_aiNode->resumeORCA();
}

WanderNode::WanderNode(HTNNode* aiNode)
: HTNPrimitiveTask("wanderNode")
, _aiNode(aiNode)
{};

WanderNode::~WanderNode() {
	_aiNode = nullptr;
}


void WanderNode::effectWorldState(unique_ptr<HTNWorldState>& worldState) {
	worldState->applyState("findEnemy", true);
}

void WanderNode::onEnterAction() {
}

HTNResult WanderNode::onUpdateAction(float dt) {
	//CCLOG("HTN WanderNode::onUpdateAction  ");
	_aiNode->wander(dt);
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	return _aiNode->notFoundEnemy() ? HTNResult::HRUNNING : HTNResult::HSUCCESS;
}

void WanderNode::onExitAction(HTNResult result) {
}

PursuitNode::PursuitNode(HTNNode* aiNode)
: HTNPrimitiveTask("pursuitNode")
, _aiNode(aiNode)
{};

PursuitNode::~PursuitNode() {
	_aiNode = nullptr;
}

void PursuitNode::effectWorldState(unique_ptr<HTNWorldState>& worldState) {
	worldState->applyState("inAttackRange", true);
}

void PursuitNode::onEnterAction() {
}

HTNResult PursuitNode::onUpdateAction(float dt) {
	//CCLOG("HTN PursuitNode::onUpdateAction  ");

	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	return _aiNode->htnPursuit(dt);
}

void PursuitNode::onExitAction(HTNResult result) {
}

EvadingNode::EvadingNode(HTNNode* aiNode)
: HTNPrimitiveTask("evadingNode")
, _aiNode(aiNode)
{};

EvadingNode::~EvadingNode() {
	_aiNode = nullptr;
}

void EvadingNode::effectWorldState(unique_ptr<HTNWorldState>& worldState) {
	worldState->applyState("findEnemy", false);
}

void EvadingNode::onEnterAction() {
}

HTNResult EvadingNode::onUpdateAction(float dt) {
	//CCLOG("HTN EvadingNode::onUpdateAction  ");
	_aiNode->setRestInterval(_aiNode->getRestInterval() - dt);
	return _aiNode->htnEvading(dt);
}

void EvadingNode::onExitAction(HTNResult result) {
}

IdleNode::IdleNode(HTNNode* aiNode)
: HTNPrimitiveTask("idleNode")
, _aiNode(aiNode)
{};

IdleNode::~IdleNode() {
	_aiNode = nullptr;
}

void IdleNode::effectWorldState(unique_ptr<HTNWorldState>& worldState) {
	worldState->applyState("fullHp", true);
}

void IdleNode::onEnterAction() {
	auto scale1 = ScaleTo::create(0.2, 1.2);
	auto scale2 = ScaleTo::create(0.1, 1);
	auto delay = DelayTime::create(0.3);
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->runAction(RepeatForever::create(Sequence::create(scale1, scale2, delay, nullptr)));
}

HTNResult IdleNode::onUpdateAction(float dt) {
	//CCLOG("HTN IdleNode::onEnterAction  ");
	_aiNode->setVelocity(Vec2::ZERO);
	_aiNode->recoverHP(dt);
	if (_aiNode->getHP() >= 20) _aiNode->updateWorldState("inDanger", false);
	if (!_aiNode->notFoundEnemy()) {
		return HTNResult::HFAIL;
	}
	return _aiNode->getHP() < 100 ? HTNResult::HRUNNING : HTNResult::HSUCCESS;
}

void IdleNode::onExitAction(HTNResult result) {
	_aiNode->stopAllActions();
	_aiNode->setScale(1);
	_aiNode->setRestInterval(10);
}