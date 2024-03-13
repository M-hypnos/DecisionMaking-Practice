#include "GOAPNode.h"

GOAPNode* GOAPNode::create() {
    GOAPNode* goapNode = new(nothrow) GOAPNode();
    if (goapNode && goapNode->init()) {
        goapNode->autorelease();
        return goapNode;
    }
    CC_SAFE_DELETE(goapNode);
    return nullptr;
}

GOAPNode::~GOAPNode() {
    
}

bool GOAPNode::init()
{
    AIAttackNode::init();
    _planRunner = make_shared<GOAPPlanRunner>(make_shared<GOAPPlanner>());
    _worldState = make_unique<GOAPWorldState>();
    _sensors = make_unique<GOAPSensors>();

    _sensors->addSensor(make_shared<GOAPNodeExampleSpace::HPSensor>(this), _worldState);
    _sensors->addSensor(make_shared<GOAPNodeExampleSpace::EnemySensor>(this), _worldState);


    unordered_map<string, bool> p = { {"alive", false} };
    unordered_map<string, bool> e = { {"deadDelete", true} };
    _planRunner->addGoal(make_shared<GOAPIGoal>("deleteAfterDead", p, e, 10));

    unordered_map<string, bool> p1 = { {"inDanger", false},{"findEnemy", true} };
    unordered_map<string, bool> e1 = { {"findEnemy", false} };
    _planRunner->addGoal(make_shared<GOAPIGoal>("killEnemy", p1, e1, 5));

    unordered_map<string, bool> p2 = { {"fullHp", false} };
    unordered_map<string, bool> e2 = { {"fullHp", true} };
    _planRunner->addGoal(make_shared<GOAPIGoal>("recoverHp", p2, e2, 3));


    unordered_map<string, bool> p3 = { {"findEnemy", false} };
    unordered_map<string, bool> e3 = { {"findEnemy", true} };
    _planRunner->addGoal(make_shared<GOAPIGoal>("recoverHp", p3, e3, 1));

    _planRunner->addAction(make_shared<GOAPNodeExampleSpace::AttackNode>(this));
    _planRunner->addAction(make_shared<GOAPNodeExampleSpace::DeadNode>(this));
    _planRunner->addAction(make_shared<GOAPNodeExampleSpace::EvadingNode>(this));
    _planRunner->addAction(make_shared<GOAPNodeExampleSpace::IdleNode>(this));
    _planRunner->addAction(make_shared<GOAPNodeExampleSpace::PursuitNode>(this));
    _planRunner->addAction(make_shared<GOAPNodeExampleSpace::WanderNode>(this));

    return true;
}

void GOAPNode::update(float dt) {
    AIAttackNode::update(dt);
    _sensors->update(_worldState);
    _planRunner->onUpdate(dt, _worldState);
}

GOAPResult GOAPNode::htnAttack() {
    if (_nearestEnemy == nullptr) {
        return GOAPResult::GFAIL;
    }
    if (!inAttackRange()) {
        return GOAPResult::GFAIL;
    }
    if (_isInAttacking) return GOAPResult::GRUNNING;
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
    return GOAPResult::GRUNNING;
}

GOAPResult GOAPNode::htnPursuit(float dt) {
    if (_nearestEnemy == nullptr) {
        return GOAPResult::GFAIL;
    }
    if (inAttackRange()) {
        setVelocity(Vec2::ZERO);
        return GOAPResult::GSUCCESS;
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
    return GOAPResult::GRUNNING;
}

GOAPResult GOAPNode::htnEvading(float dt) {
    if (_nearestEnemy == nullptr) {
        return GOAPResult::GSUCCESS;
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
    return GOAPResult::GRUNNING;
}