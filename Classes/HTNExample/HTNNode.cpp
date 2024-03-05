#include "HTNNode.h"

HTNNode* HTNNode::create() {
    HTNNode* htnNode = new(nothrow) HTNNode();
    if (htnNode && htnNode->init()) {
        htnNode->autorelease();
        return htnNode;
    }
    CC_SAFE_DELETE(htnNode);
    return nullptr;
}

HTNNode::~HTNNode() {
    
}

bool HTNNode::init()
{
    AIAttackNode::init();
    _planRunner = make_shared<HTNPlanRunner>(make_shared<HTNPlanner>());
    _domain = make_shared<HTNDomain>();
    _worldState = make_unique<HTNWorldState>();
    _sensors = make_unique<HTNSensors>();

    _sensors->addSensor(make_shared<HTNNodeExampleSpace::HPSensor>(this), _worldState);
    _sensors->addSensor(make_shared<HTNNodeExampleSpace::EnemySensor>(this), _worldState);

    auto deadCheck = [](const unique_ptr<HTNWorldState>& worldState) -> bool {
        return !any_cast<bool>(worldState->getState("alive"));
    };

    auto inSafe = [](const unique_ptr<HTNWorldState>& worldState) -> bool {
        return !any_cast<bool>(worldState->getState("inDanger"));
    };

    auto findEnemy = [](const unique_ptr<HTNWorldState>& worldState) -> bool {
        return any_cast<bool>(worldState->getState("findEnemy"));
    };

    auto inAttackRange = [](const unique_ptr<HTNWorldState>& worldState) -> bool {
        return any_cast<bool>(worldState->getState("inAttackRange"));
    };

    auto noEnemy = [](const unique_ptr<HTNWorldState>& worldState) -> bool {
        return !any_cast<bool>(worldState->getState("findEnemy"));
    };
    
    auto fullHp = [](const unique_ptr<HTNWorldState>& worldState) -> bool {
        return any_cast<bool>(worldState->getState("fullHp"));
    };

    _domain->addTask(make_shared<HTNCompoundTask>("killEnemy"));

    auto wanderTask = make_shared<HTNNodeExampleSpace::WanderNode>(this);
    auto pursuitTask = make_shared<HTNNodeExampleSpace::PursuitNode>(this);
    auto attackTask = make_shared<HTNNodeExampleSpace::AttackNode>(this);
    auto evadingTask = make_shared<HTNNodeExampleSpace::EvadingNode>(this);
    auto idleTask = make_shared<HTNNodeExampleSpace::IdleNode>(this);
    idleTask->addConditions(noEnemy);
    auto deadTask = make_shared<HTNNodeExampleSpace::DeadNode>(this);

    auto atkMethod = make_shared<HTNMethod>("atkMethod");
    atkMethod->addConditions(findEnemy);
    atkMethod->addConditions(inAttackRange);
    auto gotoAtkMethod = make_shared<HTNMethod>("gotoAtkMethod");
    gotoAtkMethod->addConditions(findEnemy);
    auto searchToAtkMethod = make_shared<HTNMethod>("searchToAtkMethod");
    searchToAtkMethod->addConditions(fullHp);
    auto recoverSearchAtkMethod = make_shared<HTNMethod>("recoverSearchAtkMethod");

    auto atkCompTask = make_shared<HTNCompoundTask>("atkCompTask");

    auto attackMethod = make_shared<HTNMethod>("attackMethod");
    attackMethod->addConditions(inSafe);

    auto scapeToRecoverMethod = make_shared<HTNMethod>("scapeToRecoverMethod");
    scapeToRecoverMethod->addConditions(findEnemy);
    auto recoverHpMethod = make_shared<HTNMethod>("recoverHpMethod");

    auto recoverHpCompTask = make_shared<HTNCompoundTask>("recoverHpCompTask");

    auto recoverMethod = make_shared<HTNMethod>("recoverMethod");

    auto aliveCompTask = make_shared<HTNCompoundTask>("aliveCompTask");

    auto aliveMethod = make_shared<HTNMethod>("aliveMethod");

    auto deadMethod = make_shared<HTNMethod>("deadMethod");
    deadMethod->addConditions(deadCheck);

    _domain->addMethod(deadMethod, "killEnemy");

    _domain->addMethod(aliveMethod, "killEnemy");

    _domain->addTask(deadTask, "deadMethod");

    _domain->addTask(aliveCompTask, "aliveMethod");

    _domain->addMethod(attackMethod, "aliveCompTask");
    _domain->addMethod(recoverMethod, "aliveCompTask");

    _domain->addTask(atkCompTask, "attackMethod");
    _domain->addTask(recoverHpCompTask, "recoverMethod");

    _domain->addMethod(atkMethod, "atkCompTask");
    _domain->addMethod(gotoAtkMethod, "atkCompTask");
    _domain->addMethod(searchToAtkMethod, "atkCompTask");
    _domain->addMethod(recoverSearchAtkMethod, "atkCompTask");

    _domain->addTask(attackTask, "atkMethod");

    _domain->addTask(pursuitTask, "gotoAtkMethod");
    _domain->addTask(attackTask, "gotoAtkMethod");

    _domain->addTask(wanderTask, "searchToAtkMethod");
    _domain->addTask(pursuitTask, "searchToAtkMethod");
    _domain->addTask(attackTask, "searchToAtkMethod");

    _domain->addTask(idleTask, "recoverSearchAtkMethod");
    _domain->addTask(wanderTask, "recoverSearchAtkMethod");
    _domain->addTask(pursuitTask, "recoverSearchAtkMethod");
    _domain->addTask(attackTask, "recoverSearchAtkMethod");

    _domain->addMethod(recoverHpMethod, "recoverHpCompTask");
    _domain->addMethod(scapeToRecoverMethod, "recoverHpCompTask");

    _domain->addTask(idleTask, "recoverHpMethod");

    _domain->addTask(evadingTask, "scapeToRecoverMethod");
    _domain->addTask(idleTask, "scapeToRecoverMethod");


    return true;
}

void HTNNode::update(float dt) {
    AIAttackNode::update(dt);
    _sensors->update(_worldState);
    _planRunner->onUpdate(dt, _worldState, _domain->getTask("killEnemy"));
}

HTNResult HTNNode::htnAttack() {
    if (_nearestEnemy == nullptr) {
        return HTNResult::HFAIL;
    }
    if (!inAttackRange()) {
        return HTNResult::HFAIL;
    }
    if (_isInAttacking) return HTNResult::HRUNNING;
    _isInAttacking = true;
    setVelocity(Vec2::ZERO);
    stopORCA();
    Vec2 direct = _nearestEnemy->getPosition() - this->getPosition();
    direct.normalize();
    auto move1 = MoveTo::create(0.1, direct * 5);
    auto move2 = MoveTo::create(0.05, Vec2::ZERO);
    auto callFunc = CallFunc::create([this] {
        _attackNode->clear();
        if (_nearestEnemy != nullptr) _nearestEnemy->hurtEx();
        });
    auto delayTime = DelayTime::create(0.3);
    auto callFunc1 = CallFunc::create([this] {
        resumeORCA();
        stopAttack();
        });
    _renderNode->runAction(Sequence::create(move1, move2, move1, move2, move1, move2, callFunc, delayTime, callFunc1, nullptr));
    _attackNode->drawLine(Vec2::ZERO, _nearestEnemy->getPosition() - this->getPosition(), Color4F(0.7, 0.7, 0.7, 1));
    return HTNResult::HRUNNING;
}

HTNResult HTNNode::htnPursuit(float dt) {
    if (_nearestEnemy == nullptr) {
        return HTNResult::HFAIL;
    }
    if (inAttackRange()) {
        setVelocity(Vec2::ZERO);
        return HTNResult::HSUCCESS;
    }

    Vec2 pursuitPos = _nearestEnemy->getPosition();
    float t = this->getPosition().getDistance(pursuitPos) / _speed / dt;
    Vec2 tarPos = pursuitPos + _nearestEnemy->getVelocity() * 1;
    Vec2 normalVector = (tarPos - this->getPosition()).getNormalized();
    Vec2 desiredVelocity = normalVector * _speed * dt * 2;
    Vec2 steering = desiredVelocity - _velocity;
    _velocity += steering * 2;

    if (_velocity.getLength() > _maxSpeed) {
        _velocity.normalize();
        _velocity *= _maxSpeed;
    }

    checkWall(dt);
    return HTNResult::HRUNNING;
}

HTNResult HTNNode::htnEvading(float dt) {
    if (_nearestEnemy == nullptr) {
        return HTNResult::HSUCCESS;
    }
    Vec2 pursuitPos = _nearestEnemy->getPosition();
    float t = this->getPosition().getDistance(pursuitPos) / _speed / dt;
    Vec2 tarPos = pursuitPos + _nearestEnemy->getVelocity() * 1;
    Vec2 normalVector = (this->getPosition() - tarPos).getNormalized();
    Vec2 desiredVelocity = normalVector * _speed * dt * 2;
    Vec2 steering = desiredVelocity - _velocity;
    _velocity += steering * 2;

    if (_velocity.getLength() > _maxSpeed) {
        _velocity.normalize();
        _velocity *= _maxSpeed;
    }

    checkWall(dt);
    return HTNResult::HRUNNING;
}