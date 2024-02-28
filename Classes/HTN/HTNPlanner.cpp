#include "HTNPlanner.h"

bool HTNPlanner::plan(const unique_ptr<HTNWorldState>& worldState, shared_ptr<HTNITask> rootTask) {
	unique_ptr<HTNPlannerStatus> plannerStatus = make_unique<HTNPlannerStatus>();
	plannerStatus->tasksToPocess.push(rootTask);
	plannerStatus->curWorldState = worldState->clone();

	stack<unique_ptr<HTNPlannerStatus>> decompHistory;

	while (!plannerStatus->tasksToPocess.empty()) {
		shared_ptr<HTNITask> task = plannerStatus->tasksToPocess.top();
		plannerStatus->tasksToPocess.pop();
		printf("parse cur task %s \n", task->getName().c_str());
		if (task->getType() == HTNTaskType::COMPOUND) {
			if (plannerStatus->nextTaskName != task->getName()) {
				plannerStatus->nextTaskName = task->getName();
				plannerStatus->nextMethodIdx = 0;
			}
			shared_ptr<HTNMethod> satisfiedMethod = static_pointer_cast<HTNCompoundTask>(task)->findSatisfiedMethod(plannerStatus->curWorldState, plannerStatus->nextMethodIdx);
			if (satisfiedMethod != nullptr) {
				printf("operate satisfiedMethod %s \n", satisfiedMethod->getName().c_str());
				//RecordDecompositionOfTask
				decompHistory.push(plannerStatus->clone());
				decompHistory.top()->tasksToPocess.push(task);

				vector<shared_ptr<HTNITask>> tasks = satisfiedMethod->getTasks();
				for (int i = tasks.size() - 1; i >= 0; i--) {
					plannerStatus->tasksToPocess.push(tasks[i]);
				}
			}
			else {
				//RestoreToLastDecomposedTask
				printf("RestoreToLastDecomposedTask \n");
				if (decompHistory.empty()) {
					stack<shared_ptr<HTNITask>>().swap(plannerStatus->tasksToPocess);
				}
				else {
					plannerStatus = decompHistory.top()->clone();
					decompHistory.pop();
				}
			}
		}
		else
		{
			shared_ptr<HTNPrimitiveTask> pTask = static_pointer_cast<HTNPrimitiveTask>(task);
			if (pTask->checkPrecondition(plannerStatus->curWorldState)) {
				printf("push primitiveTask %s \n", pTask->getName().c_str());
				pTask->effectWorldState(plannerStatus->curWorldState);
				plannerStatus->finalPlan.push(pTask);
			}
			else {
				//RestoreToLastDecomposedTask
				printf("RestoreToLastDecomposedTask \n");
				if (decompHistory.empty()) {
					stack<shared_ptr<HTNITask>>().swap(plannerStatus->tasksToPocess);
				}
				else {
					plannerStatus = decompHistory.top()->clone();
					decompHistory.pop();
				}
			}
		}
	}
	if (plannerStatus->finalPlan.empty()) {
		clearPlan();
		return false;
	}
	else {
		_finalPlan.swap(plannerStatus->finalPlan);
		return true;
	}
}