#include "GOAPWorldState.h"

GOAPWorldState::GOAPWorldState()
: _isDirty(false)
{}

GOAPWorldState::GOAPWorldState(const std::unordered_map<std::string, bool>& stateMap)
: _stateMap(stateMap)
{}

GOAPWorldState::GOAPWorldState(const GOAPWorldState& worldState)
: _stateMap(worldState._stateMap)
, _isDirty(worldState._isDirty)
{}

void GOAPWorldState::addState(std::string name, bool value) {
	if (_stateMap.find(name) != _stateMap.end()) {
		printf("=====>>  repeat add state: %s !\n", name.c_str());
		return;
	}
	_stateMap.emplace(name, value);
}

void GOAPWorldState::removeState(std::string name) {
	_stateMap.erase(name);
}

void GOAPWorldState::updateState(std::string name, bool value)
{
	if (_stateMap.find(name) == _stateMap.end()) {
		printf("=====>>  unpadte unexit state: %s !\n", name.c_str());
		return;
	}
	_isDirty = true;
	applyState(name, value);
}

void GOAPWorldState::applyState(std::string name, bool value) {
	_stateMap[name] = value;
}

//bool GOAPWorldState::checkSatisfiedWorldState(const std::unique_ptr<GOAPWorldState>& worldState) {
//	std::unordered_map<std::string, bool> stateMap = worldState->getStates();
//	for (auto iter : stateMap) {
//		if (_stateMap[iter.first] != iter.second) {
//			return false;
//		}
//	}
//	return true;
//}

bool GOAPWorldState::checkSatisfiedWorldState(const std::unordered_map<std::string, bool> stateMap) {
	for (auto iter : stateMap) {
		if (_stateMap[iter.first] != iter.second) {
			return false;
		}
	}
	return true;
}