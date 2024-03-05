#ifndef __HTN_ISENSOR_H__
#define __HTN_ISENSOR_H__
#include "HTNWorldState.h"

class HTNISensor
{
public:
	virtual void init(unique_ptr<HTNWorldState>& worldState) = 0;
	virtual void updateSensor(unique_ptr<HTNWorldState>& worldState) = 0;
protected:

private:
};

#endif