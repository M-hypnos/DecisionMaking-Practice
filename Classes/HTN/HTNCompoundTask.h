#ifndef __HTN_COMPOUND_TASK_H__
#define __HTN_COMPOUND_TASK_H__
#include "HTNITask.h"
#include "HTNMethod.h"
using namespace std;

class HTNCompoundTask : public HTNITask
{
public:
	HTNCompoundTask() = delete;
	HTNCompoundTask(string name);
	shared_ptr<HTNMethod> findSatisfiedMethod(const unique_ptr<HTNWorldState>& worldState, int& nextMethodIdx);
	HTNTaskType getType() { return HTNTaskType::COMPOUND; }
	void addMethod(shared_ptr<HTNMethod> method) { _methods.push_back(method); }
protected:

private:
	vector<shared_ptr<HTNMethod>> _methods;
};

#endif