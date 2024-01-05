#ifndef _AI_ENUM_H__
#define _AI_ENUM_H__

enum TransitionType
{
	AND,
	OR,
	NUM
};

enum FSMNodeStateID
{
	Wander,
	Idle,
	Pursuit,
	Attack,
	Evading,
	Dead
};

enum HTransitionType
{
	HAND,
	HOR,
	HNUM
};

enum HFSMNodeStateID
{
	ROOT,
	ALIVE_FSM,
	DEAD_STATE,
	//ALIVE_FSM
	FIND_ENEMY_FSM,
	NOT_FIND_ENEMY_FSM,
	//FIND_ENEMY_FSM
	ATTACK_STATE,
	PURSUIT_STATE,
	EVADING_STATE,
	//NOT_FIND_ENEMY_FSM
	WANDER_STATE,
	IDLE_STATE
};

#endif