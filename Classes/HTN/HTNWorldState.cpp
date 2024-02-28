#include "HTNWorldState.h"

HTNWorldState::HTNWorldState(unordered_map<string, Any> states)
: _states(states),
_isDirty(false)
{}

void HTNWorldState::addState(string key, Any data) {
	if (_states.find(key) != _states.end()) {
		printf("=====>>  repeat add state: %s !\n", key.c_str());
		return;
	}
	_states.emplace(key, data);
}

void HTNWorldState::removeState(string key) {
	_states.erase(key);
}

void HTNWorldState::updateState(string key, Any data) {
	if (_states.find(key) == _states.end()) {
		printf("=====>>  unpadte unexit state: %s !\n", key.c_str());
		return;
	}
	_isDirty = true;
	applyState(key, data);
}

void HTNWorldState::applyState(string key, Any data) {
	_states[key] = data;
}

const Any& HTNWorldState::getState(string key) {
	return _states[key];
}