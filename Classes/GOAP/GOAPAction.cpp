#include "GOAPAction.h"
#include "GOAPWorldState.h"

GOAPAction::GOAPAction(std::string name, int cost)
: _name(name)
,_cost(cost)
//, _precondition(std::make_unique<GOAPWorldState>())
//, _effect(std::make_unique<GOAPWorldState>())
{}

GOAPAction::GOAPAction(std::string name, std::unordered_map<std::string, bool>pStates, std::unordered_map<std::string, bool>eStates, int cost)
: _name(name)
, _cost(cost)
//, _precondition(std::make_unique<GOAPWorldState>(pStates))
//, _effect(std::make_unique<GOAPWorldState>(eStates))
, _precondition(pStates)
, _effect(eStates)
{
}

void GOAPAction::setPreconditionStates(std::unordered_map<std::string, bool>states) {
	/*for (auto iter : states) {
		_precondition->setState(iter.first, iter.second);
	}*/
	_precondition = states;
}
void GOAPAction::setEffectStates(std::unordered_map<std::string, bool>states) {
	/*for (auto iter : states) {
		_effect->setState(iter.first, iter.second);
	}*/
	_effect = states;
}

bool GOAPAction::checkPrecondition(const std::unique_ptr<GOAPWorldState>& worldState) {
	return worldState->checkSatisfiedWorldState(_precondition);
}

void GOAPAction::effectWorldState(std::unique_ptr<GOAPWorldState>& worldState) {
	for (auto iter : _effect) {
		worldState->applyState(iter.first, iter.second);
	}
}

void GOAPAction::onEnter() {
	if (_isRunning) {
		return;
	}
	_isRunning = true;
	onEnterAction();
}

GOAPResult GOAPAction::onUpdate(float dt) {
	if (!_isRunning) {
		onEnter();
	}
	auto result = onUpdateAction(dt);
	if (result != GOAPResult::GRUNNING) {
		onExit(result);
	}
	return result;
}

void GOAPAction::onExit(GOAPResult result) {
	if (!_isRunning) {
		return;
	}
	_isRunning = false;
	onExitAction(result);
}

void GOAPAction::onInterrupt() {
	onExit(GOAPResult::GINTERRUPT);
}