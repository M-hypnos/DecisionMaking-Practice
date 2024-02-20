#include "FSM.h"

FSM::FSM()
: _curState(nullptr)
, _lastState(nullptr)
{

}

FSM::~FSM() {
	for (auto state : _allStates) {
		delete state.second;
	}
	_allStates.clear();
	_curState = nullptr;
	_lastState = nullptr;
}

void FSM::onUpdate(float dt, AINode* aiNode) {
	if (_curState == nullptr) return;
	int newStateId = _curState->checkChangeState(dt, aiNode);
	if (newStateId >= 0) changeState(newStateId, aiNode);

	_curState->onUpdate(dt, aiNode);
}

void FSM::invokeFSM(AINode* aiNode) {
	if (_allStates.empty()) return;
	if (_curState != nullptr) return;
	_curState = (*_allStates.begin()).second;
	_curState->onEnter(aiNode);
}

void FSM::invokeFSM(int stateId, AINode* aiNode) {
	if (_allStates.empty()) return;
	if (_curState != nullptr) return;
	if (_allStates.find(stateId) == _allStates.end()) return;
	_curState = _allStates[stateId];
	_curState->onEnter(aiNode);
}

void FSM::changeState(int stateId, AINode* aiNode) {
	if (_allStates.find(stateId) == _allStates.end()) return;
	if(*_curState != *_allStates[stateId]){
		_curState->onExit(aiNode);
		_lastState = _curState;
		_curState = _allStates[stateId];
		_curState->onEnter(aiNode);
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