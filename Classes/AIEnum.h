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

enum BTPreconditionType
{
	BTAND,
	BTOR,
	BTNUM
};

enum BTResult
{
	NONE,
	SUCCESS,
	FAIL,
	RUNNING,
	INTERRUPT
};

enum class HTNTaskType {
	PRIMITIVE,
	COMPOUND
};

enum HTNPreconditionType
{
	HTNAND,
	HTNOR,
	HTNNUM
};

enum class HTNResult
{
	HNONE,
	HSUCCESS,
	HFAIL,
	HRUNNING,
	HINTERRUPT
};

enum class GOAPResult
{
	GNONE,
	GSUCCESS,
	GFAIL,
	GRUNNING,
	GINTERRUPT
};

#endif