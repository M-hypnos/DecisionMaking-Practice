#ifndef __HTN_DOMAIN_H__
#define __HTN_DOMAIN_H__
#include "HTNITask.h"
#include "HTNMethod.h"
#include "HTNCompoundTask.h"
using namespace std;

class HTNDomain
{
public:
	void addTask(shared_ptr<HTNITask> task, string parentMethod = "");
	void addMethod(shared_ptr<HTNMethod> method, string parentTask = "");
	auto getTask(string name) -> const shared_ptr<HTNITask> {
		return _tasks[name];
	}
protected:

private:
	unordered_map<string, shared_ptr<HTNITask>> _tasks;
	unordered_map<string, shared_ptr<HTNMethod>> _methods;
};

#endif