#ifndef __GOAP_SENSORS_H__
#define __GOAP_SENSORS_H__

#include <vector>
#include <memory>

class GOAPWorldState;

class GOAPISensor
{
public:
	virtual void initSensor(std::unique_ptr<GOAPWorldState>&worldState) = 0;
	virtual void updateSensor(std::unique_ptr<GOAPWorldState>& worldState) = 0;
};

class GOAPSensors
{
public:
	void addSensor(std::shared_ptr<GOAPISensor> sensor, std::unique_ptr<GOAPWorldState>& worldState);
	void update(std::unique_ptr<GOAPWorldState>& worldState);
protected:

private:
	std::vector<std::shared_ptr<GOAPISensor>> _sensors;
};

#endif