#include "HState.h"

HState::HState(int id)
: _id(id)
, _isActived(false)
, _timer(0)
, _parentMachine(nullptr)
{};

HState::~HState(){

}

void HState::onEnter(AINode* aiNode) {
	if (_isActived) return;
	_timer = 0;
	_isActived = true;
	onEnterAction(aiNode);
}

void HState::onExit(AINode* aiNode) {
	if (!_isActived) return;
	_timer = 0;
	_isActived = false;
	onExitAction(aiNode);
}

void HState::onUpdate(float dt, AINode* aiNode) {
	if (!_isActived) return;
	_timer += dt;
	onUpdateAction(dt, aiNode);
}

void HState::setParentMachine(HState* parentMachine) {
	_parentMachine = parentMachine;
}