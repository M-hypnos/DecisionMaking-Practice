#include "GOAPGoalState.h"
#include "GOAPWorldState.h"
#include "GOAPAction.h"

GOAPGoalState::GOAPGoalState(const std::unique_ptr<GOAPWorldState>& worldState, std::unordered_map<std::string, bool> effect) {
	for (auto iter : effect) {
		if (iter.second != worldState->getState(iter.first)) {
			_state[iter.first] = iter.second;
			_stateCount[iter.first] = 1;
		}
	}
}

GOAPGoalState::GOAPGoalState(std::unordered_map<std::string, bool> state, std::unordered_map<std::string, int> stateCount)
: _state(state)
, _stateCount(stateCount)
{}

int GOAPGoalState::getHeuristic() {
	int count = 0;
	for (auto iter : _stateCount) {
		count += iter.second;
	}
	return count;
}

bool GOAPGoalState::needAction(std::shared_ptr<GOAPAction> action) {
	auto effect = action->getEffect();
	auto precondition = action->getPrecondition();
	for (auto iter : precondition) {
		if (_state.find(iter.first) != _state.end() && _state[iter.first] != iter.second) {
			if (effect.find(iter.first) == effect.end() || effect[iter.first] != _state[iter.first]) {
				return false;
			}
		}
	}
	bool isRouteAction = false;
	for (auto iter : effect) {
		if (_state.find(iter.first) != _state.end()) {
			if (_state[iter.first] == iter.second) {
				if (_stateCount[iter.first] == 1) {
					_state.erase(iter.first);
					_stateCount.erase(iter.first);
				}
				else {
					_stateCount[iter.first]--;
				}
				isRouteAction = true;
			}
			else {
				return false;
			}
		}
	}
	return isRouteAction;
}

void GOAPGoalState::checkPrecondition(std::shared_ptr<GOAPAction> action, const std::unique_ptr<GOAPWorldState>& worldState) {
	auto precondition = action->getPrecondition();
	for (auto iter : precondition) {
		if (iter.second != worldState->getState(iter.first)) {
			if (_state[iter.first] == iter.second) {
				_stateCount[iter.first]++;
			}
			else {
				_state[iter.first] = iter.second;
				_stateCount[iter.first] = 1;
			}
		}
	}
}