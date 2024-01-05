#include "FSMNode.h"

FSMNode* FSMNode::create() {
    FSMNode* fsmNode = new(nothrow) FSMNode();
    if (fsmNode && fsmNode->init()) {
        fsmNode->autorelease();
        return fsmNode;
    }
    CC_SAFE_DELETE(fsmNode);
    return nullptr;
}

FSMNode::~FSMNode() {
    unordered_map<int, BaseState*> allStates = _fsm->getAllStates();
    for (auto state : allStates) {
        delete state.second;
    }
    delete _fsm;
}

bool FSMNode::init()
{
    AINode::init();
    _fsm = new FSM();
    
    auto condiNotFoundEnemy = [](AINode* aiNode, float timer) -> bool {
        return aiNode->notFoundEnemy();
    };
    auto condiFoundPursuit = [](AINode* aiNode, float timer) -> bool {
        return aiNode->inPursuitRange();
    };
    auto condiFoundEnemy = [](AINode* aiNode, float timer) -> bool {
        return aiNode->inPursuitRange() || aiNode->inAttackRange();
    };
    auto condiHpNotFull = [](AINode* aiNode, float timer) -> bool {
        return aiNode->getHP() < 100;
    };
    auto condiHpFull = [](AINode* aiNode, float timer) -> bool {
        return aiNode->getHP() >= 100;
    };
    auto condiEnemyInAttackRange = [](AINode* aiNode, float timer) -> bool {
        return aiNode->inAttackRange();
    };
    auto condiHpUnEnough = [](AINode* aiNode, float timer) -> bool {
        return aiNode->getHP() < 20;
    };
    auto condiHpEnough = [](AINode* aiNode, float timer) -> bool {
        return aiNode->getHP() >= 20;
    };
    auto condiDead = [](AINode* aiNode, float timer) -> bool {
        return aiNode->isDead();
    };

    BaseState* wanderState = new WanderState(FSMNodeStateID::Wander, this);
    _fsm->addState(wanderState);
    auto wanderToIdle = wanderState->addTransition(FSMNodeStateID::Idle);
    wanderToIdle->addConditions(condiNotFoundEnemy);
    wanderToIdle->addConditions(condiHpNotFull);
    auto wanderToPursuit = wanderState->addTransition(FSMNodeStateID::Pursuit);
    wanderToPursuit->addConditions(condiFoundPursuit);
    wanderToPursuit->addConditions(condiHpEnough);
    auto wanderToAttack = wanderState->addTransition(FSMNodeStateID::Attack);
    wanderToAttack->addConditions(condiEnemyInAttackRange);
    wanderToAttack->addConditions(condiHpEnough);
    auto wanderToDead = wanderState->addTransition(FSMNodeStateID::Dead);
    wanderToDead->addConditions(condiDead);

    BaseState* idleState = new IdleState(FSMNodeStateID::Idle, this);
    _fsm->addState(idleState);
    auto idleToWander = idleState->addTransition(FSMNodeStateID::Wander);
    idleToWander->addConditions(condiHpFull);
    idleToWander->addConditions(condiNotFoundEnemy);
    auto idleToPursuit = idleState->addTransition(FSMNodeStateID::Pursuit);
    idleToPursuit->addConditions(condiHpEnough);
    idleToPursuit->addConditions(condiFoundPursuit);
    auto idleToAttack = idleState->addTransition(FSMNodeStateID::Attack);
    idleToAttack->addConditions(condiHpEnough);
    idleToAttack->addConditions(condiEnemyInAttackRange);
    auto idleToEvading = idleState->addTransition(FSMNodeStateID::Evading);
    idleToEvading->addConditions(condiHpUnEnough);
    idleToEvading->addConditions(condiFoundEnemy);
    auto idleToDead = idleState->addTransition(FSMNodeStateID::Dead);
    idleToDead->addConditions(condiDead);

    BaseState* pursuitState = new PursuitState(FSMNodeStateID::Pursuit, this);
    _fsm->addState(pursuitState);
    auto pursuitToWander = pursuitState->addTransition(FSMNodeStateID::Wander);
    pursuitToWander->addConditions(condiNotFoundEnemy);
    auto pursuitToAttack = pursuitState->addTransition(FSMNodeStateID::Attack);
    pursuitToAttack->addConditions(condiEnemyInAttackRange);
    auto pursuitToDead = pursuitState->addTransition(FSMNodeStateID::Dead);
    pursuitToDead->addConditions(condiDead);

    BaseState* attackState = new AttackState(FSMNodeStateID::Attack, this);
    _fsm->addState(attackState);
    auto attackToIdle = attackState->addTransition(FSMNodeStateID::Idle);
    attackToIdle->addConditions(condiHpNotFull);
    attackToIdle->addConditions(condiNotFoundEnemy);
    auto attackToEvading = attackState->addTransition(FSMNodeStateID::Evading);
    attackToEvading->addConditions(condiHpUnEnough);
    attackToEvading->addConditions(condiFoundEnemy);
    auto attackToPursuit = attackState->addTransition(FSMNodeStateID::Pursuit);
    attackToPursuit->addConditions(condiFoundPursuit);
    auto attackToWander = attackState->addTransition(FSMNodeStateID::Wander);
    attackToWander->addConditions(condiNotFoundEnemy);
    auto attackToDead = attackState->addTransition(FSMNodeStateID::Dead);
    attackToDead->addConditions(condiDead);

    BaseState* evadingState = new EvadingState(FSMNodeStateID::Evading, this);
    _fsm->addState(evadingState);
    auto evadingToIdle = evadingState->addTransition(FSMNodeStateID::Idle);
    evadingToIdle->addConditions(condiNotFoundEnemy);
    auto evadingToDead = evadingState->addTransition(FSMNodeStateID::Dead);
    evadingToDead->addConditions(condiDead);

    BaseState* deadState = new DeadState(FSMNodeStateID::Dead, this);
    _fsm->addState(deadState);
    

    _fsm->invokeFSM(FSMNodeStateID::Wander);
    return true;
}

void FSMNode::update(float dt) {
    AINode::update(dt);
    _fsm->onAction(dt);
}