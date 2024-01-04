#include "AINode.h"

AINode* AINode::create() {
    AINode* aiNode = new(nothrow) AINode();
    if (aiNode && aiNode->init()) {
        aiNode->autorelease();
        return aiNode;
    }
    CC_SAFE_DELETE(aiNode);
    return nullptr;
}

bool AINode::init()
{
    _renderNode = Node::create();
    this->addChild(_renderNode);
    _direct = DrawNode::create();
    _renderNode->addChild(_direct);
    _direct->drawDot(Vec2(0, 0), 2, Color4F(0, 0, 0, 0.7));

    _attackNode = DrawNode::create();
    _renderNode->addChild(_attackNode);

    _label = Label::create();
    _label->setTextColor(Color4B(0, 0, 0, 255));
    _renderNode->addChild(_label);
    _label->setString(to_string(_hp));

    this->scheduleUpdate();
    return true;
}

void AINode::setTarPos(Vec2 tarPos) {
    Vec2 directPos = (tarPos - this->getPosition()).getNormalized();
    _direct->setPosition(directPos * _ridius);
    _tarPos = tarPos;
}

void AINode::update(float dt) {
    
}

void AINode::checkWall(float dt) {
    Vec2 temp = _velocity.getNormalized();
    temp *= 20;
    Vec2 tarPos = this->getPosition() + temp;
    if (!Rect(Vec2::ZERO, Director::getInstance()->getVisibleSize()).containsPoint(tarPos)) {
        Vec2 steering = Vec2::ZERO;
        if (tarPos.y >= Director::getInstance()->getVisibleSize().height) steering += Vec2(0, -1);
        if (tarPos.y <= 0) steering += Vec2(0, 1);
        if (tarPos.x >= Director::getInstance()->getVisibleSize().width) steering += Vec2(-1, 0);
        if (tarPos.x <= 0) steering += Vec2(1, 0);
        _velocity += steering * _speed * dt;
    }
}

void AINode::wander(float dt) {
    Vec2 circleCenter = _velocity.getNormalized();
    circleCenter *= 10;

    float rad = _wanderAngle * M_PI / 180;
    Vec2 displacement;
    displacement.x = cos(rad);
    displacement.y = sin(rad);

    float randomValue = RandomHelper::random_real<float>(-0.5f, 0.5f);
    _wanderAngle += randomValue * 60;

    Vec2 wanderForce = circleCenter + displacement;

    float speed = _speed * dt;
    _velocity += wanderForce;

    if (_velocity.getLength() > _maxSpeed) {
        _velocity.normalize();
        _velocity *= _maxSpeed;
    }

    checkWall(dt);
}

void AINode::pursuit(float dt) {
    if (_nearestEnemy == nullptr) return;
    Vec2 pursuitPos = _nearestEnemy->getPosition();
    float t = this->getPosition().getDistance(pursuitPos) / _speed / dt;
    Vec2 tarPos = pursuitPos + _nearestEnemy->getVelocity() * 3;
    Vec2 normalVector = (tarPos - this->getPosition()).getNormalized();
    Vec2 desiredVelocity = normalVector * _speed * dt;
    Vec2 steering = desiredVelocity - _velocity;
    _velocity += steering;

    if (_velocity.getLength() > _maxSpeed) {
        _velocity.normalize();
        _velocity *= _maxSpeed;
    }

    checkWall(dt);
}

void AINode::evading(float dt) {
    if (_nearestEnemy == nullptr) return;
    Vec2 pursuitPos = _nearestEnemy->getPosition();
    float t = this->getPosition().getDistance(pursuitPos) / _speed / dt;
    Vec2 tarPos = pursuitPos + _nearestEnemy->getVelocity() * 3;
    Vec2 normalVector = (this->getPosition() - tarPos).getNormalized();
    Vec2 desiredVelocity = normalVector * _speed * dt;
    Vec2 steering = desiredVelocity - _velocity;
    _velocity += steering;

    if (_velocity.getLength() > _maxSpeed) {
        _velocity.normalize();
        _velocity *= _maxSpeed;
    }

    checkWall(dt);
}

void AINode::setVelocity(Vec2 velocity) {
    _velocity = velocity;
}

Vec2 AINode::getVelocity() {
    return _velocity;
}

bool AINode::notFoundEnemy() {
    if (_nearestEnemy == nullptr) return true;
    float dist = this->getPosition().getDistance(_nearestEnemy->getPosition());
    return dist > _pursuitRidius;
}

bool AINode::findEnemy() {
    if (_nearestEnemy == nullptr) return false;
    float dist = this->getPosition().getDistance(_nearestEnemy->getPosition());
    return dist > _attackRidius && dist <= _pursuitRidius;
}

bool AINode::inAttackRange() {
    if (_nearestEnemy == nullptr) return false;
    float dist = this->getPosition().getDistance(_nearestEnemy->getPosition());
    return dist <= _attackRidius;
}

void AINode::updatePos(Vec2 velocity) {
    Vec2 directPos = velocity.getNormalized() *= _ridius;
    _direct->setPosition(directPos);
    this->setPosition(this->getPosition() + velocity);
    setVelocity(velocity);
}

void AINode::attack() {
    if (_nearestEnemy == nullptr) return;
    if (_isInAttacking) return;
    _isInAttacking = true;
    Vec2 direct = _nearestEnemy->getPosition() - this->getPosition();
    direct.normalize();
    auto move1 = MoveTo::create(0.1, direct * 5);
    auto move2 = MoveTo::create(0.05, Vec2::ZERO);
    auto callFunc = CallFunc::create([this] {
        _attackNode->clear();
        if (_nearestEnemy != nullptr) _nearestEnemy->hurt();
        });
    auto delayTime = DelayTime::create(0.3);
    auto callFunc1 = CallFunc::create([this] {
        _isInAttacking = false; 
        });
    _renderNode->runAction(Sequence::create(move1, move2, move1, move2, move1, move2, callFunc, delayTime, callFunc1, nullptr));
    _attackNode->drawLine(Vec2::ZERO, _nearestEnemy->getPosition() - this->getPosition(), Color4F(0.7, 0.7, 0.7, 1));
}

void AINode::stopAttack() {
    _renderNode->setPosition(Vec2::ZERO);
    _renderNode->stopAllActions();
    _attackNode->clear();
    _isInAttacking = false;
}

void AINode::hurt() {
    _hp -= 10;
    _label->setString(to_string(_hp));
}

void AINode::recoverHP(float dt) {
    _recoverTime += dt;
    if (_recoverTime > 1) {
        _recoverTime = 0;
        _hp += 2;
        _label->setString(to_string(_hp));
    }
}

void AINode::stopORCA() {
    _weight = 0;
}

void AINode::resumeORCA() {
    _weight = 0.5;
}