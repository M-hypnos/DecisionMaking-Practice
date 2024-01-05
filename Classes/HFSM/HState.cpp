#include "HState.h"

HState::HState(int id, AINode* aiNode)
: _id(id)
, _isActived(false)
, _timer(0)
, _aiNode(aiNode)
, _parentMachine(nullptr)
{};

HState::~HState(){

}

void HState::onEnter() {
	if (_isActived) return;
	_timer = 0;
	_isActived = true;
	onEnterAction();
}

void HState::onExit() {
	if (!_isActived) return;
	_timer = 0;
	_isActived = false;
	onExitAction();
}

void HState::onUpdate(float dt) {
	if (!_isActived) return;
	_timer += dt;
	onUpdateAction(dt);
}

void HState::setParentMachine(HState* parentMachine) {
	_parentMachine = parentMachine;
}