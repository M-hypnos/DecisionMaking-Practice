#ifndef __GOAP_IGOAL_H__
#define __GOAP_IGOAL_H__
#include <unordered_map>
#include <memory>
#include <stack>

class GOAPWorldState;
class GOAPGoalState;
class GOAPIGoal
{
public:
	GOAPIGoal() = delete;
	GOAPIGoal(std::string name, int priority = 0);
	GOAPIGoal(std::string name, std::unordered_map<std::string, bool>pStates, std::unordered_map<std::string, bool>eStates, int priority = 0);
	void setPreconditionStates(std::unordered_map<std::string, bool>states);
	void setEffectStates(std::unordered_map<std::string, bool>states);
	bool checkPrecondition(const std::unique_ptr<GOAPWorldState>& worldState);

	auto getPriority() -> const int {
		return _priority;
	}
	std::unique_ptr<GOAPGoalState> getGoalState(const std::unique_ptr<GOAPWorldState>& worldState);
	auto getName()-> std::string {
		return _name;
	}
protected:

private:
	std::string _name;
	int _priority;
	std::unordered_map<std::string, bool> _precondition;
	std::unordered_map<std::string, bool> _effect;
};

#endif