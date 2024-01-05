#ifndef __HFSM_H__
#define __HFSM_H__

#include<unordered_map>
#include "HState.h"
#include "HTransition.h"
using namespace std;

class HFSM :public HState
{
public:
	HFSM(int stateId, AINode* aiNode);
	void onAction(float dt);
	void addState(HState* state);
	HTransition* addState(HState* state, bool addTrans);
	HState* removeState(int stateId);
	unordered_map<int, HState*> getAllStates() { return _allStates; }
	bool isRootMachine() { return _parentMachine == nullptr; }
	int getUpdateState();
	int getEnterState();
	void invokeHFSM();
	void setDeafultStateId(int stateId) { _defalutStateId = stateId; }
	HTransition* addTransition(int fromStateId, int toStateId);
	~HFSM();
protected:
	HState* _curState;
	HState* _lastState;
	int _defalutStateId;
	bool _sortTans;
	unordered_map<int, HState*> _allStates;
	vector<HTransition*> _trans;
	vector<HTransition*> _enterTrans;

	virtual void onEnterAction();
	virtual void onExitAction();
	virtual void onUpdateAction(float dt);
};

#endif