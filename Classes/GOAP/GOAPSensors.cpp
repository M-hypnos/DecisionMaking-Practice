#include "GOAPSensors.h"
#include "GOAPWorldState.h"

void GOAPSensors::addSensor(std::shared_ptr<GOAPISensor> sensor, std::unique_ptr<GOAPWorldState>& worldState) {
	_sensors.push_back(sensor);
	sensor->initSensor(worldState);
}

void GOAPSensors::update(std::unique_ptr<GOAPWorldState>& worldState) {
	for (auto sensor : _sensors) {
		sensor->updateSensor(worldState);
	}
}