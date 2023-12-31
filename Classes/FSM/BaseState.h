#ifndef __BASE_STATE_H__
#define __BASE_STATE_H__

#include "AINode.h"
#include "Transition.h"
using namespace std;

class BaseState
{
public:
	BaseState() = delete;
	BaseState(int stateId, AINode* aiNode);

	virtual ~BaseState();

	void onEnter();
	void onExit();
	void onUpdate(float dt);

	Transition* addTransition(int toStateId);
	int checkChangeState(float dt);

	int getStateId() const { return _id; }
	void setCheckInterval(float checkInterval) { _checkIntervel = checkInterval; }

	bool operator ==(const BaseState& rhs) { return this->getStateId() == rhs.getStateId();  }
	bool operator !=(const BaseState& rhs) { return this->getStateId() != rhs.getStateId();  }
protected:
	int _id;
	bool _isActived;
	float _timer;
	float _checkTimer;
	float _checkIntervel;
	bool _sortTans;
	AINode* _aiNode;
	vector<Transition*> _trans;
private:
	virtual void onEnterAction() = 0;
	virtual void onExitAction() = 0;
	virtual void onUpdateAction(float dt) = 0;
};

#endif