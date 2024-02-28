#ifndef __HTN_PRECONDITION_H__
#define __HTN_PRECONDITION_H__
#include "utils/Any.h"
#include <unordered_map>
#include <functional>
#include "AIEnum.h"
#include "HTNWorldState.h"
using namespace selfUtils;

class HTNPrecondition
{
public:
	HTNPrecondition();
	~HTNPrecondition();
	void setType(int type) { _conditionType = type; }
	bool check(const unique_ptr<HTNWorldState>& worldState);
	auto addConditions(function<bool(const unique_ptr<HTNWorldState>& worldState)> condition) -> void { 
		_conditions.push_back(condition);
	}
private:
	int _trueNum;
	int _conditionType;
	vector<function<bool(const unique_ptr<HTNWorldState>& worldState)>> _conditions;
};

#endif