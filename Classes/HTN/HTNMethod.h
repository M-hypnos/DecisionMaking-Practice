#ifndef __HTN_METHOD_H__
#define __HTN_METHOD_H__
#include "HTNITask.h"
#include "HTNPrecondition.h"

class HTNMethod
{
public:
	HTNMethod() = delete;
	HTNMethod(string name, shared_ptr<HTNPrecondition> precondition = nullptr);
	bool checkPrecondition(const unique_ptr<HTNWorldState>& worldState);
	auto getName() -> string { return _name; }
	auto getTasks() -> vector<shared_ptr<HTNITask>> { 
		return _childTasks;
	}
	auto addTask(shared_ptr<HTNITask> task) -> void { 
		_childTasks.push_back(task);
	}
	auto setPreconditionType(int type) -> void {
		if (_precondition) _precondition->setType(type);
	}
	auto addConditions(function<bool(const unique_ptr<HTNWorldState>& worldState)> condition) -> void {
		if (_precondition == nullptr) _precondition = make_shared<HTNPrecondition>();
		_precondition->addConditions(condition);
	}
protected:

private:
	string _name;
	vector<shared_ptr<HTNITask>> _childTasks;
	shared_ptr<HTNPrecondition> _precondition;
};

#endif