#ifndef __HSTATE_H__
#define __HSTATE_H__

#include "AINode.h"
using namespace std;

class HState
{
public:
	HState() = delete;
	HState(int stateId);

	virtual ~HState();

	void onEnter(AINode* aiNode);
	void onExit(AINode* aiNode);
	virtual void onUpdate(float dt, AINode* aiNode);

	int getStateId() const { return _id; }

	HState* getParentMachine() { return _parentMachine; }
	void setParentMachine(HState* parentMachine);

	bool operator ==(const HState& rhs) { return this->getStateId() == rhs.getStateId();  }
	bool operator !=(const HState& rhs) { return this->getStateId() != rhs.getStateId();  }
protected:
	int _id;
	bool _isActived;
	float _timer;
	HState* _parentMachine;

private:
	virtual void onEnterAction(AINode* aiNode) = 0;
	virtual void onExitAction(AINode* aiNode) = 0;
	virtual void onUpdateAction(float dt, AINode* aiNode) = 0;
};

#endif