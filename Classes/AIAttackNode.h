#ifndef _AI_ATTACK_NODE_H__
#define _AI_ATTACK_NODE_H__

#include "cocos2d.h"
#include "AINode.h"
USING_NS_CC;
using namespace std;

class AIAttackNode : public AINode
{
public:
	static AIAttackNode* create();

CC_CONSTRUCTOR_ACCESS:
	virtual bool init() override;

	int getId() { return _id; }
	void setId(int id) { _id = id; }
	void setDirect(DrawNode* direct) { _direct = direct; }
	void setTarPos(Vec2 tarPos);

	Vec2 getVelocity();
	void setVelocity(Vec2 velocity);
	Vec2 getTarPos() { return _tarPos; }

	void wander(float dt);
	void pursuit(float dt);
	BTResult pursuitEx(float dt);
	void evading(float dt);
	BTResult evadingEx(float dt);
	float getRestInterval() { return _restInterval; }
	void setRestInterval(float restInterval) { _restInterval = restInterval; }

	virtual void update(float dt);

	void updatePos(Vec2 velocity);
	void setNearestEnemy(AINode* nearestEnemy);

	bool inPursuitRange();
	bool notFoundEnemy();
	bool inAttackRange();

	bool isInAttack() { return _isInAttacking; }

	float getPursuitRidius() { return _pursuitRidius; }
	float getRidius() { return _ridius; }

	void attack();
	BTResult attackEx();
	void stopAttack();

	void hurt();
	void recoverHP(float dt);

	void checkWall(float dt);

	void stopORCA();
	void resumeORCA();

	float getHP() { return _hp; }

	Node* _renderNode;

	bool isDead() { return _hp <= 0; }

	virtual bool isStopORCA() override;

	void setDead();
protected:
	DrawNode* _direct;
	int _id;

	Vec2 _tarPos;
	Vec2 _velocity;

	float _speed = 30;

	float _ridius = 10;

	float _wanderAngle = 0;

	float _maxSpeed = 1;

	float _restInterval = 10;

	AIAttackNode* _nearestEnemy = nullptr;

	float _attackRidius = 30;
	float _pursuitRidius = 100;

	bool _isInAttacking = false;

	DrawNode* _attackNode;

	int _hp = 100;

	Label* _label;

	float _recoverTime = 0;
};

#endif