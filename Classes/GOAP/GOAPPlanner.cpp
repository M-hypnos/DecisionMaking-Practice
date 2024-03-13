#include "GOAPPlanner.h"
#include "GOAPIGoal.h"
#include "GOAPWorldState.h"
#include "GOAPAction.h"
#include<algorithm>


bool cmp(std::shared_ptr<GOAPAStarNode> x, std::shared_ptr<GOAPAStarNode> y)
{
	return x->g_ + x->goalState_->getHeuristic() > y->g_ + y->goalState_->getHeuristic();
}

bool GOAPPlanner::plan(const std::unique_ptr<GOAPWorldState>& curWorldState, const std::shared_ptr<GOAPIGoal>& goal, std::vector<std::shared_ptr<GOAPAction>> actionSet) {
	_openList.clear();
	_closeList.clear();
	clearPlan();
	auto goalState = goal->getGoalState(curWorldState);
	auto node = std::make_shared<GOAPAStarNode>(nullptr, std::move(goalState), 0, nullptr);
	_openList.push_back(node);
	while (!_openList.empty()) {
		auto curNode = _openList[_openList.size() - 1];
		_openList.pop_back();
		_closeList.push_back(curNode);

		if (curNode->goalState_->isFinish()) {
			while (curNode != nullptr && curNode->action_ != nullptr) {
				_finalPlan.push(curNode->action_);
				curNode = curNode->parent_.lock();
			}
			return true;
		}
		if (curNode->action_ != nullptr) {
			printf("a* curNode act:  %s \n", curNode->action_->getName().c_str());
		}
		for (auto action : actionSet) {
			auto newGoal = curNode->goalState_->clone();
			bool isRouteAction = newGoal->needAction(action);
			if (isRouteAction) {
				printf("============== >> route action   %s \n", action->getName().c_str());
				newGoal->checkPrecondition(action, curWorldState);
				if (std::find_if(_closeList.begin(), _closeList.end(), [&](std::shared_ptr<GOAPAStarNode> gnode) {return gnode->goalState_ == newGoal; }) == _closeList.end()) {
					auto iter = std::find_if(_openList.begin(), _openList.end(), [&](std::shared_ptr<GOAPAStarNode> gnode) {return gnode->goalState_ == newGoal; });
					if (iter == _openList.end()) {
						auto childNode = std::make_shared<GOAPAStarNode>(curNode, std::move(newGoal), action->getCost() + curNode->g_, action);
						_openList.push_back(childNode);
					}
					else if ((*iter)->g_ > action->getCost() + curNode->g_) {
						(*iter)->parent_ = curNode;
						(*iter)->g_ = action->getCost() + curNode->g_;
						(*iter)->action_ = action;
					}
				}
			}
		}
		
		std::sort(_openList.begin(), _openList.end(), cmp);
	}
	return false;
}