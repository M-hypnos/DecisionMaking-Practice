#ifndef __GOAP_GOAL_STATE_H__
#define __GOAP_GOAL_STATE_H__
#include  <memory>
#include <unordered_map>

class GOAPWorldState;
class GOAPAction;

class GOAPGoalState
{
public:
	GOAPGoalState(const std::unique_ptr<GOAPWorldState>& worldState, std::unordered_map<std::string, bool> effect);
	GOAPGoalState(std::unordered_map<std::string, bool> state, std::unordered_map<std::string, int> stateCount);
	int getHeuristic();
	bool needAction(std::shared_ptr<GOAPAction> action);
	void checkPrecondition(std::shared_ptr<GOAPAction> action, const std::unique_ptr<GOAPWorldState>& worldState);
	auto isFinish() -> bool {
		return _state.empty();
	}
	auto clone() -> std::unique_ptr<GOAPGoalState> {
		return std::make_unique<GOAPGoalState>(_state, _stateCount);
	}
	auto operator==(const GOAPGoalState& rhs) -> bool {
		return _state == rhs._state && _stateCount == rhs._stateCount;
	}
protected:

private:
	std::unordered_map<std::string, bool> _state;
	std::unordered_map<std::string, int> _stateCount;
};

#endif