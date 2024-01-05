#ifndef __HSTATE_H__
#define __HSTATE_H__

#include "AINode.h"
using namespace std;

class HState
{
public:
	HState() = delete;
	HState(int stateId, AINode* aiNode);

	virtual ~HState();

	void onEnter();
	void onExit();
	void onUpdate(float dt);

	int getStateId() const { return _id; }

	HState* getParentMachine() { return _parentMachine; }
	void setParentMachine(HState* parentMachine);

	bool operator ==(const HState& rhs) { return this->getStateId() == rhs.getStateId();  }
	bool operator !=(const HState& rhs) { return this->getStateId() != rhs.getStateId();  }
protected:
	int _id;
	bool _isActived;
	float _timer;
	AINode* _aiNode;
	HState* _parentMachine;

private:
	virtual void onEnterAction() = 0;
	virtual void onExitAction() = 0;
	virtual void onUpdateAction(float dt) = 0;
};

#endif