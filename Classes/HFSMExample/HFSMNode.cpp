#include "HFSMNode.h"

HFSMNode* HFSMNode::create() {
    HFSMNode* hfsmNode = new(nothrow) HFSMNode();
    if (hfsmNode && hfsmNode->init()) {
        hfsmNode->autorelease();
        return hfsmNode;
    }
    CC_SAFE_DELETE(hfsmNode);
    return nullptr;
}

HFSMNode::~HFSMNode() {
    delete _hfsm;
    _hfsm = nullptr;
}

bool HFSMNode::init()
{
    AIAttackNode::init();
    _hfsm = new HFSM(HFSMNodeStateID::ROOT);
    
    // root FSM (alive FSM, dead State)
    HFSM* aliveHfsm = new HFSM(HFSMNodeStateID::ALIVE_FSM);
    _hfsm->addState(aliveHfsm);
    HState* deadHState = new DeadHState(HFSMNodeStateID::DEAD_STATE);
    _hfsm->addState(deadHState);
    _hfsm->setDeafultStateId(HFSMNodeStateID::ALIVE_FSM);
    auto condiDead = [](AINode* aiNode, float timer) -> bool {
        return static_cast<AIAttackNode*>(aiNode)->isDead();
    };
    auto aliveToDead = _hfsm->addTransition(HFSMNodeStateID::ALIVE_FSM, HFSMNodeStateID::DEAD_STATE);
    aliveToDead->addConditions(condiDead);

    // alive FSM (findEnemy FSM, notFindEnemy FSM)
    auto condiNotFoundEnemy = [](AINode* aiNode, float timer) -> bool {
        return static_cast<AIAttackNode*>(aiNode)->notFoundEnemy();
    };
    auto condiFoundEnemy = [](AINode* aiNode, float timer) -> bool {
        return static_cast<AIAttackNode*>(aiNode)->inPursuitRange() || static_cast<AIAttackNode*>(aiNode)->inAttackRange();
    };
    HFSM* findEnemyHfsm = new HFSM(HFSMNodeStateID::FIND_ENEMY_FSM);
    auto enterFindEnemy = aliveHfsm->addState(findEnemyHfsm, true);
    enterFindEnemy->addConditions(condiFoundEnemy);
    HFSM* notFindEnemyHfsm = new HFSM(HFSMNodeStateID::NOT_FIND_ENEMY_FSM);
    auto enterNotFindEnemy = aliveHfsm->addState(notFindEnemyHfsm, true);
    enterNotFindEnemy->addConditions(condiNotFoundEnemy);

    auto findToNotFind = aliveHfsm->addTransition(HFSMNodeStateID::FIND_ENEMY_FSM, HFSMNodeStateID::NOT_FIND_ENEMY_FSM);
    findToNotFind->addConditions(condiNotFoundEnemy);
    auto notFindToFind = aliveHfsm->addTransition(HFSMNodeStateID::NOT_FIND_ENEMY_FSM, HFSMNodeStateID::FIND_ENEMY_FSM);
    notFindToFind->addConditions(condiFoundEnemy);

    // notFindEnemy FSM (wander state, idle state)
    auto condiHpNotFull = [](AINode* aiNode, float timer) -> bool {
        return static_cast<AIAttackNode*>(aiNode)->getHP() < 100;
    };
    auto condiHpFull = [](AINode* aiNode, float timer) -> bool {
        return static_cast<AIAttackNode*>(aiNode)->getHP() >= 100;
    };
    HState* wanderHState = new WanderHState(HFSMNodeStateID::WANDER_STATE);
    auto enterWander = notFindEnemyHfsm->addState(wanderHState, true);
    enterWander->addConditions(condiHpFull);
    HState* idleHState = new IdleHState(HFSMNodeStateID::IDLE_STATE);
    auto enterIdle = notFindEnemyHfsm->addState(idleHState, true);
    enterIdle->addConditions(condiHpNotFull);

    auto wanderToIdle = notFindEnemyHfsm->addTransition(HFSMNodeStateID::WANDER_STATE, HFSMNodeStateID::IDLE_STATE);
    wanderToIdle->addConditions(condiHpNotFull);
    auto idleToWander = notFindEnemyHfsm->addTransition(HFSMNodeStateID::IDLE_STATE, HFSMNodeStateID::WANDER_STATE);
    idleToWander->addConditions(condiHpFull);

    // findEnemy FSM (attack state, pursuit state, evading state)
    auto condiFoundPursuit = [](AINode* aiNode, float timer) -> bool {
        return static_cast<AIAttackNode*>(aiNode)->inPursuitRange();
    };
    auto condiEnemyInAttackRange = [](AINode* aiNode, float timer) -> bool {
        return static_cast<AIAttackNode*>(aiNode)->inAttackRange();
    };
    auto condiHpUnEnough = [](AINode* aiNode, float timer) -> bool {
        return static_cast<AIAttackNode*>(aiNode)->getHP() < 20;
    };
    auto condiHpEnough = [](AINode* aiNode, float timer) -> bool {
        return static_cast<AIAttackNode*>(aiNode)->getHP() >= 20;
    };

    HState* attackHState = new AttackHState(HFSMNodeStateID::ATTACK_STATE);
    auto enterAttack = findEnemyHfsm->addState(attackHState, true);
    enterAttack->addConditions(condiHpEnough);
    enterAttack->addConditions(condiEnemyInAttackRange);
    HState* pursuitHState = new PursuitHState(HFSMNodeStateID::PURSUIT_STATE);
    auto enterPursuit = findEnemyHfsm->addState(pursuitHState, true);
    enterPursuit->addConditions(condiHpEnough);
    enterPursuit->addConditions(condiFoundPursuit);
    HState* evadingHState = new EvadingHState(HFSMNodeStateID::EVADING_STATE);
    auto enterEvading = findEnemyHfsm->addState(evadingHState, true);
    enterEvading->addConditions(condiHpUnEnough);

    auto attackToPursuit = findEnemyHfsm->addTransition(HFSMNodeStateID::ATTACK_STATE, HFSMNodeStateID::PURSUIT_STATE);
    attackToPursuit->addConditions(condiFoundPursuit);
    auto attackToEvading = findEnemyHfsm->addTransition(HFSMNodeStateID::ATTACK_STATE, HFSMNodeStateID::EVADING_STATE);
    attackToEvading->addConditions(condiHpUnEnough);
    auto pursuitToAttack = findEnemyHfsm->addTransition(HFSMNodeStateID::PURSUIT_STATE, HFSMNodeStateID::ATTACK_STATE);
    pursuitToAttack->addConditions(condiEnemyInAttackRange);
    auto pursuitToEvading = findEnemyHfsm->addTransition(HFSMNodeStateID::PURSUIT_STATE, HFSMNodeStateID::EVADING_STATE);
    pursuitToEvading->addConditions(condiHpUnEnough);

    _hfsm->invokeHFSM(this);
    return true;
}

void HFSMNode::update(float dt) {
    AIAttackNode::update(dt);
    _hfsm->onUpdate(dt, this);
}