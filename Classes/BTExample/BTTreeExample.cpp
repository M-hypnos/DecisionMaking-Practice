#include "BTTreeExample.h"

BTTreeExample::BTTreeExample( BTNode* root)
: BTTree(root)
{
};

BTTreeExample::~BTTreeExample(){

}

void BTTreeExample::setTree() {
	_root = new BTPrioritySelectNode();

	auto condiDead = [](AINode* aiNode) -> bool {
		return static_cast<AIAttackNode*>(aiNode)->isDead();
	};

	auto condiNotFoundEnemy = [](AINode* aiNode) -> bool {
		return static_cast<AIAttackNode*>(aiNode)->notFoundEnemy();
	};
	auto condiFoundPursuit = [](AINode* aiNode) -> bool {
		return static_cast<AIAttackNode*>(aiNode)->inPursuitRange();
	};
	auto condiFoundEnemy = [](AINode* aiNode) -> bool {
		return static_cast<AIAttackNode*>(aiNode)->inPursuitRange() || static_cast<AIAttackNode*>(aiNode)->inAttackRange();
	};
	auto condiHpNotFull = [](AINode* aiNode) -> bool {
		return static_cast<AIAttackNode*>(aiNode)->getHP() < 100;
	};
	auto condiHpFull = [](AINode* aiNode) -> bool {
		return static_cast<AIAttackNode*>(aiNode)->getHP() >= 100;
	};
	auto condiEnemyInAttackRange = [](AINode* aiNode) -> bool {
		return static_cast<AIAttackNode*>(aiNode)->inAttackRange();
	};
	auto condiHpUnEnough = [](AINode* aiNode) -> bool {
		return static_cast<AIAttackNode*>(aiNode)->getHP() < 20;
	};
	auto condiHpEnough = [](AINode* aiNode) -> bool {
		return static_cast<AIAttackNode*>(aiNode)->getHP() >= 20;
	};

	//root: dead, alive
	auto dead = new BTDeadNode();
	auto DeadCondi = new BTPrecondition();
	DeadCondi->addConditions(condiDead);
	dead->addPrecondition(DeadCondi);
	_root->addChild(dead);

	auto alive = new BTSelectNode();
	_root->addChild(alive);

	//alive: seeEnemy, noEnemy
	auto seeEnemy = new BTPrioritySelectNode();
	auto findEnemyCondi = new BTPrecondition();
	findEnemyCondi->addConditions(condiFoundEnemy);
	seeEnemy->addPrecondition(findEnemyCondi);
	alive->addChild(seeEnemy);
	auto noEnemy = new BTPrioritySelectNode();
	auto noEnemyCondi = new BTPrecondition();
	noEnemyCondi->addConditions(condiNotFoundEnemy);
	noEnemy->addPrecondition(noEnemyCondi);
	alive->addChild(noEnemy);

	//seeEnemy: hpEnough, evading
	auto hpEnough = new BTSequenceNode();
	auto hpEnoughCondi = new BTPrecondition();
	hpEnoughCondi->addConditions(condiHpEnough);
	hpEnough->addPrecondition(hpEnoughCondi);
	seeEnemy->addChild(hpEnough);
	auto evading = new BTEvadingNode();
	seeEnemy->addChild(evading);

	//hpEnough: pursuit, attack
	auto pursuit = new BTPursuitNode();
	hpEnough->addChild(pursuit);
	auto attack = new BTAttackNode();
	hpEnough->addChild(attack);

	//noEnemy: idle, wander
	auto idle = new BTIdleNode();
	auto idleCondi = new BTPrecondition();
	idleCondi->addConditions(condiHpNotFull);
	idle->addPrecondition(idleCondi);
	noEnemy->addChild(idle);
	auto wander = new BTWanderNode();
	noEnemy->addChild(wander);
}