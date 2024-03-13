#include "GOAPPlanRunner.h"
#include "GOAPIGoal.h"
#include "GOAPWorldState.h"
#include "GOAPPlanner.h"
#include <algorithm>
#include "GOAPAction.h"
#include "AIEnum.h"

GOAPPlanRunner::GOAPPlanRunner(std::shared_ptr<GOAPPlanner> planner)
: _planner(planner)
, _needSortGoal(false)
{}

void GOAPPlanRunner::addGoal(std::shared_ptr<GOAPIGoal> goal) {
	_goalSet.push_back(goal);
	_needSortGoal = true;
}

void GOAPPlanRunner::addAction(std::shared_ptr<GOAPAction> action) {
	_actionSet.push_back(action);
}

void GOAPPlanRunner::onUpdate(float dt, std::unique_ptr<GOAPWorldState>& worldState) {
	if (worldState->isDirty()) {
		worldState->clearDirty();
		if (_curAction) {
			_curAction->onExit(GOAPResult::GINTERRUPT);
			_curAction = nullptr;
		}
		if (plan(worldState)) {
			executeTask(dt, worldState);
		}
		return;
	}
	if (_planner->hasPlan()) {
		executeTask(dt, worldState);
		return;
	}
	if (plan(worldState)) {
		executeTask(dt, worldState);
	}
}

bool GOAPPlanRunner::plan(std::unique_ptr<GOAPWorldState>& worldState) {
	if (_needSortGoal) {
		_needSortGoal = false;
		std::sort(_goalSet.begin(), _goalSet.end(), [](std::shared_ptr<GOAPIGoal> goalA, std::shared_ptr<GOAPIGoal> goalB) {
			return goalA->getPriority() > goalB->getPriority();
		});
	}
	for (auto goal : _goalSet) {
		if (goal->checkPrecondition(worldState)) {
			printf("=======>>  plan goal %s", goal->getName().c_str());
			if (_planner->plan(worldState, goal, _actionSet)) {
				return true;
			}
		}
	}
	return false;
}

void GOAPPlanRunner::executeTask(float dt, std::unique_ptr<GOAPWorldState>& worldState) {
	if (_curAction && !_curAction->checkPrecondition(worldState)) {
		_curAction->onInterrupt();
		_curAction = nullptr;
		_planner->clearPlan();
		return;
	}

	if (_curAction == nullptr) {
		_curAction = _planner->getPlanTask();
	}

	switch (_curAction->onUpdate(dt))
	{
	case GOAPResult::GSUCCESS:
		_curAction->effectWorldState(worldState);
		_curAction = nullptr;
		break;
	case GOAPResult::GFAIL:
		_curAction = nullptr;
		_planner->clearPlan();
		break;
	case GOAPResult::GRUNNING:
		break;
	default:
		_curAction = nullptr;
		_planner->clearPlan();
		break;
	}
}