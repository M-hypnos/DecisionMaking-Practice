#include "HTNDomain.h"

void HTNDomain::addTask(shared_ptr<HTNITask> task, string parentMethod)
{
	string name = task->getName();
	if (parentMethod != "") {
		if (_methods.find(parentMethod) == _methods.end()) {
			printf("error addTask %s cannot find method %s\n", name.c_str(), parentMethod.c_str());
			throw bad_cast();
		}
		_methods[parentMethod]->addTask(task);
	}
	_tasks.emplace(name, task);
}
void HTNDomain::addMethod(shared_ptr<HTNMethod> method, string parentTask)
{
	string name = method->getName();
	if (parentTask != "") {
		if (_tasks.find(parentTask) == _tasks.end()) {
			printf("error addMethod %s cannot find task %s\n", name.c_str(), parentTask.c_str());
			throw bad_cast();
		}
		if (_tasks[parentTask]->getType() != HTNTaskType::COMPOUND) {
			printf("error addMethod %s task is not compoundTask %s\n", name.c_str(), parentTask.c_str());
			throw bad_cast();
		}
		static_pointer_cast<HTNCompoundTask>(_tasks[parentTask])->addMethod(method);
	}
	_methods.emplace(name, method);
}