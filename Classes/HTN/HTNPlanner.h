#ifndef __HTN_PLANNER_H__
#define __HTN_PLANNER_H__
#include "HTNWorldState.h"
#include "HTNITask.h"
#include <stack>
#include <queue>
#include "HTNMethod.h"
#include "HTNCompoundTask.h"
#include "HTNPrimitiveTask.h"
using namespace std;

class HTNPlanner;

struct HTNPlannerStatus {
	HTNPlannerStatus() = default;
	HTNPlannerStatus(stack<shared_ptr<HTNITask>> tp, queue<shared_ptr<HTNPrimitiveTask>> fp, unique_ptr<HTNWorldState>& cws, string ntn, int nmi)
		:tasksToPocess(tp), finalPlan(fp), curWorldState(move(cws)), nextTaskName(ntn), nextMethodIdx(nmi){}
	stack<shared_ptr<HTNITask>> tasksToPocess;
	queue<shared_ptr<HTNPrimitiveTask>> finalPlan;
	unique_ptr<HTNWorldState> curWorldState;
	string nextTaskName;
	int nextMethodIdx;
	auto clone()-> unique_ptr<HTNPlannerStatus> {
		return make_unique<HTNPlannerStatus>(tasksToPocess, finalPlan, curWorldState->clone(), nextTaskName, nextMethodIdx);
	}
};

class HTNPlanner
{
public:
	bool plan(const unique_ptr<HTNWorldState>& worldState, shared_ptr<HTNITask> rootTask);
	bool hasPlan() { return !_finalPlan.empty(); }
	auto getPlanTask() -> shared_ptr<HTNPrimitiveTask> {
		auto task = _finalPlan.front();
		_finalPlan.pop();
		return task;
	}
	auto clearPlan() -> void {
		queue<shared_ptr<HTNPrimitiveTask>>().swap(_finalPlan);
	}
protected:

private:
	queue<shared_ptr<HTNPrimitiveTask>> _finalPlan;
};

#endif