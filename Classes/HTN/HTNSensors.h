#ifndef __HTN_SENSORS_H__
#define __HTN_SENSORS_H__
#include "HTNWorldState.h"
#include <vector>
#include <memory>
using namespace std;

class HTNISensor
{
public:
	virtual void initSensor(unique_ptr<HTNWorldState>&worldState) = 0;
	virtual void updateSensor(unique_ptr<HTNWorldState>& worldState) = 0;
};

class HTNSensors
{
public:
	void addSensor(shared_ptr<HTNISensor> sensor, unique_ptr<HTNWorldState>& worldState);
	void update(unique_ptr<HTNWorldState>& worldState);
protected:

private:
	vector<shared_ptr<HTNISensor>> _sensors;
};

#endif