#ifndef __HTN_PRIMITIVE_TASK_H__
#define __HTN_PRIMITIVE_TASK_H__
#include "HTNITask.h"
#include "HTNPrecondition.h"

class HTNPrimitiveTask : public HTNITask
{
public:
	HTNPrimitiveTask() = delete;
	HTNPrimitiveTask(string name, shared_ptr<HTNPrecondition> precondition = nullptr);
	bool checkPrecondition(const unique_ptr<HTNWorldState>& worldState);
	void onEnter();
	virtual HTNResult onUpdate(float dt);
	void onExit(HTNResult result);
	virtual void onInterrupt();
	virtual void effectWorldState(unique_ptr<HTNWorldState>& worldState) = 0;

	auto getType() -> HTNTaskType override { 
		return HTNTaskType::PRIMITIVE; 
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
	shared_ptr<HTNPrecondition> _precondition;
	bool _isRunning = false;
	virtual void onEnterAction() = 0;
	virtual HTNResult onUpdateAction(float dt) = 0;
	virtual void onExitAction(HTNResult result) = 0;
};

#endif