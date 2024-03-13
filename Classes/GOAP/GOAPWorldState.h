#ifndef __GOAP_WORLD_STATE_H__
#define __GOAP_WORLD_STATE_H__
#include  <memory>
#include <unordered_map>

class GOAPWorldState
{
public:
	GOAPWorldState();
	GOAPWorldState(const std::unordered_map<std::string, bool>& stateMap);
	GOAPWorldState(const GOAPWorldState& worldState);
	auto getStates() -> std::unordered_map<std::string, bool> {
		return _stateMap;
	}
	auto getStates() const -> std::unordered_map<std::string, bool> {
		return _stateMap;
	}
	void addState(std::string name, bool value = false);
	void removeState(std::string name);
	void updateState(std::string name, bool value = false);
	void applyState(std::string name, bool value);

	auto isDirty() -> const bool {
		return _isDirty;
	}
	auto getState(std::string name) -> bool {
		return _stateMap[name];
	}
	//bool checkSatisfiedWorldState(const std::unique_ptr<GOAPWorldState>& worldState);
	bool checkSatisfiedWorldState(const std::unordered_map<std::string, bool> stateMap);
	auto clearDirty() -> void {
		_isDirty = false;
	}
protected:

private:
	std::unordered_map<std::string, bool> _stateMap;
	bool _isDirty;
};

#endif