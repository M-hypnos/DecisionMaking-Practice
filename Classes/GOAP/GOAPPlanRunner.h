#ifndef __GOAP_PLAN_RUNNER_H__
#define __GOAP_PLAN_RUNNER_H__

#include <vector>
#include <memory>

class GOAPIGoal;
class GOAPWorldState;
class GOAPPlanner;
class GOAPAction;

class GOAPPlanRunner
{
public:
	GOAPPlanRunner(std::shared_ptr<GOAPPlanner> planner);
	void addGoal(std::shared_ptr<GOAPIGoal> goal);
	void addAction(std::shared_ptr<GOAPAction> action);
	void onUpdate(float dt, std::unique_ptr<GOAPWorldState>& worldState);
protected:

private:
	bool plan(std::unique_ptr<GOAPWorldState>& worldState);
	void executeTask(float dt, std::unique_ptr<GOAPWorldState>& worldState);

	bool _needSortGoal;
	std::shared_ptr<GOAPPlanner> _planner;
	std::vector<std::shared_ptr<GOAPIGoal>> _goalSet;
	std::vector<std::shared_ptr<GOAPAction>> _actionSet;
	std::shared_ptr<GOAPAction> _curAction;
};

#endif