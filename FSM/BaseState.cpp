#include "BaseState.h"

BaseState::BaseState(int id)
: _id(id)
, _isActived(false)
, _timer(0)
, _checkTimer(0)
, _checkIntervel(-1)
, _sortTans(false)
{};

BaseState::~BaseState(){
	for (auto tran : _trans) {
		delete tran;
	}
	_trans.clear();
}

void BaseState::onEnter(AINode* aiNode) {
	if (_isActived) return;
	_timer = 0;
	_checkTimer = 0;
	_isActived = true;
	onEnterAction(aiNode);
}

void BaseState::onExit(AINode* aiNode) {
	if (!_isActived) return;
	_timer = 0;
	_isActived = false;
	onExitAction(aiNode);
}

void BaseState::onUpdate(float dt, AINode* aiNode) {
	if (!_isActived) return;
	_timer += dt;
	onUpdateAction(dt, aiNode);
}

Transition* BaseState::addTransition(int toStateId) {
	Transition* tran = new Transition(toStateId);
	_trans.push_back(tran);
	_sortTans = false;
	return tran;
}

int BaseState::checkChangeState(float dt, AINode* aiNode) {
	if (!_isActived)  return -1;
	if (_checkTimer < _checkIntervel) {
		_checkTimer += dt;
		return -1;
	}
	_checkTimer = 0;
	if (!_sortTans) {
		_sortTans = true;
		sort(_trans.begin(), _trans.end(), [&](const Transition* a, const Transition* b)->bool { return a->getWeight() > b->getWeight(); });
	}
	for (auto tran : _trans) {
		if (tran->checkChangeState(aiNode, _timer)) {
			return tran->getToStateId();
		}
	}
	return -1;
}