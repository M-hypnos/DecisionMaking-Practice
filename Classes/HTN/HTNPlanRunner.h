#ifndef __HTN_PLAN_RUNNER_H__
#define __HTN_PLAN_RUNNER_H__
#include "HTNPlanner.h"

class HTNPlanRunner
{
public:
	HTNPlanRunner() = delete;
	HTNPlanRunner(shared_ptr<HTNPlanner> planner);
	void onUpdate(float dt, unique_ptr<HTNWorldState>& worldState, shared_ptr<HTNITask> rootTask);
protected:

private:
	void executeTask(float dt, unique_ptr<HTNWorldState>& worldState);
	shared_ptr<HTNPlanner> _planner;
	shared_ptr<HTNPrimitiveTask> _curTask;
};

#endif