#include "GOAPNodeTest.h"

using namespace GOAPNodeTestSpace;

ChopTree::ChopTree(GOAPTestNode* aiNode)
: GOAPAction("ChopTree", 2)
,_aiNode(aiNode)
{
	setPreconditionStates({{ "hasWood", false }});
	setEffectStates({ { "hasWood", true } });
};

ChopTree::~ChopTree() {
	_aiNode = nullptr;
}

void ChopTree::onEnterAction() {
	CCLOG("GOAP ChopTree::onEnterAction  ");
}

GOAPResult ChopTree::onUpdateAction(float dt) {
	CCLOG("GOAP ChopTree::onUpdateAction  ");
	return GOAPResult::GSUCCESS;
}

void ChopTree::onExitAction(GOAPResult result) {
	CCLOG("GOAP ChopTree::onExitAction  ");
}

BuyTree::BuyTree(GOAPTestNode* aiNode)
	: GOAPAction("BuyTree", 1)
	, _aiNode(aiNode)
{
	setPreconditionStates({ { "hasWood", false } });
	setEffectStates({ { "hasWood", true } });
};

BuyTree::~BuyTree() {
	_aiNode = nullptr;
}

void BuyTree::onEnterAction() {
	CCLOG("GOAP BuyTree::onEnterAction  ");
}

GOAPResult BuyTree::onUpdateAction(float dt) {
	CCLOG("GOAP BuyTree::onUpdateAction  ");
	return GOAPResult::GSUCCESS;
}

void BuyTree::onExitAction(GOAPResult result) {
	CCLOG("GOAP BuyTree::onExitAction  ");
}

MineOre::MineOre(GOAPTestNode* aiNode)
	: GOAPAction("MineOre", 10)
	, _aiNode(aiNode)
{
	setPreconditionStates({ { "hasOre", false } });
	setEffectStates({ { "hasOre", true } });
};

MineOre::~MineOre() {
	_aiNode = nullptr;
}

void MineOre::onEnterAction() {
	CCLOG("GOAP MineOre::onEnterAction  ");
}

GOAPResult MineOre::onUpdateAction(float dt) {
	CCLOG("GOAP MineOre::onUpdateAction  ");
	return GOAPResult::GSUCCESS;
}

void MineOre::onExitAction(GOAPResult result) {
	CCLOG("GOAP MineOre::onExitAction  ");
}

WorksWood::WorksWood(GOAPTestNode* aiNode)
	: GOAPAction("WorksWood", 5)
	, _aiNode(aiNode)
{
	setPreconditionStates({ { "hasWood", true } });
	setEffectStates({ { "hasWood", false },{"hasWorkWood", true} });
};

WorksWood::~WorksWood() {
	_aiNode = nullptr;
}

void WorksWood::onEnterAction() {
	CCLOG("GOAP WorksWood::onEnterAction  ");
}

GOAPResult WorksWood::onUpdateAction(float dt) {
	CCLOG("GOAP WorksWood::onUpdateAction  ");
	return GOAPResult::GSUCCESS;
}

void WorksWood::onExitAction(GOAPResult result) {
	CCLOG("GOAP WorksWood::onExitAction  ");
}

SmeltOre::SmeltOre(GOAPTestNode* aiNode)
	: GOAPAction("SmeltOre", 10)
	, _aiNode(aiNode)
{
	setPreconditionStates({ { "hasOre", true } });
	setEffectStates({ { "hasOre", false },{"hasSmeltOre", true} });
};

SmeltOre::~SmeltOre() {
	_aiNode = nullptr;
}

void SmeltOre::onEnterAction() {
	CCLOG("GOAP SmeltOre::onEnterAction  ");
}

GOAPResult SmeltOre::onUpdateAction(float dt) {
	CCLOG("GOAP SmeltOre::onUpdateAction  ");
	return GOAPResult::GSUCCESS;
}

void SmeltOre::onExitAction(GOAPResult result) {
	CCLOG("GOAP SmeltOre::onExitAction  ");
}

CreateAxe::CreateAxe(GOAPTestNode* aiNode)
	: GOAPAction("CreateAxe", 10)
	, _aiNode(aiNode)
{
	setPreconditionStates({ { "hasSmeltOre", true },{ "hasWorkWood", true }, {"hasAxe", false}});
	setEffectStates({ { "hasSmeltOre", false },{ "hasWorkWood", false }, {"hasAxe", true} });
};

CreateAxe::~CreateAxe() {
	_aiNode = nullptr;
}

void CreateAxe::onEnterAction() {
	CCLOG("GOAP CreateAxe::onEnterAction  ");
}

GOAPResult CreateAxe::onUpdateAction(float dt) {
	CCLOG("GOAP CreateAxe::onUpdateAction  ");
	return GOAPResult::GSUCCESS;
}

void CreateAxe::onExitAction(GOAPResult result) {
	CCLOG("GOAP CreateAxe::onExitAction  ");
}



WoodSensor::WoodSensor(GOAPTestNode* aiNode)
: _aiNode(aiNode)
{}

void WoodSensor::initSensor(unique_ptr<GOAPWorldState>& worldState) {
	/*int hp = _aiNode->getHP();
	worldState->addState("alive", Any(hp > 0 ? true : false));
	worldState->addState("inDanger", Any(hp < 20 ? true : false));
	worldState->addState("fullHp", Any(hp == 100 ? true : false));*/
	worldState->addState("hasWood", false);
	worldState->addState("hasWorkWood", false);
}

void WoodSensor::updateSensor(unique_ptr<GOAPWorldState>& worldState) {
	/*int hp = _aiNode->getHP();
	if (hp > 0) {
		if (any_cast<bool>(worldState->getState("fullHp")) != (hp == 100)) {
			worldState->updateState("fullHp", hp == 100);
		}
		if (any_cast<bool>(worldState->getState("inDanger")) != (hp < 20)) {
			worldState->updateState("inDanger", hp < 20);
		}
	}
	else {
		if (any_cast<bool>(worldState->getState("alive")) == true) {
			worldState->updateState("alive", false);
		}
	}*/
}

OreSensor::OreSensor(GOAPTestNode* aiNode)
: _aiNode(aiNode)
{}

void OreSensor::initSensor(unique_ptr<GOAPWorldState>& worldState) {
	/*worldState->addState("findEnemy", !_aiNode->notFoundEnemy());
	worldState->addState("inAttackRange", _aiNode->inAttackRange());*/
	worldState->addState("hasOre", false);
	worldState->addState("hasSmeltOre", false);
}

void OreSensor::updateSensor(unique_ptr<GOAPWorldState>& worldState) {
	/*if (any_cast<bool>(worldState->getState("findEnemy")) == _aiNode->notFoundEnemy()) {
		worldState->updateState("findEnemy", !_aiNode->notFoundEnemy());
	}
	if (any_cast<bool>(worldState->getState("inAttackRange")) != _aiNode->inAttackRange()) {
		worldState->updateState("inAttackRange", _aiNode->inAttackRange());
	}*/
}

AxeSensor::AxeSensor(GOAPTestNode* aiNode)
	: _aiNode(aiNode)
{}

void AxeSensor::initSensor(unique_ptr<GOAPWorldState>& worldState) {
	worldState->addState("hasAxe", false);
	worldState->addState("greedy", true);
}

void AxeSensor::updateSensor(unique_ptr<GOAPWorldState>& worldState) {

}