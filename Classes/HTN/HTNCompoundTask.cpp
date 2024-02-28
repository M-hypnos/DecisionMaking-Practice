#include "HTNCompoundTask.h"

HTNCompoundTask::HTNCompoundTask(string name)
: HTNITask(name)
{}

shared_ptr<HTNMethod> HTNCompoundTask::findSatisfiedMethod(const unique_ptr<HTNWorldState>& worldState, int& nextMethodIdx) {
	for (; nextMethodIdx < _methods.size(); nextMethodIdx++) {
		printf("check satisfiedMethod %s \n", _methods[nextMethodIdx]->getName().c_str());
		if (_methods[nextMethodIdx]->checkPrecondition(worldState)) {
			return _methods[nextMethodIdx++];
		}
	}
	nextMethodIdx = 0;
	return nullptr;
}