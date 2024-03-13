#include "GOAPTestNode.h"

GOAPTestNode* GOAPTestNode::create() {
    GOAPTestNode* goapTestNode = new(nothrow) GOAPTestNode();
    if (goapTestNode && goapTestNode->init()) {
        goapTestNode->autorelease();
        return goapTestNode;
    }
    CC_SAFE_DELETE(goapTestNode);
    return nullptr;
}

GOAPTestNode::~GOAPTestNode() {

}

bool GOAPTestNode::init()
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

    this->scheduleUpdate();
    return true;
}

void GOAPTestNode::createGoap() {
    if (_planRunner != nullptr) return;
    _planRunner = make_shared<GOAPPlanRunner>(make_shared<GOAPPlanner>());
    _worldState = make_unique<GOAPWorldState>();
    _sensors = make_unique<GOAPSensors>();

    _sensors->addSensor(make_shared<GOAPNodeTestSpace::WoodSensor>(this), _worldState);
    _sensors->addSensor(make_shared<GOAPNodeTestSpace::OreSensor>(this), _worldState);
    _sensors->addSensor(make_shared<GOAPNodeTestSpace::AxeSensor>(this), _worldState);

    unordered_map<string, bool> p1 = { {"hasAxe", false} };
    unordered_map<string, bool> e1 = { {"hasAxe", true} };
    _planRunner->addGoal(make_shared<GOAPIGoal>("getAxe", p1, e1, 1));
    unordered_map<string, bool> p2 = { {"hasAxe", false},{"greedy", true} };
    unordered_map<string, bool> e2 = { {"hasAxe", true}, {"hasOre", false} };
    //unordered_map<string, bool> e2 = { {"hasAxe", true}, {"hasOre", true} };
    _planRunner->addGoal(make_shared<GOAPIGoal>("getAxe&Ore", p2, e2, 2));

    _planRunner->addAction(make_shared<GOAPNodeTestSpace::ChopTree>(this));
    _planRunner->addAction(make_shared<GOAPNodeTestSpace::BuyTree>(this));
    _planRunner->addAction(make_shared<GOAPNodeTestSpace::MineOre>(this));
    _planRunner->addAction(make_shared<GOAPNodeTestSpace::WorksWood>(this));
    _planRunner->addAction(make_shared<GOAPNodeTestSpace::SmeltOre>(this));
    _planRunner->addAction(make_shared<GOAPNodeTestSpace::CreateAxe>(this));
}

void GOAPTestNode::setString(string str) {
    _label->setString(str);
}
void GOAPTestNode::setString1(string str) {
    _label1->setString(str);
}
void GOAPTestNode::setString2(string str) {
    _label2->setString(str);
}

void GOAPTestNode::update(float dt) {
    if (_planRunner == nullptr) return;
    _sensors->update(_worldState);
    _planRunner->onUpdate(dt, _worldState);
}