#include "HFSM.h"

HFSM::HFSM(int stateId)
: HState(stateId)
, _curState(nullptr)
, _lastState(nullptr)
, _defalutStateId(-1)
, _sortTans(false)
{

}

HFSM::~HFSM() {
	for (auto tran : _trans) {
		delete tran;
	}
	_trans.clear();
	for (auto tran : _enterTrans) {
		delete tran;
	}
	_enterTrans.clear();
	for (auto state : _allStates) {
		delete state.second;
	}
	_allStates.clear();
	_curState = nullptr;
	_lastState = nullptr;
}

void HFSM::onEnterAction(AINode* aiNode) {
	//CCLOG("HFSM::onEnterAction %d ", getStateId());
	if (_allStates.empty()) {
		CCLOG("=======>> warn: no sub state  %d ", getStateId());
		return;
	}
	if (_curState != nullptr) {
		CCLOG("=======>> warn: enter active HFSM  %d ", getStateId());
		return;
	}
	int stateId = getEnterState(aiNode);
	if (stateId < 0) {
		CCLOG("=======>> error: can not enter HFSM  %d ", getStateId());
		return;
	}
	_curState = _allStates[stateId];
	_curState->onEnter(aiNode);
}

void HFSM::onExitAction(AINode* aiNode) {
	if (_curState == nullptr) return;
	_curState->onExit(aiNode);
	_curState = nullptr;
	//CCLOG("HFSM::onExitAction  %d ", getStateId());
}

void HFSM::onUpdateAction(float dt, AINode* aiNode) {
	if (_curState == nullptr) {
		CCLOG("=======>> warn: no active state HFSM  %d ", getStateId());
		return;
	}
	//CCLOG("HFSM::onUpdateAction %d ", getStateId());
	int stateId = getUpdateState(aiNode);
	if (stateId < 0) {
		CCLOG("=======>> error: can not update HFSM  %d ", getStateId());
		return;
	}
	if (*_curState == *_allStates[stateId]) {
		_curState->onUpdate(dt, aiNode);
	}
	else {
		_curState->onExit(aiNode);
		_lastState = _curState;
		_curState = _allStates[stateId];
		_curState->onEnter(aiNode);
	}
}

void HFSM::onUpdate(float dt, AINode* aiNode) {
	if (!isRootMachine()) return;
	HState::onUpdate(dt, aiNode);
}

void HFSM::invokeHFSM(AINode* aiNode) {
	if (!isRootMachine()) return;
	int stateId = getEnterState(aiNode);
	if (stateId < 0) return;
	_isActived = true;
	_curState = _allStates[stateId];
	_curState->onEnter(aiNode);
}

int HFSM::getUpdateState(AINode* aiNode) {
	if (!_sortTans) {
		_sortTans = true;
		sort(_trans.begin(), _trans.end(), [&](const HTransition* a, const HTransition* b)->bool { return a->getWeight() > b->getWeight(); });
		sort(_enterTrans.begin(), _enterTrans.end(), [&](const HTransition* a, const HTransition* b)->bool { return a->getWeight() > b->getWeight(); });
	}
	for (auto tran : _trans) {
		bool isCurStateTrans = _curState->getStateId() == tran->getFromStateId();
		if (isCurStateTrans && tran->checkChangeState(aiNode, _timer)) {
			return tran->getToStateId();
		}
	}
	return _curState->getStateId();
}

int HFSM::getEnterState(AINode* aiNode) {
	if (!_sortTans) {
		_sortTans = true;
		sort(_trans.begin(), _trans.end(), [&](const HTransition* a, const HTransition* b)->bool { return a->getWeight() > b->getWeight(); });
		sort(_enterTrans.begin(), _enterTrans.end(), [&](const HTransition* a, const HTransition* b)->bool { return a->getWeight() > b->getWeight(); });
	}
	for (auto tran : _enterTrans) {
		bool isCurStateTrans = _id == tran->getFromStateId();
		if (isCurStateTrans && tran->checkChangeState(aiNode, _timer)) {
			return tran->getToStateId();
		}
	}
	if (_allStates.find(_defalutStateId) != _allStates.end()) return _defalutStateId;
	return -1;
}

void HFSM::addState(HState* state) {
	if (state->getParentMachine() != nullptr) return;
	int stateId = state->getStateId();
	if (_allStates.find(stateId) != _allStates.end()) {
		CCLOG("add same state %d", stateId);
		return;
	}
	_allStates.emplace(stateId, state);
}

HTransition* HFSM::addState(HState* state, bool addTrans) {
	if (state->getParentMachine() != nullptr) return nullptr;
	int stateId = state->getStateId();
	if (_allStates.find(stateId) != _allStates.end()) {
		CCLOG("add same state %d", stateId);
		return nullptr;
	}
	_allStates.emplace(stateId, state);
	_sortTans = false;
	if (addTrans) {
		HTransition* tran = new HTransition(_id, stateId);
		_enterTrans.push_back(tran);
		return tran;
	}
	else {
		return nullptr;
	}
}

HState* HFSM::removeState(int stateId) {
	if (_allStates.find(stateId) == _allStates.end()) {
		CCLOG("remove unexited state %d", stateId);
		return nullptr;
	}
	HState* temp = _allStates[stateId];
	_allStates.erase(stateId);

	for (auto iter = _trans.begin(); iter != _trans.end();) {
		if ((*iter)->getFromStateId() == stateId || (*iter)->getToStateId() == stateId) {
			iter = _trans.erase(iter);
		}
		else {
			iter++;
		}
	}
	for (auto iter = _enterTrans.begin(); iter != _enterTrans.end();) {
		if ( (*iter)->getToStateId() == stateId) {
			iter = _enterTrans.erase(iter);
		}
		else {
			iter++;
		}
	}

	return temp;
}

HTransition* HFSM::addTransition(int fromStateId, int toStateId) {
	if (_allStates.find(fromStateId) == _allStates.end()) {
		CCLOG("add unexited subState transition %d", fromStateId);
		return nullptr;
	}
	if (_allStates.find(toStateId) == _allStates.end()) {
		CCLOG("add unexited subState transition %d", toStateId);
		return nullptr;
	}

	_sortTans = false;
	HTransition* tran = new HTransition(fromStateId, toStateId);
	_trans.push_back(tran);
	return tran;
}