#include "FSM.h"

FSM::FSM()
: _curState(nullptr)
, _lastState(nullptr)
{

}

FSM::~FSM() {
	_allStates.clear();
}

void FSM::onAction(float dt) {
	if (_curState == nullptr) return;
	int newStateId = _curState->checkChangeState(dt);
	if (newStateId >= 0) changeState(newStateId);

	_curState->onUpdate(dt);
}

void FSM::invokeFSM() {
	if (_allStates.empty()) return;
	if (_curState != nullptr) return;
	_curState = (*_allStates.begin()).second;
	_curState->onEnter();
}

void FSM::invokeFSM(int stateId) {
	if (_allStates.empty()) return;
	if (_curState != nullptr) return;
	if (_allStates.find(stateId) == _allStates.end()) return;
	_curState = _allStates[stateId];
	_curState->onEnter();
}

void FSM::changeState(int stateId) {
	if (_allStates.find(stateId) == _allStates.end()) return;
	if(*_curState != *_allStates[stateId]){
		_curState->onExit();
		_lastState = _curState;
		_curState = _allStates[stateId];
		_curState->onEnter();
	}
}

void FSM::addState(BaseState* state) {
	int stateId = state->getStateId();
	if (_allStates.find(stateId) != _allStates.end()) {
		CCLOG("add same state %d", stateId);
		return;
	}
	_allStates.emplace(stateId, state);
}

BaseState* FSM::removeState(int stateId) {
	if (_allStates.find(stateId) == _allStates.end()) {
		CCLOG("remove unexited state %d", stateId);
		return nullptr;
	}
	BaseState* temp = _allStates[stateId];
	_allStates.erase(stateId);
	return temp;
}