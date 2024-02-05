#ifndef __BASE_STATE_H__
#define __BASE_STATE_H__

#include "AINode.h"
#include "Transition.h"
using namespace std;

class BaseState
{
public:
	BaseState() = delete;
	BaseState(int stateId);

	virtual ~BaseState();

	void onEnter(AINode* aiNode);
	void onExit(AINode* aiNode);
	void onUpdate(float dt, AINode* aiNode);

	Transition* addTransition(int toStateId);
	int checkChangeState(float dt, AINode* aiNode);

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
	vector<Transition*> _trans;
private:
	virtual void onEnterAction(AINode* aiNode) = 0;
	virtual void onExitAction(AINode* aiNode) = 0;
	virtual void onUpdateAction(float dt, AINode* aiNode) = 0;
};

#endif