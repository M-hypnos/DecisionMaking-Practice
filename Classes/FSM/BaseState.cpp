#include "BaseState.h"

BaseState::BaseState(int id, AINode* aiNode)
: _id(id)
, _isActived(false)
, _timer(0)
, _aiNode(aiNode)
{};

BaseState::~BaseState(){
	for (auto tran : _trans) {
		delete tran;
	}
	_trans.clear();
}

void BaseState::onEnter() {
	if (_isActived) return;
	_timer = 0;
	_isActived = true;
	onEnterAction();
}

void BaseState::onExit() {
	if (!_isActived) return;
	_timer = 0;
	_isActived = false;
	onExitAction();
}

void BaseState::onUpdate(float dt) {
	if (!_isActived) return;
	_timer += dt;
	onUpdateAction(dt);
}

Transition* BaseState::addTransition(int toStateId) {
	Transition* tran = new Transition(toStateId);
	_trans.push_back(tran);
	return tran;
}

int BaseState::checkChangeState() {
	if (!_isActived)  return -1;
	for (auto tran : _trans) {
		if (tran->checkChangeState(_aiNode, _timer)) {
			return tran->getToStateId();
		}
	}
	return -1;
}