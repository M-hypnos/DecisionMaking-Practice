#ifndef __HTN_ITASK_H__
#define __HTN_ITASK_H__
#include "HTNWorldState.h"
#include "AIEnum.h"

class HTNITask
{
public:
	HTNITask() = delete;
	HTNITask(string name):_name(name){}
	virtual HTNTaskType getType() = 0;
	auto getName() -> string { return _name; }
protected:

private:
	string _name;
};

#endif