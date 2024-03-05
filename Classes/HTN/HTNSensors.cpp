#include "HTNSensors.h"

void HTNSensors::addSensor(shared_ptr<HTNISensor> sensor, unique_ptr<HTNWorldState>& worldState) {
	_sensors.push_back(sensor);
	sensor->initSensor(worldState);
}

void HTNSensors::update(unique_ptr<HTNWorldState>& worldState) {
	for (auto sensor : _sensors) {
		sensor->updateSensor(worldState);
	}
}