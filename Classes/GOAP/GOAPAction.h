#ifndef __GOAP_ACTION_H__
#define __GOAP_ACTION_H__

#include <memory>
#include <unordered_map>
#include "AIEnum.h"

class GOAPWorldState;

class GOAPAction
{
public:
	GOAPAction() = delete;
	GOAPAction(std::string name, int cost);
	GOAPAction(std::string name, std::unordered_map<std::string, bool>pStates, std::unordered_map<std::string, bool>eStates, int cost);
	void setPreconditionStates(std::unordered_map<std::string, bool>states);
	void setEffectStates(std::unordered_map<std::string, bool>states);
	bool checkPrecondition(const std::unique_ptr<GOAPWorldState>& worldState);
	void effectWorldState(std::unique_ptr<GOAPWorldState>& worldState);
	int getCost() { return _cost; }
	auto getName() -> const std::string {
		return _name;
	}
	auto getPrecondition() -> const std::unordered_map<std::string, bool> {
		return _precondition;
	}
	auto getEffect() -> const std::unordered_map<std::string, bool> {
		return _effect;
	}

	void onEnter();
	virtual GOAPResult onUpdate(float dt);
	void onExit(GOAPResult result);
	virtual void onInterrupt();
protected:

private:
	std::string _name;
	int _cost;
	/*std::unique_ptr<GOAPWorldState> _precondition;
	std::unique_ptr<GOAPWorldState> _effect;*/
	std::unordered_map<std::string, bool> _precondition;
	std::unordered_map<std::string, bool> _effect;
	bool _isRunning = false;
	virtual void onEnterAction() = 0;
	virtual GOAPResult onUpdateAction(float dt) = 0;
	virtual void onExitAction(GOAPResult result) = 0;
};

#endif