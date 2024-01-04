#include "FSM.h"

FSM::FSM()
: _curState(nullptr)
, _lastState(nullptr)
{

}

FSM::~FSM() {
	_allStates.clear();
}

void FSM::onUpdate(float dt) {
	if (_curState == nullptr) return;
	_curState->onUpdate(dt);

	int newStateId = _curState->checkChangeState();
	if (newStateId >= 0) changeState(newStateId);
}

void FSM::changeState(int stateId) {
	if (_allStates.find(stateId) == _allStates.end()) return;
	if (_curState == nullptr) {
		_curState = _allStates[stateId];
		_curState->onEnter();
	}
	else if(*_curState != *_allStates[stateId]){
		_curState->onExit();
		_lastState = _curState;
		_curState = _allStates[stateId];
		_curState->onEnter();
	}
}

void FSM::addState(BaseState* state) {
	int stateId = state->getStateId();
	if (_allStates.find(stateId) != _allStates.end()) {
		printf("add same state %d", stateId);
		return;
	}
	_allStates.emplace(stateId, state);
}

BaseState* FSM::removeState(int stateId) {
	if (_allStates.find(stateId) == _allStates.end()) {
		printf("remove unexited state %d", stateId);
		return nullptr;
	}
	BaseState* temp = _allStates[stateId];
	_allStates.erase(stateId);
	return temp;
}