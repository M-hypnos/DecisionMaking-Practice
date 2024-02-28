#include "HTNPrimitiveTask.h"

HTNPrimitiveTask::HTNPrimitiveTask(string name, shared_ptr<HTNPrecondition> precondition)
: HTNITask(name)
,_precondition(precondition)
{}

bool HTNPrimitiveTask::checkPrecondition(const unique_ptr<HTNWorldState>& worldState) {
	if (_precondition) {
		return _precondition->check(worldState);
	}
	return true;
}

void HTNPrimitiveTask::onEnter() {
	if (_isRunning) {
		return;
	}
	_isRunning = true;
	onEnterAction();
}

HTNResult HTNPrimitiveTask::onUpdate(float dt) {
	if (!_isRunning) {
		onEnter();
	}
	auto result = onUpdateAction(dt);
	if (result != HTNResult::HRUNNING) {
		onExit(result);
	}
	return result;
}

void HTNPrimitiveTask::onExit(HTNResult result) {
	if (!_isRunning) {
		return;
	}
	_isRunning = false;
	onExitAction(result);
}

void HTNPrimitiveTask::onInterrupt() {
	onExit(HTNResult::HINTERRUPT);
}