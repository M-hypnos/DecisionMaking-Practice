#include "AILogNode.h"

AILogNode* AILogNode::create() {
    AILogNode* aiLogNode = new(nothrow) AILogNode();
    if (aiLogNode && aiLogNode->init()) {
        aiLogNode->autorelease();
        return aiLogNode;
    }
    CC_SAFE_DELETE(aiLogNode);
    return nullptr;
}

bool AILogNode::init()
{
    _label = Label::create();
    _label->setTextColor(Color4B(0, 0, 0, 255));
    _label->setSystemFontSize(40);
    this->addChild(_label);

    _label1 = Label::create();
    _label1->setTextColor(Color4B(0, 0, 0, 255));
    _label1->setSystemFontSize(40);
    this->addChild(_label1);
    _label1->setPosition(Vec2(0, 100));

    _label2 = Label::create();
    _label2->setTextColor(Color4B(0, 0, 0, 255));
    _label2->setSystemFontSize(40);
    this->addChild(_label2);
    _label2->setPosition(Vec2(0, -100));


    _btTree = new BTTestTree(nullptr);
    _btTree->setTree();

    this->scheduleUpdate();
    return true;
}

void AILogNode::setString(string str) {
    _label->setString(str);
}
void AILogNode::setString1(string str) {
    _label1->setString(str);
}
void AILogNode::setString2(string str) {
    _label2->setString(str);
}

void AILogNode::update(float dt) {
    _btTree->onUpdate(dt, this);
}

BTResult AILogNode::doImmediatelyAction(string str) {
    float random = RandomHelper::random_real<float>(0, 2);
    if (random <= 1) {
        setString(str + " success");
        return BTResult::SUCCESS;
    }
    else {
        setString(str + " fail");
        return BTResult::FAIL;
    }
}

void AILogNode::interruptAct() {
    _delayActTime = 0;
}

BTResult AILogNode::doDelayAction(float dt, string str) {
    _delayActTime += dt;
    if (_delayActTime > 3) {
        _delayActTime = 0;
        float random = RandomHelper::random_real<float>(0, 5);
        if (random < 3) {
            setString(str + " fail");
            return BTResult::FAIL;
        }
        else {
            setString(str + " success");
            return BTResult::SUCCESS;
        }
    }
    _label->setString(str + " running");
    return BTResult::RUNNING;
}

void AILogNode::startTree() {
    setString("");
    setString1("");
    setString2("");
    _btTree->start(true);
}