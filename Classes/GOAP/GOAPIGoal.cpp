#include "GOAPIGoal.h"
#include "GOAPWorldState.h"
#include "GOAPGoalState.h"

GOAPIGoal::GOAPIGoal(std::string name, int priority)
: _name(name)
, _priority(priority)
{}

GOAPIGoal::GOAPIGoal(std::string name, std::unordered_map<std::string, bool>pStates, std::unordered_map<std::string, bool>eStates, int priority)
: _name(name)
, _priority(priority)
, _precondition(pStates)
, _effect(eStates)
{}

void GOAPIGoal::setPreconditionStates(std::unordered_map<std::string, bool>states) {
	_precondition = states;
}
void GOAPIGoal::setEffectStates(std::unordered_map<std::string, bool>states) {
	_effect = states;
}

bool GOAPIGoal::checkPrecondition(const std::unique_ptr<GOAPWorldState>& worldState) {
	return worldState->checkSatisfiedWorldState(_precondition);
}

std::unique_ptr<GOAPGoalState> GOAPIGoal::getGoalState(const std::unique_ptr<GOAPWorldState>& worldState) {
	return std::make_unique<GOAPGoalState>(worldState, _effect);
}