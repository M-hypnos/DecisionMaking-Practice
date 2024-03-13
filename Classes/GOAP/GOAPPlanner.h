#ifndef __GOAP_PLANNER_H__
#define __GOAP_PLANNER_H__
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stack>
#include <utility>
#include "GOAPGoalState.h"

class GOAPIGoal;
class GOAPWorldState;
class GOAPAction;

struct GOAPAStarNode {
	GOAPAStarNode(std::shared_ptr<GOAPAStarNode> parent, std::unique_ptr<GOAPGoalState> goalState, int cost, std::shared_ptr<GOAPAction> action)
		: goalState_(std::move(goalState)), action_(action), g_(cost){
		if (parent != nullptr) {
			parent_ = parent;
		}
	}
	std::weak_ptr<GOAPAStarNode> parent_;
	std::shared_ptr<GOAPAction> action_;
	std::unique_ptr<GOAPGoalState> goalState_;
	int g_;
};

class GOAPPlanner
{
public:
	bool plan(const std::unique_ptr<GOAPWorldState>& curWorldState, const std::shared_ptr<GOAPIGoal>& goal, std::vector<std::shared_ptr<GOAPAction>> actionSet);
	bool hasPlan() { return !_finalPlan.empty(); }
	auto clearPlan() -> void {
		std::queue<std::shared_ptr<GOAPAction>>().swap(_finalPlan);
	}
	auto getPlanTask() -> std::shared_ptr<GOAPAction> {
		auto task = _finalPlan.front();
		_finalPlan.pop();
		return task;
	}
protected:

private:
	/*bool goalNeedEffect(std::unordered_map<std::string, bool> goalState, std::unordered_map<std::string, bool> effect);*/
	std::vector<std::shared_ptr<GOAPAStarNode>> _openList;
	std::vector<std::shared_ptr<GOAPAStarNode>> _closeList;
	std::queue<std::shared_ptr<GOAPAction>> _finalPlan;
};

#endif