#include "HTNPlanRunner.h"

HTNPlanRunner::HTNPlanRunner(shared_ptr<HTNPlanner> planner)
: _planner(planner)
{}

void HTNPlanRunner::onUpdate(float dt, unique_ptr<HTNWorldState>& worldState, shared_ptr<HTNITask> rootTask) {
	if (worldState->isDirty()) {
		worldState->clearDirty();
		if (_curTask) {
			_curTask->onExit(HTNResult::HINTERRUPT);
			_curTask = nullptr;
		}
		if (_planner->plan(worldState, rootTask)) {
			executeTask(dt, worldState);
		}
		return;
	}
	if (_planner->hasPlan()) {
		executeTask(dt, worldState);
		return;
	}

	if (_planner->plan(worldState, rootTask)) {
		executeTask(dt, worldState);
	}
}

void HTNPlanRunner::executeTask(float dt, unique_ptr<HTNWorldState>& worldState) {
	if (_curTask && !_curTask->checkPrecondition(worldState)) {
		_curTask->onInterrupt();
		_curTask = nullptr;
		_planner->clearPlan();
		return;
	}

	if (_curTask == nullptr) {
		_curTask = _planner->getPlanTask();
	}

	switch (_curTask->onUpdate(dt))
	{
	case HTNResult::HSUCCESS:
		_curTask->effectWorldState(worldState);
		_curTask = nullptr;
		break;
	case HTNResult::HFAIL:
		_curTask = nullptr;
		_planner->clearPlan();
		break;
	case HTNResult::HRUNNING:
		break;
	default:
		_curTask = nullptr;
		_planner->clearPlan();
		break;
	}
}