#ifndef __HTN_WORLD_STATE_H__
#define __HTN_WORLD_STATE_H__
#include <unordered_map>
#include "utils/Any.h"
using namespace std;
using namespace selfUtils;

class HTNWorldState
{
public:
	HTNWorldState() = default;
	HTNWorldState(unordered_map<string, Any> states);
	void addState(string key, Any data);
	void removeState(string key);
	void updateState(string key, Any data);
	void applyState(string key, Any data);
	const Any& getState(string key);

	auto clone() ->unique_ptr<HTNWorldState> {
		return make_unique<HTNWorldState>(_states);
	}
	auto isDirty() ->bool {
		return _isDirty;
	}
	auto clearDirty() -> void {
		_isDirty = false;
	}
protected:

private:
	unordered_map<string, Any> _states;
	bool _isDirty;
};

#endif